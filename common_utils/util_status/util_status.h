#ifndef C135D49F_37CA_495E_A29E_F355C47B5803
#define C135D49F_37CA_495E_A29E_F355C47B5803
#ifndef UTIL_STATUS_H
#define UTIL_STATUS_H

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
 * @brief Utility-library status codes.
 */
typedef enum util_status_error
{
    UTIL_STATUS_ERROR_OK = 0,
    UTIL_STATUS_ERROR_INVALID_ARGUMENT = 1
} util_status_error_t;

/**
 * @brief Optional hook called after status normalization.
 * @param[in] enInputError Input status value.
 * @param[in] enOutputError Normalized output status value.
 */
WEAK void util_status__on_normalized(util_status_error_t enInputError,
                                     util_status_error_t enOutputError);

/**
 * @brief Normalize a utility-library status value.
 * @param[in] enInputError Input status value.
 * @param[out] penOutputError Normalized status value.
 * @return UTIL_STATUS_ERROR_OK on success, otherwise an error code.
 */
util_status_error_t util_status__normalize(util_status_error_t enInputError,
                                           util_status_error_t* penOutputError);

#ifdef __cplusplus
}
#endif

#endif


#endif /* C135D49F_37CA_495E_A29E_F355C47B5803 */
