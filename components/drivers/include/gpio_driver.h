/**
 * @file gpio_driver.h
 * @brief Thin wrapper around the ESP-IDF GPIO driver.
 *
 * Provides a simple, board-agnostic API for configuring and controlling
 * individual GPIO pins on the ESP32-S3.
 */
#pragma once

#include <stdbool.h>
#include "esp_err.h"
#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Run-time configuration for a single GPIO pin. */
typedef struct {
    gpio_num_t   pin;       /**< GPIO number (GPIO_NUM_0 … GPIO_NUM_48).   */
    gpio_mode_t  mode;      /**< GPIO_MODE_INPUT / OUTPUT / INPUT_OUTPUT.   */
    bool         pull_up;   /**< Enable internal pull-up resistor.          */
    bool         pull_down; /**< Enable internal pull-down resistor.        */
} gpio_driver_config_t;

/**
 * @brief  Initialise a GPIO pin according to @p cfg.
 * @return ESP_OK on success, or an ESP-IDF error code.
 */
esp_err_t gpio_driver_init(const gpio_driver_config_t *cfg);

/**
 * @brief  Set the output level of a previously initialised GPIO pin.
 * @param  cfg   Configuration that was used to initialise the pin.
 * @param  level true = HIGH, false = LOW.
 * @return ESP_OK on success, or an ESP-IDF error code.
 */
esp_err_t gpio_driver_set_level(const gpio_driver_config_t *cfg, bool level);

/**
 * @brief  Read the current level of a GPIO pin.
 * @param  cfg   Configuration that was used to initialise the pin.
 * @return 1 (HIGH) or 0 (LOW).
 */
int gpio_driver_get_level(const gpio_driver_config_t *cfg);

/**
 * @brief  De-initialise a GPIO pin and release its resources.
 * @return ESP_OK on success, or an ESP-IDF error code.
 */
esp_err_t gpio_driver_deinit(const gpio_driver_config_t *cfg);

#ifdef __cplusplus
}
#endif
