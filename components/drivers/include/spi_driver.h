/**
 * @file spi_driver.h
 * @brief Thin wrapper around the ESP-IDF SPI master driver.
 */
#pragma once

#include <stddef.h>
#include <stdint.h>
#include "esp_err.h"
#include "driver/spi_master.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Run-time configuration for an SPI master bus + single device. */
typedef struct {
    spi_host_device_t host;   /**< SPI2_HOST or SPI3_HOST.                */
    int               mosi;   /**< GPIO number for MOSI.                  */
    int               miso;   /**< GPIO number for MISO (-1 if not used). */
    int               sclk;   /**< GPIO number for SCLK.                  */
    int               cs;     /**< GPIO number for CS/SS.                 */
    int               clk_hz; /**< SPI clock frequency in Hz.             */
} spi_driver_config_t;

/**
 * @brief  Initialise the SPI bus and add a single device.
 * @return ESP_OK on success, or an ESP-IDF error code.
 */
esp_err_t spi_driver_init(const spi_driver_config_t *cfg);

/**
 * @brief  Perform a full-duplex SPI transfer.
 *
 * @p tx_data and @p rx_data may be NULL if only one direction is needed.
 * Both buffers must be DMA-capable (allocated with heap_caps_malloc or stack
 * with WORD_ALIGNED_ATTR) for large transfers.
 *
 * @return ESP_OK on success, or an ESP-IDF error code.
 */
esp_err_t spi_driver_transfer(const spi_driver_config_t *cfg,
                               const uint8_t *tx_data,
                               uint8_t       *rx_data,
                               size_t         len);

/**
 * @brief  De-initialise the SPI device and free the bus.
 * @return ESP_OK on success, or an ESP-IDF error code.
 */
esp_err_t spi_driver_deinit(const spi_driver_config_t *cfg);

#ifdef __cplusplus
}
#endif
