#ifndef DFA01712_0E99_4B12_A1CF_32EC99D2685F
#define DFA01712_0E99_4B12_A1CF_32EC99D2685F
#ifndef APP_CORE_H
#define APP_CORE_H

#include "telemetry/telemetry.h"

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
 * @brief Sample-project status codes.
 */
typedef enum sample_project_error
{
    SAMPLE_PROJECT_ERROR_OK = 0,
    SAMPLE_PROJECT_ERROR_CHILD_FAILURE = 1,
    SAMPLE_PROJECT_ERROR_DRIVER_FAILURE = 2,
    SAMPLE_PROJECT_ERROR_TELEMETRY_FAILURE = 3
} sample_project_error_t;

/**
 * @brief Optional hook called when one application cycle completes.
 * @param[in] eCycleError Result of the completed cycle.
 */
WEAK void app_core__on_cycle_complete(sample_project_error_t eCycleError);

/**
 * @brief Initialize the application core.
 * @return SAMPLE_PROJECT_ERROR_OK on success, otherwise an error code.
 */
sample_project_error_t app_core__init(void);

/**
 * @brief Run one application-core work cycle.
 * @return SAMPLE_PROJECT_ERROR_OK on success, otherwise an error code.
 */
sample_project_error_t app_core__run_cycle(void);

#ifdef __cplusplus
}
#endif

#endif


#endif /* DFA01712_0E99_4B12_A1CF_32EC99D2685F */
