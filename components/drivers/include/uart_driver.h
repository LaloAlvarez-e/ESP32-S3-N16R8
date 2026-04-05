/**
 * @file uart_driver.h
 * @brief Thin wrapper around the ESP-IDF UART driver.
 */
#pragma once

#include <stddef.h>
#include <stdint.h>
#include "esp_err.h"
#include "driver/uart.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Run-time configuration for a UART port. */
typedef struct {
    uart_port_t port;      /**< UART_NUM_0, UART_NUM_1, or UART_NUM_2.  */
    int         baud_rate; /**< Baud rate (e.g. 115200).                 */
    int         tx_pin;    /**< TX GPIO number (UART_PIN_NO_CHANGE to keep default). */
    int         rx_pin;    /**< RX GPIO number (UART_PIN_NO_CHANGE to keep default). */
    int         buf_size;  /**< RX ring-buffer size in bytes (≥ 128).   */
} uart_driver_config_t;

/**
 * @brief  Install and configure a UART port.
 * @return ESP_OK on success, or an ESP-IDF error code.
 */
esp_err_t uart_driver_init(const uart_driver_config_t *cfg);

/**
 * @brief  Transmit @p len bytes from @p data over the UART port.
 * @return Number of bytes written, or -1 on error.
 */
int uart_driver_write(const uart_driver_config_t *cfg,
                      const uint8_t *data, size_t len);

/**
 * @brief  Read up to @p max_len bytes from the UART RX ring buffer.
 * @param  timeout_ms  Maximum time to wait (portMAX_DELAY for indefinite).
 * @return Number of bytes read (0 if timeout), or -1 on error.
 */
int uart_driver_read(const uart_driver_config_t *cfg,
                     uint8_t *buf, size_t max_len, uint32_t timeout_ms);

/**
 * @brief  De-install the UART driver and free resources.
 * @return ESP_OK on success, or an ESP-IDF error code.
 */
esp_err_t uart_driver_deinit(const uart_driver_config_t *cfg);

#ifdef __cplusplus
}
#endif
