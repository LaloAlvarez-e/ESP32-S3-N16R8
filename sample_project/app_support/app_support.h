#ifndef F10B9F6C_130A_4645_9DCB_E5BF066D0B76
#define F10B9F6C_130A_4645_9DCB_E5BF066D0B76
#ifndef APP_SUPPORT_H
#define APP_SUPPORT_H

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
 * @brief Sample-project support-module status codes.
 */
typedef enum app_support_error
{
    APP_SUPPORT_ERROR_OK = 0,
    APP_SUPPORT_ERROR_CLOCK_FAILURE = 1,
    APP_SUPPORT_ERROR_PLATFORM_FAILURE = 2,
    APP_SUPPORT_ERROR_UTILITY_FAILURE = 3
} app_support_error_t;

/**
 * @brief Platform hook that records one support value.
 * @param[in] u32Value Value to log or persist.
 * @return APP_SUPPORT_ERROR_OK on success, otherwise an error code.
 */
WEAK app_support_error_t app_support__platform_log(uint32_t u32Value);

/**
 * @brief Record one boot event for the sample project.
 * @return APP_SUPPORT_ERROR_OK on success, otherwise an error code.
 */
app_support_error_t app_support__record_boot(void);

/**
 * @brief Report one application result code.
 * @param[in] u32ResultCode Result code to report.
 * @return APP_SUPPORT_ERROR_OK on success, otherwise an error code.
 */
app_support_error_t app_support__report_result(uint32_t u32ResultCode);

#ifdef __cplusplus
}
#endif

#endif


#endif /* F10B9F6C_130A_4645_9DCB_E5BF066D0B76 */
