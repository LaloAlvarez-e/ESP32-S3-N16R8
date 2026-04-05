#include "spi_driver.h"
#include "esp_log.h"

static const char *TAG = "spi_driver";

/* One device handle per bus (single-device model; extend for multi-device). */
static spi_device_handle_t s_spi_device[SPI_HOST_MAX] = {NULL};

esp_err_t spi_driver_init(const spi_driver_config_t *cfg)
{
    if (cfg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    spi_bus_config_t bus_cfg = {
        .mosi_io_num     = cfg->mosi,
        .miso_io_num     = cfg->miso,
        .sclk_io_num     = cfg->sclk,
        .quadwp_io_num   = -1,
        .quadhd_io_num   = -1,
        .max_transfer_sz = 4096,
    };

    esp_err_t ret = spi_bus_initialize(cfg->host, &bus_cfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "spi_bus_initialize failed: 0x%x", ret);
        return ret;
    }

    spi_device_interface_config_t dev_cfg = {
        .clock_speed_hz = cfg->clk_hz,
        .mode           = 0,
        .spics_io_num   = cfg->cs,
        .queue_size     = 7,
    };

    ret = spi_bus_add_device(cfg->host, &dev_cfg, &s_spi_device[cfg->host]);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "spi_bus_add_device failed: 0x%x", ret);
        spi_bus_free(cfg->host);
        return ret;
    }

    ESP_LOGD(TAG, "SPI host %d initialised at %d Hz", cfg->host, cfg->clk_hz);
    return ESP_OK;
}

esp_err_t spi_driver_transfer(const spi_driver_config_t *cfg,
                               const uint8_t *tx_data,
                               uint8_t       *rx_data,
                               size_t         len)
{
    if (cfg == NULL || len == 0) {
        return ESP_ERR_INVALID_ARG;
    }
    if (s_spi_device[cfg->host] == NULL) {
        ESP_LOGE(TAG, "SPI host %d not initialised", cfg->host);
        return ESP_ERR_INVALID_STATE;
    }

    spi_transaction_t txn = {
        .length    = len * 8,
        .tx_buffer = tx_data,
        .rx_buffer = rx_data,
    };

    return spi_device_transmit(s_spi_device[cfg->host], &txn);
}

esp_err_t spi_driver_deinit(const spi_driver_config_t *cfg)
{
    if (cfg == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    if (s_spi_device[cfg->host] != NULL) {
        spi_bus_remove_device(s_spi_device[cfg->host]);
        s_spi_device[cfg->host] = NULL;
    }
    esp_err_t ret = spi_bus_free(cfg->host);
    if (ret == ESP_OK) {
        ESP_LOGD(TAG, "SPI host %d de-initialised", cfg->host);
    }
    return ret;
}
