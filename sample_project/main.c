#include "sample_project.h"

void app_main(void)
{
    sample_project_error_t eError = SAMPLE_PROJECT_ERROR_OK;
    app_support_error_t eSupportError = APP_SUPPORT_ERROR_OK;

    if (APP_SUPPORT_ERROR_OK == eSupportError)
    {
        eSupportError = app_support__record_boot();
    }

    if (SAMPLE_PROJECT_ERROR_OK == eError)
    {
        eError = app_core__init();
    }

    if (SAMPLE_PROJECT_ERROR_OK == eError)
    {
        eError = app_core__run_cycle();
    }

    if (APP_SUPPORT_ERROR_OK == eSupportError)
    {
        eSupportError = app_support__report_result((uint32_t)eError);
    }

    (void)eError;
    (void)eSupportError;
}
