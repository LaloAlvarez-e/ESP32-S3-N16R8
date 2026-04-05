#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "gpio_driver.h"
#include "uart_driver.h"
#include "i2c_driver.h"
#include "spi_driver.h"
#include "camera_driver.h"
#include "http_server.h"

static const char *TAG = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "ESP32-S3-N16R8 starting up");

    /* ------------------------------------------------------------------
     * 1. Peripheral drivers
     * ------------------------------------------------------------------ */
    gpio_driver_config_t gpio_cfg = {
        .pin        = GPIO_NUM_48,   /* Built-in RGB LED data pin on many S3 devkits */
        .mode       = GPIO_MODE_OUTPUT,
        .pull_up    = false,
        .pull_down  = false,
    };
    ESP_ERROR_CHECK(gpio_driver_init(&gpio_cfg));
    ESP_LOGI(TAG, "GPIO driver initialised");

    uart_driver_config_t uart_cfg = {
        .port      = UART_NUM_0,
        .baud_rate = 115200,
        .tx_pin    = UART_PIN_NO_CHANGE,
        .rx_pin    = UART_PIN_NO_CHANGE,
        .buf_size  = 256,
    };
    ESP_ERROR_CHECK(uart_driver_init(&uart_cfg));
    ESP_LOGI(TAG, "UART driver initialised");

    i2c_driver_config_t i2c_cfg = {
        .port     = I2C_NUM_0,
        .sda_pin  = GPIO_NUM_8,
        .scl_pin  = GPIO_NUM_9,
        .clk_hz   = 400000,
        .pullup   = true,
    };
    ESP_ERROR_CHECK(i2c_driver_init(&i2c_cfg));
    ESP_LOGI(TAG, "I2C driver initialised");

    spi_driver_config_t spi_cfg = {
        .host    = SPI2_HOST,
        .mosi    = GPIO_NUM_11,
        .miso    = GPIO_NUM_13,
        .sclk    = GPIO_NUM_12,
        .cs      = GPIO_NUM_10,
        .clk_hz  = 10000000,
    };
    ESP_ERROR_CHECK(spi_driver_init(&spi_cfg));
    ESP_LOGI(TAG, "SPI driver initialised");

    /* ------------------------------------------------------------------
     * 2. Camera (OV2640, JPEG, QVGA — adjust pins for your module)
     * ------------------------------------------------------------------ */
    camera_config_t cam_cfg = CAMERA_DEFAULT_CONFIG();
    esp_err_t cam_err = camera_driver_init(&cam_cfg);
    if (cam_err == ESP_OK) {
        ESP_LOGI(TAG, "Camera driver initialised");
    } else {
        ESP_LOGW(TAG, "Camera not detected (err 0x%x) — continuing without camera", cam_err);
    }

    /* ------------------------------------------------------------------
     * 3. HTTP server (WiFi credentials come from Kconfig / menuconfig)
     * ------------------------------------------------------------------ */
    http_server_config_t srv_cfg = HTTP_SERVER_DEFAULT_CONFIG();
    ESP_ERROR_CHECK(http_server_start(&srv_cfg));
    ESP_LOGI(TAG, "HTTP server started on port %d", srv_cfg.port);

    /* ------------------------------------------------------------------
     * 4. Main loop — blink the status LED
     * ------------------------------------------------------------------ */
    bool led_state = false;
    while (1) {
        gpio_driver_set_level(&gpio_cfg, led_state);
        led_state = !led_state;
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
