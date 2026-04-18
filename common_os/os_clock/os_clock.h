#ifndef D00C8FE7_704B_4357_860C_E6BC55FB4CE1
#define D00C8FE7_704B_4357_860C_E6BC55FB4CE1
#ifndef OS_CLOCK_H
#define OS_CLOCK_H

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
 * @brief Clock-module status codes.
 */
typedef enum os_clock_error
{
    OS_CLOCK_ERROR_OK = 0,
    OS_CLOCK_ERROR_INVALID_ARGUMENT = 1,
    OS_CLOCK_ERROR_PLATFORM_FAILURE = 2
} os_clock_error_t;

/**
 * @brief Platform hook that retrieves the current tick count.
 * @param[out] pu32Ticks Current platform tick count.
 * @return OS_CLOCK_ERROR_OK on success, otherwise an error code.
 */
WEAK os_clock_error_t os_clock__platform_get_ticks(uint32_t* pu32Ticks);

/**
 * @brief Read the current OS tick count.
 * @param[out] pu32Ticks Current tick count.
 * @return OS_CLOCK_ERROR_OK on success, otherwise an error code.
 */
os_clock_error_t os_clock__get_ticks(uint32_t* pu32Ticks);

#ifdef __cplusplus
}
#endif

#endif


#endif /* D00C8FE7_704B_4357_860C_E6BC55FB4CE1 */
