#include "util_status.h"

#include <stddef.h>

/**
 * @brief Validate the normalization output pointer.
 * @param[in] penOutputError Output pointer to validate.
 * @return UTIL_STATUS_ERROR_OK on success, otherwise an error code.
 */
STATIC util_status_error_t util_status_validate_output_pointer(util_status_error_t* penOutputError)
{
    util_status_error_t eError = UTIL_STATUS_ERROR_OK;

    if (NULL == penOutputError)
    {
        eError = UTIL_STATUS_ERROR_INVALID_ARGUMENT;
    }

    return eError;
}

void util_status__on_normalized(util_status_error_t enInputError,
                                util_status_error_t enOutputError)
{
    (void)enInputError;
    (void)enOutputError;
}

util_status_error_t util_status__normalize(util_status_error_t enInputError,
                                           util_status_error_t* penOutputError)
{
    util_status_error_t eError = UTIL_STATUS_ERROR_OK;
    util_status_error_t enOutputError = UTIL_STATUS_ERROR_INVALID_ARGUMENT;

    eError = util_status_validate_output_pointer(penOutputError);

    if (UTIL_STATUS_ERROR_OK == eError)
    {
        *penOutputError = enInputError;
        enOutputError = *penOutputError;
    }

    util_status__on_normalized(enInputError, enOutputError);

    return eError;
}

