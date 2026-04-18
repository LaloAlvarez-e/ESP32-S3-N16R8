#include "app_core.h"

#include <stdbool.h>

#include "gpio_driver/gpio_driver.h"

#define APP_CORE_STATUS_LED_PIN (2U)

/**
 * @brief Translate a GPIO driver status into an application-core status.
 * @param[in] eDriverError GPIO driver status.
 * @return SAMPLE_PROJECT_ERROR_OK on success, otherwise an application-core error.
 */
STATIC sample_project_error_t app_core_translate_driver_error(gpio_driver_error_t eDriverError)
{
    sample_project_error_t eError = SAMPLE_PROJECT_ERROR_DRIVER_FAILURE;

    if (GPIO_DRIVER_ERROR_OK == eDriverError)
    {
        eError = SAMPLE_PROJECT_ERROR_OK;
    }

    return eError;
}

/**
 * @brief Translate a telemetry status into an application-core status.
 * @param[in] eTelemetryError Telemetry-module status.
 * @return SAMPLE_PROJECT_ERROR_OK on success, otherwise an application-core error.
 */
STATIC sample_project_error_t app_core_translate_telemetry_error(telemetry_error_t eTelemetryError)
{
    sample_project_error_t eError = SAMPLE_PROJECT_ERROR_TELEMETRY_FAILURE;

    if (TELEMETRY_ERROR_OK == eTelemetryError)
    {
        eError = SAMPLE_PROJECT_ERROR_OK;
    }

    return eError;
}

void app_core__on_cycle_complete(sample_project_error_t eCycleError)
{
    (void)eCycleError;
}

sample_project_error_t app_core__init(void)
{
    sample_project_error_t eError = SAMPLE_PROJECT_ERROR_OK;
    gpio_driver_error_t eDriverError = GPIO_DRIVER_ERROR_OK;

    if (SAMPLE_PROJECT_ERROR_OK == eError)
    {
        eDriverError = gpio_driver__init(APP_CORE_STATUS_LED_PIN);
    }

    if (SAMPLE_PROJECT_ERROR_OK == eError)
    {
        eError = app_core_translate_driver_error(eDriverError);
    }

    return eError;
}

sample_project_error_t app_core__run_cycle(void)
{
    sample_project_error_t eError = SAMPLE_PROJECT_ERROR_OK;
    telemetry_error_t eTelemetryError = TELEMETRY_ERROR_OK;
    gpio_driver_error_t eDriverError = GPIO_DRIVER_ERROR_OK;
    bool bIndicatorRaised = false;

    if (SAMPLE_PROJECT_ERROR_OK == eError)
    {
        eTelemetryError = telemetry__publish(TELEMETRY_MESSAGE_ID_HEARTBEAT);
    }

    if (SAMPLE_PROJECT_ERROR_OK == eError)
    {
        eError = app_core_translate_telemetry_error(eTelemetryError);
    }

    if (SAMPLE_PROJECT_ERROR_OK == eError)
    {
        eDriverError = gpio_driver__set_level(APP_CORE_STATUS_LED_PIN, GPIO_DRIVER_LEVEL_HIGH);
    }

    if (SAMPLE_PROJECT_ERROR_OK == eError)
    {
        eError = app_core_translate_driver_error(eDriverError);
        if (SAMPLE_PROJECT_ERROR_OK == eError)
        {
            bIndicatorRaised = true;
        }
    }

    if (true == bIndicatorRaised)
    {
        eDriverError = gpio_driver__set_level(APP_CORE_STATUS_LED_PIN, GPIO_DRIVER_LEVEL_LOW);
        if ((SAMPLE_PROJECT_ERROR_OK == eError) && (GPIO_DRIVER_ERROR_OK != eDriverError))
        {
            eError = app_core_translate_driver_error(eDriverError);
        }
    }

    app_core__on_cycle_complete(eError);

    return eError;
}

