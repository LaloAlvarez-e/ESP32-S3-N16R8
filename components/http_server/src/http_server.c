#include "http_server.h"

#include <string.h>
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_http_server.h"
#include "camera_driver.h"
#include "sdkconfig.h"

static const char *TAG = "http_server";

/* -------------------------------------------------------------------------
 * WiFi event handling
 * --------------------------------------------------------------------- */
#define WIFI_CONNECTED_BIT  BIT0
#define WIFI_FAIL_BIT       BIT1

static EventGroupHandle_t s_wifi_event_group = NULL;
static int                s_retry_count      = 0;
static httpd_handle_t     s_httpd            = NULL;

static void wifi_event_handler(void *arg, esp_event_base_t base,
                                int32_t id, void *data)
{
    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_count < CONFIG_APP_WIFI_RETRY_MAX) {
            esp_wifi_connect();
            s_retry_count++;
            ESP_LOGW(TAG, "Retrying WiFi connection (%d/%d)...",
                     s_retry_count, CONFIG_APP_WIFI_RETRY_MAX);
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
            ESP_LOGE(TAG, "WiFi connection failed after %d retries",
                     CONFIG_APP_WIFI_RETRY_MAX);
        }
    } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)data;
        ESP_LOGI(TAG, "WiFi connected. IP: " IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_count = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

static esp_err_t wifi_init_sta(const char *ssid, const char *password)
{
    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t init_cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&init_cfg));

    esp_event_handler_instance_t h_any, h_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, &h_any));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, &h_got_ip));

    wifi_config_t wifi_cfg = {0};
    strlcpy((char *)wifi_cfg.sta.ssid,     ssid,     sizeof(wifi_cfg.sta.ssid));
    strlcpy((char *)wifi_cfg.sta.password, password, sizeof(wifi_cfg.sta.password));
    wifi_cfg.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                            pdFALSE, pdFALSE,
                                            portMAX_DELAY);

    esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, h_any);
    esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, h_got_ip);
    vEventGroupDelete(s_wifi_event_group);
    s_wifi_event_group = NULL;

    if (bits & WIFI_CONNECTED_BIT) {
        return ESP_OK;
    }
    return ESP_FAIL;
}

/* -------------------------------------------------------------------------
 * HTTP request handlers
 * --------------------------------------------------------------------- */

/* GET /  — status page */
static esp_err_t handler_status(httpd_req_t *req)
{
    const char *body =
        "<!DOCTYPE html><html><head><title>ESP32-S3-N16R8</title></head><body>"
        "<h1>ESP32-S3-N16R8 Status</h1>"
        "<p>Server is running.</p>"
        "<ul>"
        "  <li><a href=\"/capture\">Capture single JPEG</a></li>"
        "  <li><a href=\"/stream\">MJPEG stream</a></li>"
        "</ul>"
        "</body></html>";

    httpd_resp_set_type(req, "text/html");
    return httpd_resp_send(req, body, HTTPD_RESP_USE_STRLEN);
}

/* GET /capture — return a single JPEG frame */
static esp_err_t handler_capture(httpd_req_t *req)
{
    camera_fb_t *fb = camera_driver_capture();
    if (fb == NULL) {
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "image/jpeg");
    httpd_resp_set_hdr(req, "Content-Disposition", "inline; filename=capture.jpg");
    esp_err_t ret = httpd_resp_send(req, (const char *)fb->buf, (ssize_t)fb->len);
    camera_driver_return_fb(fb);
    return ret;
}

/* GET /stream — MJPEG stream */
#define STREAM_CONTENT_TYPE  "multipart/x-mixed-replace; boundary=frame"
#define STREAM_BOUNDARY      "\r\n--frame\r\n"
#define STREAM_PART          "Content-Type: image/jpeg\r\nContent-Length: %zu\r\n\r\n"

static esp_err_t handler_stream(httpd_req_t *req)
{
    esp_err_t  ret;
    char       part_buf[64];

    ret = httpd_resp_set_type(req, STREAM_CONTENT_TYPE);
    if (ret != ESP_OK) {
        return ret;
    }

    while (true) {
        camera_fb_t *fb = camera_driver_capture();
        if (fb == NULL) {
            ESP_LOGE(TAG, "Stream: failed to capture frame");
            ret = ESP_FAIL;
            break;
        }

        ret = httpd_resp_send_chunk(req, STREAM_BOUNDARY,
                                    strlen(STREAM_BOUNDARY));
        if (ret == ESP_OK) {
            size_t hlen = (size_t)snprintf(part_buf, sizeof(part_buf),
                                            STREAM_PART, fb->len);
            ret = httpd_resp_send_chunk(req, part_buf, (ssize_t)hlen);
        }
        if (ret == ESP_OK) {
            ret = httpd_resp_send_chunk(req, (const char *)fb->buf,
                                        (ssize_t)fb->len);
        }

        camera_driver_return_fb(fb);

        if (ret != ESP_OK) {
            /* Client disconnected */
            break;
        }
    }

    return ret;
}

/* -------------------------------------------------------------------------
 * Public API
 * --------------------------------------------------------------------- */

esp_err_t http_server_start(const http_server_config_t *cfg)
{
    if (cfg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    /* Initialise NVS (required by WiFi) */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    /* Connect to WiFi */
    const char *ssid     = cfg->ssid     ? cfg->ssid     : CONFIG_APP_WIFI_SSID;
    const char *password = cfg->password ? cfg->password : CONFIG_APP_WIFI_PASSWORD;

    ret = wifi_init_sta(ssid, password);
    if (ret != ESP_OK) {
        ESP_LOGW(TAG, "WiFi not available — HTTP server will not start");
        return ret;
    }

    /* Configure and start HTTP server */
    httpd_config_t httpd_cfg      = HTTPD_DEFAULT_CONFIG();
    httpd_cfg.server_port         = cfg->port;
    httpd_cfg.lru_purge_enable    = true;
    httpd_cfg.max_open_sockets    = 7;

    if (httpd_start(&s_httpd, &httpd_cfg) != ESP_OK) {
        ESP_LOGE(TAG, "httpd_start failed");
        return ESP_FAIL;
    }

    /* Register URI handlers */
    static const httpd_uri_t uri_status = {
        .uri     = "/",
        .method  = HTTP_GET,
        .handler = handler_status,
    };
    static const httpd_uri_t uri_capture = {
        .uri     = "/capture",
        .method  = HTTP_GET,
        .handler = handler_capture,
    };
    static const httpd_uri_t uri_stream = {
        .uri     = "/stream",
        .method  = HTTP_GET,
        .handler = handler_stream,
    };

    httpd_register_uri_handler(s_httpd, &uri_status);
    httpd_register_uri_handler(s_httpd, &uri_capture);
    httpd_register_uri_handler(s_httpd, &uri_stream);

    ESP_LOGI(TAG, "HTTP server listening on port %d", cfg->port);
    return ESP_OK;
}

esp_err_t http_server_stop(void)
{
    if (s_httpd == NULL) {
        return ESP_OK;
    }
    esp_err_t ret = httpd_stop(s_httpd);
    s_httpd = NULL;
    esp_wifi_disconnect();
    esp_wifi_stop();
    ESP_LOGI(TAG, "HTTP server stopped");
    return ret;
}
