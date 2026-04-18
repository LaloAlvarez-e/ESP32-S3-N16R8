#ifndef FA6BE589_3ACC_4E94_949C_C4AE5680F7F9
#define FA6BE589_3ACC_4E94_949C_C4AE5680F7F9
#ifndef UTIL_MATH_H
#define UTIL_MATH_H

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
 * @brief Utility math status codes.
 */
typedef enum util_math_error
{
    UTIL_MATH_ERROR_OK = 0,
    UTIL_MATH_ERROR_INVALID_ARGUMENT = 1,
    UTIL_MATH_ERROR_OVERFLOW = 2
} util_math_error_t;

/**
 * @brief Optional hook called when saturating addition overflows.
 * @param[in] u32Left Left input value.
 * @param[in] u32Right Right input value.
 */
WEAK void util_math__on_overflow(uint32_t u32Left, uint32_t u32Right);

/**
 * @brief Add two values using saturation on overflow.
 * @param[in] u32Left Left input value.
 * @param[in] u32Right Right input value.
 * @param[out] pu32Result Saturated result value.
 * @return UTIL_MATH_ERROR_OK on success, otherwise an error code.
 */
util_math_error_t util_math__saturating_add(uint32_t u32Left,
                                            uint32_t u32Right,
                                            uint32_t* pu32Result);

#ifdef __cplusplus
}
#endif

#endif


#endif /* FA6BE589_3ACC_4E94_949C_C4AE5680F7F9 */
