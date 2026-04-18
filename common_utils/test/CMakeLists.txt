include(GoogleTest)

add_executable(common_utils_util_status_tests
    util_status_test.cpp
    ../util_status/util_status.c
)

target_include_directories(common_utils_util_status_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_definitions(common_utils_util_status_tests PRIVATE UNIT_TEST)
target_compile_features(common_utils_util_status_tests PRIVATE cxx_std_17)
target_link_libraries(common_utils_util_status_tests PRIVATE GTest::gmock_main)

gtest_discover_tests(common_utils_util_status_tests DISCOVERY_TIMEOUT 30)

add_executable(common_utils_util_math_tests
    util_math_test.cpp
    ../util_math/util_math.c
)

target_include_directories(common_utils_util_math_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_definitions(common_utils_util_math_tests PRIVATE UNIT_TEST)
target_compile_features(common_utils_util_math_tests PRIVATE cxx_std_17)
target_link_libraries(common_utils_util_math_tests PRIVATE GTest::gmock_main)

gtest_discover_tests(common_utils_util_math_tests DISCOVERY_TIMEOUT 30)
