#ifndef C440A7F3_25A9_4261_9829_B3C5306370EA
#define C440A7F3_25A9_4261_9829_B3C5306370EA
#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>

#if !defined(STATIC)
#if defined(UNIT_TEST)
#define STATIC
#else
#define STATIC static
#endif
#endif

#if !defined(WEAK)
#if defined(UNIT_TEST) || defined(_MSC_VER)
#define WEAK
#else
#define WEAK __attribute__((weak))
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Driver-layer status codes for GPIO operations.
 */
typedef enum gpio_driver_error
{
    GPIO_DRIVER_ERROR_OK = 0,
    GPIO_DRIVER_ERROR_INVALID_ARGUMENT = 1,
    GPIO_DRIVER_ERROR_PLATFORM_FAILURE = 2
} gpio_driver_error_t;

/**
 * @brief Supported GPIO output levels.
 */
typedef enum gpio_driver_level
{
    GPIO_DRIVER_LEVEL_LOW = 0,
    GPIO_DRIVER_LEVEL_HIGH = 1
} gpio_driver_level_t;

/**
 * @brief Platform hook that configures a GPIO pin.
 * @param[in] u32PinNumber GPIO pin identifier.
 * @return GPIO_DRIVER_ERROR_OK on success, otherwise an error code.
 */
WEAK gpio_driver_error_t gpio_driver__platform_init(uint32_t u32PinNumber);

/**
 * @brief Platform hook that applies a GPIO output level.
 * @param[in] u32PinNumber GPIO pin identifier.
 * @param[in] enLevel Output level to apply.
 * @return GPIO_DRIVER_ERROR_OK on success, otherwise an error code.
 */
WEAK gpio_driver_error_t gpio_driver__platform_set_level(uint32_t u32PinNumber,
                                                         gpio_driver_level_t enLevel);

/**
 * @brief Initialize the GPIO driver for a pin.
 * @param[in] u32PinNumber GPIO pin identifier.
 * @return GPIO_DRIVER_ERROR_OK on success, otherwise an error code.
 */
gpio_driver_error_t gpio_driver__init(uint32_t u32PinNumber);

/**
 * @brief Set the logical output level for a GPIO pin.
 * @param[in] u32PinNumber GPIO pin identifier.
 * @param[in] enLevel Output level to apply.
 * @return GPIO_DRIVER_ERROR_OK on success, otherwise an error code.
 */
gpio_driver_error_t gpio_driver__set_level(uint32_t u32PinNumber,
                                           gpio_driver_level_t enLevel);

#ifdef __cplusplus
}
#endif

#endif


#endif /* C440A7F3_25A9_4261_9829_B3C5306370EA */
