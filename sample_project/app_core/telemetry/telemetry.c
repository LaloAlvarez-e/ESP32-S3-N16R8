#include "telemetry.h"

/**
 * @brief Validate a telemetry message identifier.
 * @param[in] enMessageId Telemetry message identifier.
 * @return TELEMETRY_ERROR_OK on success, otherwise an error code.
 */
STATIC telemetry_error_t telemetry_validate_message(telemetry_message_id_t enMessageId)
{
    telemetry_error_t eError = TELEMETRY_ERROR_OK;

    if (TELEMETRY_MESSAGE_ID_HEARTBEAT != enMessageId)
    {
        eError = TELEMETRY_ERROR_INVALID_ARGUMENT;
    }

    return eError;
}

/**
 * @brief Translate a platform hook status into a telemetry-module status.
 * @param[in] ePlatformError Platform hook status.
 * @return TELEMETRY_ERROR_OK on success, otherwise a module error.
 */
STATIC telemetry_error_t telemetry_translate_platform_error(telemetry_error_t ePlatformError)
{
    telemetry_error_t eError = TELEMETRY_ERROR_PLATFORM_FAILURE;

    if (TELEMETRY_ERROR_OK == ePlatformError)
    {
        eError = TELEMETRY_ERROR_OK;
    }

    return eError;
}

telemetry_error_t telemetry__platform_send(telemetry_message_id_t enMessageId)
{
    telemetry_error_t eError = TELEMETRY_ERROR_OK;

    (void)enMessageId;

    return eError;
}

telemetry_error_t telemetry__publish(telemetry_message_id_t enMessageId)
{
    telemetry_error_t eError = TELEMETRY_ERROR_OK;
    telemetry_error_t ePlatformError = TELEMETRY_ERROR_OK;

    eError = telemetry_validate_message(enMessageId);

    if (TELEMETRY_ERROR_OK == eError)
    {
        ePlatformError = telemetry__platform_send(enMessageId);
    }

    if (TELEMETRY_ERROR_OK == eError)
    {
        eError = telemetry_translate_platform_error(ePlatformError);
    }

    return eError;
}

