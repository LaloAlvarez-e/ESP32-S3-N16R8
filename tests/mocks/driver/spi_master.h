/**
 * @file driver/spi_master.h  (mock)
 * @brief Stub SPI master types and functions for host-based unit tests.
 */
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "esp_err.h"

typedef enum {
    SPI1_HOST = 0, SPI2_HOST = 1, SPI3_HOST = 2, SPI_HOST_MAX = 3,
} spi_host_device_t;

#define SPI_DMA_CH_AUTO 3

typedef void *spi_device_handle_t;

typedef struct {
    int mosi_io_num;
    int miso_io_num;
    int sclk_io_num;
    int quadwp_io_num;
    int quadhd_io_num;
    int max_transfer_sz;
} spi_bus_config_t;

typedef struct {
    int     clock_speed_hz;
    uint8_t mode;
    int     spics_io_num;
    int     queue_size;
} spi_device_interface_config_t;

typedef struct {
    size_t         length;
    const uint8_t *tx_buffer;
    uint8_t       *rx_buffer;
} spi_transaction_t;

/* ---------- Mock state (C-linkage, defined in spi_mock.c) --------------- */
typedef struct {
    bool               bus_initialized[SPI_HOST_MAX];
    spi_device_handle_t devices[SPI_HOST_MAX];
    esp_err_t          transmit_result;
} spi_mock_state_t;

#ifdef __cplusplus
extern "C" {
#endif

extern spi_mock_state_t spi_mock_state;

esp_err_t spi_bus_initialize(spi_host_device_t host,
                              const spi_bus_config_t *bus_cfg, int dma_chan);
esp_err_t spi_bus_add_device(spi_host_device_t host,
                              const spi_device_interface_config_t *dev_cfg,
                              spi_device_handle_t *handle);
esp_err_t spi_device_transmit(spi_device_handle_t handle, spi_transaction_t *trans);
esp_err_t spi_bus_remove_device(spi_device_handle_t handle);
esp_err_t spi_bus_free(spi_host_device_t host);

#ifdef __cplusplus
}
#endif
