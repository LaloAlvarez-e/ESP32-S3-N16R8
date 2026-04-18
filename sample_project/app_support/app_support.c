#include "app_support.h"

#include "os_clock/os_clock.h"
#include "util_math/util_math.h"
#include "util_status/util_status.h"

#define APP_SUPPORT_BOOT_EVENT_OFFSET (1U)

/**
 * @brief Translate a clock-module error into a support-module error.
 * @param[in] eClockError Clock-module status.
 * @return APP_SUPPORT_ERROR_OK on success, otherwise a support-module error.
 */
STATIC app_support_error_t app_support_translate_clock_error(os_clock_error_t eClockError)
{
    app_support_error_t eError = APP_SUPPORT_ERROR_CLOCK_FAILURE;

    if (OS_CLOCK_ERROR_OK == eClockError)
    {
        eError = APP_SUPPORT_ERROR_OK;
    }

    return eError;
}

/**
 * @brief Translate a utility status error into a support-module error.
 * @param[in] eUtilityError Utility status.
 * @return APP_SUPPORT_ERROR_OK on success, otherwise a support-module error.
 */
STATIC app_support_error_t app_support_translate_status_error(util_status_error_t eUtilityError)
{
    app_support_error_t eError = APP_SUPPORT_ERROR_UTILITY_FAILURE;

    if (UTIL_STATUS_ERROR_OK == eUtilityError)
    {
        eError = APP_SUPPORT_ERROR_OK;
    }

    return eError;
}

/**
 * @brief Translate a utility math error into a support-module error.
 * @param[in] eMathError Utility math status.
 * @return APP_SUPPORT_ERROR_OK on success, otherwise a support-module error.
 */
STATIC app_support_error_t app_support_translate_math_error(util_math_error_t eMathError)
{
    app_support_error_t eError = APP_SUPPORT_ERROR_UTILITY_FAILURE;

    if (UTIL_MATH_ERROR_OK == eMathError)
    {
        eError = APP_SUPPORT_ERROR_OK;
    }

    return eError;
}

app_support_error_t app_support__platform_log(uint32_t u32Value)
{
    app_support_error_t eError = APP_SUPPORT_ERROR_OK;

    (void)u32Value;

    return eError;
}

app_support_error_t app_support__record_boot(void)
{
    app_support_error_t eError = APP_SUPPORT_ERROR_OK;
    os_clock_error_t eClockError = OS_CLOCK_ERROR_OK;
    util_math_error_t eMathError = UTIL_MATH_ERROR_OK;
    app_support_error_t ePlatformError = APP_SUPPORT_ERROR_OK;
    uint32_t u32BootTicks = 0U;
    uint32_t u32LogValue = 0U;

    if (APP_SUPPORT_ERROR_OK == eError)
    {
        eClockError = os_clock__get_ticks(&u32BootTicks);
    }

    if (APP_SUPPORT_ERROR_OK == eError)
    {
        eError = app_support_translate_clock_error(eClockError);
    }

    if (APP_SUPPORT_ERROR_OK == eError)
    {
        eMathError = util_math__saturating_add(u32BootTicks,
                                               APP_SUPPORT_BOOT_EVENT_OFFSET,
                                               &u32LogValue);
    }

    if (APP_SUPPORT_ERROR_OK == eError)
    {
        eError = app_support_translate_math_error(eMathError);
    }

    if (APP_SUPPORT_ERROR_OK == eError)
    {
        ePlatformError = app_support__platform_log(u32LogValue);
    }

    if (APP_SUPPORT_ERROR_OK == eError)
    {
        eError = ePlatformError;
    }

    return eError;
}

app_support_error_t app_support__report_result(uint32_t u32ResultCode)
{
    app_support_error_t eError = APP_SUPPORT_ERROR_OK;
    util_status_error_t eStatusError = UTIL_STATUS_ERROR_OK;
    util_status_error_t enNormalizedError = UTIL_STATUS_ERROR_OK;
    app_support_error_t ePlatformError = APP_SUPPORT_ERROR_OK;

    if (0U != u32ResultCode)
    {
        eStatusError = UTIL_STATUS_ERROR_INVALID_ARGUMENT;
    }

    if (APP_SUPPORT_ERROR_OK == eError)
    {
        eStatusError = util_status__normalize(eStatusError, &enNormalizedError);
    }

    if (APP_SUPPORT_ERROR_OK == eError)
    {
        eError = app_support_translate_status_error(eStatusError);
    }

    if (APP_SUPPORT_ERROR_OK == eError)
    {
        ePlatformError = app_support__platform_log((uint32_t)enNormalizedError);
    }

    if (APP_SUPPORT_ERROR_OK == eError)
    {
        eError = ePlatformError;
    }

    return eError;
}
