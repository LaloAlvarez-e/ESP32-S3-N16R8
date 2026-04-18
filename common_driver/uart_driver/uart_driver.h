#ifndef BE10A14C_42CD_4FEB_98BA_6F45A133637F
#define BE10A14C_42CD_4FEB_98BA_6F45A133637F
#ifndef UART_DRIVER_H
#define UART_DRIVER_H

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
 * @brief Driver-layer status codes for UART operations.
 */
typedef enum uart_driver_error
{
    UART_DRIVER_ERROR_OK = 0,
    UART_DRIVER_ERROR_INVALID_ARGUMENT = 1,
    UART_DRIVER_ERROR_PLATFORM_FAILURE = 2
} uart_driver_error_t;

/**
 * @brief Platform hook that opens a UART port.
 * @param[in] u32PortNumber UART port identifier.
 * @return UART_DRIVER_ERROR_OK on success, otherwise an error code.
 */
WEAK uart_driver_error_t uart_driver__platform_init(uint32_t u32PortNumber);

/**
 * @brief Platform hook that writes UART bytes.
 * @param[in] u32PortNumber UART port identifier.
 * @param[in] pau8Buffer Buffer to transmit.
 * @param[in] u32Length Number of bytes to transmit.
 * @return UART_DRIVER_ERROR_OK on success, otherwise an error code.
 */
WEAK uart_driver_error_t uart_driver__platform_write(uint32_t u32PortNumber,
                                                     const uint8_t* pau8Buffer,
                                                     uint32_t u32Length);

/**
 * @brief Initialize a UART port.
 * @param[in] u32PortNumber UART port identifier.
 * @return UART_DRIVER_ERROR_OK on success, otherwise an error code.
 */
uart_driver_error_t uart_driver__init(uint32_t u32PortNumber);

/**
 * @brief Write bytes to a UART port.
 * @param[in] u32PortNumber UART port identifier.
 * @param[in] pau8Buffer Buffer to transmit.
 * @param[in] u32Length Number of bytes to transmit.
 * @return UART_DRIVER_ERROR_OK on success, otherwise an error code.
 */
uart_driver_error_t uart_driver__write(uint32_t u32PortNumber,
                                       const uint8_t* pau8Buffer,
                                       uint32_t u32Length);

#ifdef __cplusplus
}
#endif

#endif


#endif /* BE10A14C_42CD_4FEB_98BA_6F45A133637F */
