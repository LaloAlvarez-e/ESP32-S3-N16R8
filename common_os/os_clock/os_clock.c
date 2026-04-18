#include "os_clock.h"

#include <stddef.h>

/**
 * @brief Validate a clock output pointer.
 * @param[in] pu32Ticks Output pointer to validate.
 * @return OS_CLOCK_ERROR_OK on success, otherwise an error code.
 */
STATIC os_clock_error_t os_clock_validate_output_pointer(uint32_t* pu32Ticks)
{
    os_clock_error_t eError = OS_CLOCK_ERROR_OK;

    if (NULL == pu32Ticks)
    {
        eError = OS_CLOCK_ERROR_INVALID_ARGUMENT;
    }

    return eError;
}

/**
 * @brief Translate platform hook status into a module error.
 * @param[in] ePlatformError Platform hook status.
 * @return OS_CLOCK_ERROR_OK on success, otherwise a module error.
 */
STATIC os_clock_error_t os_clock_translate_platform_error(os_clock_error_t ePlatformError)
{
    os_clock_error_t eError = OS_CLOCK_ERROR_PLATFORM_FAILURE;

    if (OS_CLOCK_ERROR_OK == ePlatformError)
    {
        eError = OS_CLOCK_ERROR_OK;
    }

    return eError;
}

os_clock_error_t os_clock__platform_get_ticks(uint32_t* pu32Ticks)
{
    os_clock_error_t eError = OS_CLOCK_ERROR_OK;

    if (NULL != pu32Ticks)
    {
        *pu32Ticks = 0U;
    }
    else
    {
        eError = OS_CLOCK_ERROR_INVALID_ARGUMENT;
    }

    return eError;
}

os_clock_error_t os_clock__get_ticks(uint32_t* pu32Ticks)
{
    os_clock_error_t eError = OS_CLOCK_ERROR_OK;
    os_clock_error_t ePlatformError = OS_CLOCK_ERROR_OK;

    eError = os_clock_validate_output_pointer(pu32Ticks);

    if (OS_CLOCK_ERROR_OK == eError)
    {
        *pu32Ticks = 0U;
    }

    if (OS_CLOCK_ERROR_OK == eError)
    {
        ePlatformError = os_clock__platform_get_ticks(pu32Ticks);
    }

    if (OS_CLOCK_ERROR_OK == eError)
    {
        eError = os_clock_translate_platform_error(ePlatformError);
    }

    return eError;
}
