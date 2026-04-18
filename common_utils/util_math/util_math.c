#include "util_math.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Validate the output pointer for a math operation.
 * @param[in] pu32Result Output pointer to validate.
 * @return UTIL_MATH_ERROR_OK on success, otherwise an error code.
 */
STATIC util_math_error_t util_math_validate_output_pointer(uint32_t* pu32Result)
{
    util_math_error_t eError = UTIL_MATH_ERROR_OK;

    if (NULL == pu32Result)
    {
        eError = UTIL_MATH_ERROR_INVALID_ARGUMENT;
    }

    return eError;
}

/**
 * @brief Detect whether a 32-bit addition will overflow.
 * @param[in] u32Left Left input value.
 * @param[in] u32Right Right input value.
 * @return true when overflow will occur, otherwise false.
 */
STATIC bool util_math_detect_overflow(uint32_t u32Left, uint32_t u32Right)
{
    bool bOverflow = false;

    if ((UINT32_MAX - u32Left) < u32Right)
    {
        bOverflow = true;
    }

    return bOverflow;
}

void util_math__on_overflow(uint32_t u32Left, uint32_t u32Right)
{
    (void)u32Left;
    (void)u32Right;
}

util_math_error_t util_math__saturating_add(uint32_t u32Left,
                                            uint32_t u32Right,
                                            uint32_t* pu32Result)
{
    util_math_error_t eError = UTIL_MATH_ERROR_OK;

    eError = util_math_validate_output_pointer(pu32Result);

    if (UTIL_MATH_ERROR_OK == eError)
    {
        *pu32Result = 0U;
    }

    if (UTIL_MATH_ERROR_OK == eError)
    {
        if (true == util_math_detect_overflow(u32Left, u32Right))
        {
            *pu32Result = UINT32_MAX;
            util_math__on_overflow(u32Left, u32Right);
            eError = UTIL_MATH_ERROR_OVERFLOW;
        }
    }

    if (UTIL_MATH_ERROR_OK == eError)
    {
        *pu32Result = u32Left + u32Right;
    }

    return eError;
}
