include(GoogleTest)

add_executable(sample_project_app_core_tests
    app_core_test.cpp
    ../app_core/app_core.c
)

target_include_directories(sample_project_app_core_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}/../../common_driver
)

target_compile_definitions(sample_project_app_core_tests PRIVATE UNIT_TEST)
target_compile_features(sample_project_app_core_tests PRIVATE cxx_std_17)
target_link_libraries(sample_project_app_core_tests PRIVATE GTest::gmock_main)

gtest_discover_tests(sample_project_app_core_tests DISCOVERY_TIMEOUT 30)

add_executable(sample_project_telemetry_tests
    telemetry_test.cpp
    ../app_core/telemetry/telemetry.c
)

target_include_directories(sample_project_telemetry_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_definitions(sample_project_telemetry_tests PRIVATE UNIT_TEST)
target_compile_features(sample_project_telemetry_tests PRIVATE cxx_std_17)
target_link_libraries(sample_project_telemetry_tests PRIVATE GTest::gmock_main)

gtest_discover_tests(sample_project_telemetry_tests DISCOVERY_TIMEOUT 30)

add_executable(sample_project_app_support_tests
    app_support_test.cpp
    ../app_support/app_support.c
)

target_include_directories(sample_project_app_support_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}/../../common_utils
        ${CMAKE_CURRENT_SOURCE_DIR}/../../common_os
)

target_compile_definitions(sample_project_app_support_tests PRIVATE UNIT_TEST)
target_compile_features(sample_project_app_support_tests PRIVATE cxx_std_17)
target_link_libraries(sample_project_app_support_tests PRIVATE GTest::gmock_main)

gtest_discover_tests(sample_project_app_support_tests DISCOVERY_TIMEOUT 30)
