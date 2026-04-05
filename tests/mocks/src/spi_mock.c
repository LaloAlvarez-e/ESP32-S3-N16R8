#include "driver/spi_master.h"
#include <stdint.h>

spi_mock_state_t spi_mock_state = { .transmit_result = ESP_OK };

esp_err_t spi_bus_initialize(spi_host_device_t host,
                              const spi_bus_config_t *bus_cfg, int dma_chan)
{
    (void)bus_cfg; (void)dma_chan;
    if (host < SPI_HOST_MAX) {
        spi_mock_state.bus_initialized[host] = true;
    }
    return ESP_OK;
}

esp_err_t spi_bus_add_device(spi_host_device_t host,
                              const spi_device_interface_config_t *dev_cfg,
                              spi_device_handle_t *handle)
{
    (void)dev_cfg;
    if (host < SPI_HOST_MAX) {
        spi_mock_state.devices[host] = (void *)((uintptr_t)host + 1);
        *handle = spi_mock_state.devices[host];
    } else {
        *handle = NULL;
    }
    return ESP_OK;
}

esp_err_t spi_device_transmit(spi_device_handle_t handle, spi_transaction_t *trans)
{
    (void)handle; (void)trans;
    return spi_mock_state.transmit_result;
}

esp_err_t spi_bus_remove_device(spi_device_handle_t handle)
{
    (void)handle;
    return ESP_OK;
}

esp_err_t spi_bus_free(spi_host_device_t host)
{
    if (host < SPI_HOST_MAX) {
        spi_mock_state.bus_initialized[host] = false;
        spi_mock_state.devices[host] = NULL;
    }
    return ESP_OK;
}
