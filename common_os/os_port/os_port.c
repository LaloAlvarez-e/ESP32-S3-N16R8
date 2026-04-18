#include "os_port.h"

common_os_error_t os_port__platform_start_scheduler(void)
{
    common_os_error_t eError = COMMON_OS_ERROR_OK;

    return eError;
}

void os_port__on_scheduler_started(void)
{
}

common_os_error_t os_port__init(void)
{
    common_os_error_t eError = COMMON_OS_ERROR_OK;
    common_os_error_t ePlatformError = COMMON_OS_ERROR_OK;

    if (COMMON_OS_ERROR_OK == eError)
    {
        ePlatformError = os_port__platform_start_scheduler();
    }

    if (COMMON_OS_ERROR_OK == eError)
    {
        if (COMMON_OS_ERROR_OK != ePlatformError)
        {
            eError = COMMON_OS_ERROR_PLATFORM_FAILURE;
        }
    }

    if (COMMON_OS_ERROR_OK == eError)
    {
        os_port__on_scheduler_started();
    }

    return eError;
}

