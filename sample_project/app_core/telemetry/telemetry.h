#ifndef A94AE835_CFE1_4182_8052_D58A760D173F
#define A94AE835_CFE1_4182_8052_D58A760D173F
#ifndef TELEMETRY_H
#define TELEMETRY_H

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
 * @brief Telemetry-module status codes.
 */
typedef enum telemetry_error
{
    TELEMETRY_ERROR_OK = 0,
    TELEMETRY_ERROR_INVALID_ARGUMENT = 1,
    TELEMETRY_ERROR_PLATFORM_FAILURE = 2
} telemetry_error_t;

/**
 * @brief Telemetry message identifiers.
 */
typedef enum telemetry_message_id
{
    TELEMETRY_MESSAGE_ID_HEARTBEAT = 1
} telemetry_message_id_t;

/**
 * @brief Platform hook that transmits a telemetry message.
 * @param[in] enMessageId Telemetry message identifier.
 * @return TELEMETRY_ERROR_OK on success, otherwise an error code.
 */
WEAK telemetry_error_t telemetry__platform_send(telemetry_message_id_t enMessageId);

/**
 * @brief Publish one telemetry message.
 * @param[in] enMessageId Telemetry message identifier.
 * @return TELEMETRY_ERROR_OK on success, otherwise an error code.
 */
telemetry_error_t telemetry__publish(telemetry_message_id_t enMessageId);

#ifdef __cplusplus
}
#endif

#endif


#endif /* A94AE835_CFE1_4182_8052_D58A760D173F */
