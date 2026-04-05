#include "uart_driver.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

static const char *TAG = "uart_driver";

esp_err_t uart_driver_init(const uart_driver_config_t *cfg)
{
    if (cfg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uart_config_t uart_cfg = {
        .baud_rate           = cfg->baud_rate,
        .data_bits           = UART_DATA_8_BITS,
        .parity              = UART_PARITY_DISABLE,
        .stop_bits           = UART_STOP_BITS_1,
        .flow_ctrl           = UART_HW_FLOWCTRL_DISABLE,
        .source_clk          = UART_SCLK_DEFAULT,
    };

    esp_err_t ret = uart_param_config(cfg->port, &uart_cfg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "uart_param_config failed: 0x%x", ret);
        return ret;
    }

    ret = uart_set_pin(cfg->port, cfg->tx_pin, cfg->rx_pin,
                       UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "uart_set_pin failed: 0x%x", ret);
        return ret;
    }

    ret = uart_driver_install(cfg->port, cfg->buf_size, 0, 0, NULL, 0);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "uart_driver_install failed: 0x%x", ret);
        return ret;
    }

    ESP_LOGD(TAG, "UART%d initialised at %d baud", cfg->port, cfg->baud_rate);
    return ESP_OK;
}

int uart_driver_write(const uart_driver_config_t *cfg,
                      const uint8_t *data, size_t len)
{
    if (cfg == NULL || data == NULL || len == 0) {
        return -1;
    }
    return uart_write_bytes(cfg->port, (const char *)data, len);
}

int uart_driver_read(const uart_driver_config_t *cfg,
                     uint8_t *buf, size_t max_len, uint32_t timeout_ms)
{
    if (cfg == NULL || buf == NULL || max_len == 0) {
        return -1;
    }
    TickType_t ticks = (timeout_ms == portMAX_DELAY)
                       ? portMAX_DELAY
                       : pdMS_TO_TICKS(timeout_ms);
    return uart_read_bytes(cfg->port, buf, (uint32_t)max_len, ticks);
}

esp_err_t uart_driver_deinit(const uart_driver_config_t *cfg)
{
    if (cfg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    esp_err_t ret = uart_driver_delete(cfg->port);
    if (ret == ESP_OK) {
        ESP_LOGD(TAG, "UART%d de-initialised", cfg->port);
    }
    return ret;
}
