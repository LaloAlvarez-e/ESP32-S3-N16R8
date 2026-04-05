/**
 * @file http_server.h
 * @brief HTTP server with WiFi station mode for the ESP32-S3-N16R8.
 *
 * Provides:
 *  - WiFi station initialisation (credentials from Kconfig)
 *  - HTTP GET  /        — status page
 *  - HTTP GET  /capture — single JPEG frame (requires camera_driver)
 *  - HTTP GET  /stream  — MJPEG stream (requires camera_driver)
 */
#pragma once

#include <stdint.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/** HTTP server runtime configuration. */
typedef struct {
    uint16_t    port;        /**< TCP port to listen on (default 80).      */
    const char *ssid;        /**< WiFi SSID  (NULL → use Kconfig value).   */
    const char *password;    /**< WiFi password (NULL → use Kconfig value). */
} http_server_config_t;

/** Sensible defaults — reads credentials from Kconfig (menuconfig). */
#define HTTP_SERVER_DEFAULT_CONFIG() {  \
    .port     = CONFIG_APP_HTTP_SERVER_PORT, \
    .ssid     = CONFIG_APP_WIFI_SSID,        \
    .password = CONFIG_APP_WIFI_PASSWORD,    \
}

/**
 * @brief  Initialise NVS, WiFi (station mode), and start the HTTP server.
 *
 * Blocks until an IP address is obtained or the retry limit
 * (CONFIG_APP_WIFI_RETRY_MAX) is reached.
 *
 * @return ESP_OK on success, ESP_FAIL if WiFi connection failed.
 */
esp_err_t http_server_start(const http_server_config_t *cfg);

/**
 * @brief  Stop the HTTP server and disconnect WiFi.
 * @return ESP_OK on success.
 */
esp_err_t http_server_stop(void);

#ifdef __cplusplus
}
#endif
