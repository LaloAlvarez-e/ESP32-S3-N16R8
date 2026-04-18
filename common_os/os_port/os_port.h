#ifndef A623DC1D_5C09_4FA6_8E02_F989C8E68835
#define A623DC1D_5C09_4FA6_8E02_F989C8E68835
#ifndef OS_PORT_H
#define OS_PORT_H

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
 * @brief Common OS status codes.
 */
typedef enum common_os_error
{
    COMMON_OS_ERROR_OK = 0,
    COMMON_OS_ERROR_INVALID_ARGUMENT = 1,
    COMMON_OS_ERROR_PLATFORM_FAILURE = 2
} common_os_error_t;

/**
 * @brief Platform hook that starts the underlying scheduler.
 * @return COMMON_OS_ERROR_OK on success, otherwise an error code.
 */
WEAK common_os_error_t os_port__platform_start_scheduler(void);

/**
 * @brief Project override hook called after OS initialization.
 */
WEAK void os_port__on_scheduler_started(void);

/**
 * @brief Initialize the common OS port.
 * @return COMMON_OS_ERROR_OK on success, otherwise an error code.
 */
common_os_error_t os_port__init(void);

#ifdef __cplusplus
}
#endif

#endif


#endif /* A623DC1D_5C09_4FA6_8E02_F989C8E68835 */
