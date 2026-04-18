#include <gtest/gtest.h>

extern "C"
{
#include "util_status/util_status.h"
}

TEST(util_status_test, returns_invalid_argument_when_output_pointer_is_null)
{
    EXPECT_EQ(UTIL_STATUS_ERROR_INVALID_ARGUMENT,
              util_status__normalize(UTIL_STATUS_ERROR_OK, nullptr));
}

TEST(util_status_test, copies_input_status_when_output_pointer_is_valid)
{
    util_status_error_t enOutputError = UTIL_STATUS_ERROR_INVALID_ARGUMENT;

    EXPECT_EQ(UTIL_STATUS_ERROR_OK,
              util_status__normalize(UTIL_STATUS_ERROR_OK, &enOutputError));
    EXPECT_EQ(UTIL_STATUS_ERROR_OK, enOutputError);
}

TEST(util_status_test, preserves_non_ok_status_when_output_pointer_is_valid)
{
    util_status_error_t enOutputError = UTIL_STATUS_ERROR_OK;

    EXPECT_EQ(UTIL_STATUS_ERROR_OK,
              util_status__normalize(UTIL_STATUS_ERROR_INVALID_ARGUMENT, &enOutputError));
    EXPECT_EQ(UTIL_STATUS_ERROR_INVALID_ARGUMENT, enOutputError);
}
