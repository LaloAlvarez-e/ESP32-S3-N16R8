#include "uart_driver.h"

#include <stddef.h>

/**
 * @brief Validate a UART port identifier.
 * @param[in] u32PortNumber UART port identifier.
 * @return UART_DRIVER_ERROR_OK on success, otherwise an error code.
 */
STATIC uart_driver_error_t uart_driver_validate_port(uint32_t u32PortNumber)
{
    uart_driver_error_t eError = UART_DRIVER_ERROR_OK;

    if (0U == u32PortNumber)
    {
        eError = UART_DRIVER_ERROR_INVALID_ARGUMENT;
    }

    return eError;
}

/**
 * @brief Validate a UART buffer argument.
 * @param[in] pau8Buffer Buffer to validate.
 * @param[in] u32Length Buffer length.
 * @return UART_DRIVER_ERROR_OK on success, otherwise an error code.
 */
STATIC uart_driver_error_t uart_driver_validate_buffer(const uint8_t* pau8Buffer,
                                                       uint32_t u32Length)
{
    uart_driver_error_t eError = UART_DRIVER_ERROR_OK;

    if ((NULL == pau8Buffer) || (0U == u32Length))
    {
        eError = UART_DRIVER_ERROR_INVALID_ARGUMENT;
    }

    return eError;
}

/**
 * @brief Translate a platform hook status into a module status.
 * @param[in] ePlatformError Platform hook status.
 * @return UART_DRIVER_ERROR_OK on success, otherwise a module error.
 */
STATIC uart_driver_error_t uart_driver_translate_platform_error(uart_driver_error_t ePlatformError)
{
    uart_driver_error_t eError = UART_DRIVER_ERROR_PLATFORM_FAILURE;

    if (UART_DRIVER_ERROR_OK == ePlatformError)
    {
        eError = UART_DRIVER_ERROR_OK;
    }

    return eError;
}

uart_driver_error_t uart_driver__platform_init(uint32_t u32PortNumber)
{
    uart_driver_error_t eError = UART_DRIVER_ERROR_OK;

    (void)u32PortNumber;

    return eError;
}

uart_driver_error_t uart_driver__platform_write(uint32_t u32PortNumber,
                                                const uint8_t* pau8Buffer,
                                                uint32_t u32Length)
{
    uart_driver_error_t eError = UART_DRIVER_ERROR_OK;

    (void)u32PortNumber;
    (void)pau8Buffer;
    (void)u32Length;

    return eError;
}

uart_driver_error_t uart_driver__init(uint32_t u32PortNumber)
{
    uart_driver_error_t eError = UART_DRIVER_ERROR_OK;
    uart_driver_error_t ePlatformError = UART_DRIVER_ERROR_OK;

    eError = uart_driver_validate_port(u32PortNumber);

    if (UART_DRIVER_ERROR_OK == eError)
    {
        ePlatformError = uart_driver__platform_init(u32PortNumber);
    }

    if (UART_DRIVER_ERROR_OK == eError)
    {
        eError = uart_driver_translate_platform_error(ePlatformError);
    }

    return eError;
}

uart_driver_error_t uart_driver__write(uint32_t u32PortNumber,
                                       const uint8_t* pau8Buffer,
                                       uint32_t u32Length)
{
    uart_driver_error_t eError = UART_DRIVER_ERROR_OK;
    uart_driver_error_t ePlatformError = UART_DRIVER_ERROR_OK;

    eError = uart_driver_validate_port(u32PortNumber);

    if (UART_DRIVER_ERROR_OK == eError)
    {
        eError = uart_driver_validate_buffer(pau8Buffer, u32Length);
    }

    if (UART_DRIVER_ERROR_OK == eError)
    {
        ePlatformError = uart_driver__platform_write(u32PortNumber, pau8Buffer, u32Length);
    }

    if (UART_DRIVER_ERROR_OK == eError)
    {
        eError = uart_driver_translate_platform_error(ePlatformError);
    }

    return eError;
}
