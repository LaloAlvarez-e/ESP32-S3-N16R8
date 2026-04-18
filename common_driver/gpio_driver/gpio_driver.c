#include "gpio_driver.h"

/**
 * @brief Validate a GPIO pin identifier.
 * @param[in] u32PinNumber GPIO pin identifier.
 * @return GPIO_DRIVER_ERROR_OK on success, otherwise an error code.
 */
STATIC gpio_driver_error_t gpio_driver_validate_pin(uint32_t u32PinNumber)
{
    gpio_driver_error_t eError = GPIO_DRIVER_ERROR_OK;

    if (0U == u32PinNumber)
    {
        eError = GPIO_DRIVER_ERROR_INVALID_ARGUMENT;
    }

    return eError;
}

/**
 * @brief Validate a GPIO output level.
 * @param[in] enLevel Output level to validate.
 * @return GPIO_DRIVER_ERROR_OK on success, otherwise an error code.
 */
STATIC gpio_driver_error_t gpio_driver_validate_level(gpio_driver_level_t enLevel)
{
    gpio_driver_error_t eError = GPIO_DRIVER_ERROR_OK;

    if ((GPIO_DRIVER_LEVEL_LOW != enLevel) && (GPIO_DRIVER_LEVEL_HIGH != enLevel))
    {
        eError = GPIO_DRIVER_ERROR_INVALID_ARGUMENT;
    }

    return eError;
}

/**
 * @brief Translate a platform error into a module error.
 * @param[in] ePlatformError Platform hook status.
 * @return GPIO_DRIVER_ERROR_OK on success, otherwise a module error.
 */
STATIC gpio_driver_error_t gpio_driver_translate_platform_error(gpio_driver_error_t ePlatformError)
{
    gpio_driver_error_t eError = GPIO_DRIVER_ERROR_PLATFORM_FAILURE;

    if (GPIO_DRIVER_ERROR_OK == ePlatformError)
    {
        eError = GPIO_DRIVER_ERROR_OK;
    }

    return eError;
}

gpio_driver_error_t gpio_driver__platform_init(uint32_t u32PinNumber)
{
    gpio_driver_error_t eError = GPIO_DRIVER_ERROR_OK;

    (void)u32PinNumber;

    return eError;
}

gpio_driver_error_t gpio_driver__platform_set_level(uint32_t u32PinNumber,
                                                    gpio_driver_level_t enLevel)
{
    gpio_driver_error_t eError = GPIO_DRIVER_ERROR_OK;

    (void)u32PinNumber;
    (void)enLevel;

    return eError;
}

gpio_driver_error_t gpio_driver__init(uint32_t u32PinNumber)
{
    gpio_driver_error_t eError = GPIO_DRIVER_ERROR_OK;
    gpio_driver_error_t ePlatformError = GPIO_DRIVER_ERROR_OK;

    eError = gpio_driver_validate_pin(u32PinNumber);

    if (GPIO_DRIVER_ERROR_OK == eError)
    {
        ePlatformError = gpio_driver__platform_init(u32PinNumber);
    }

    if (GPIO_DRIVER_ERROR_OK == eError)
    {
        eError = gpio_driver_translate_platform_error(ePlatformError);
    }

    return eError;
}

gpio_driver_error_t gpio_driver__set_level(uint32_t u32PinNumber,
                                           gpio_driver_level_t enLevel)
{
    gpio_driver_error_t eError = GPIO_DRIVER_ERROR_OK;
    gpio_driver_error_t ePlatformError = GPIO_DRIVER_ERROR_OK;

    eError = gpio_driver_validate_pin(u32PinNumber);

    if (GPIO_DRIVER_ERROR_OK == eError)
    {
        eError = gpio_driver_validate_level(enLevel);
    }

    if (GPIO_DRIVER_ERROR_OK == eError)
    {
        ePlatformError = gpio_driver__platform_set_level(u32PinNumber, enLevel);
    }

    if (GPIO_DRIVER_ERROR_OK == eError)
    {
        eError = gpio_driver_translate_platform_error(ePlatformError);
    }

    return eError;
}

