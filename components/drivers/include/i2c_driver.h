/**
 * @file i2c_driver.h
 * @brief Thin wrapper around the ESP-IDF I2C master driver.
 */
#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "driver/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Run-time configuration for an I2C master port. */
typedef struct {
    i2c_port_t port;    /**< I2C_NUM_0 or I2C_NUM_1.                      */
    int        sda_pin; /**< GPIO number for SDA.                          */
    int        scl_pin; /**< GPIO number for SCL.                          */
    uint32_t   clk_hz;  /**< Bus clock frequency in Hz (e.g. 400000).      */
    bool       pullup;  /**< Enable ESP32-S3 internal pull-ups on SDA/SCL. */
} i2c_driver_config_t;

/**
 * @brief  Install and configure an I2C master port.
 * @return ESP_OK on success, or an ESP-IDF error code.
 */
esp_err_t i2c_driver_init(const i2c_driver_config_t *cfg);

/**
 * @brief  Write @p len bytes to I2C slave at @p dev_addr.
 * @return ESP_OK on success, or an ESP-IDF error code.
 */
esp_err_t i2c_driver_write(const i2c_driver_config_t *cfg,
                            uint8_t dev_addr,
                            const uint8_t *data, size_t len);

/**
 * @brief  Read @p len bytes from I2C slave at @p dev_addr.
 * @return ESP_OK on success, or an ESP-IDF error code.
 */
esp_err_t i2c_driver_read(const i2c_driver_config_t *cfg,
                           uint8_t dev_addr,
                           uint8_t *buf, size_t len);

/**
 * @brief  Write @p write_len bytes then read @p read_len bytes (register read pattern).
 * @return ESP_OK on success, or an ESP-IDF error code.
 */
esp_err_t i2c_driver_write_read(const i2c_driver_config_t *cfg,
                                 uint8_t dev_addr,
                                 const uint8_t *write_buf, size_t write_len,
                                 uint8_t *read_buf,  size_t read_len);

/**
 * @brief  De-install the I2C driver and free resources.
 * @return ESP_OK on success, or an ESP-IDF error code.
 */
esp_err_t i2c_driver_deinit(const i2c_driver_config_t *cfg);

#ifdef __cplusplus
}
#endif
