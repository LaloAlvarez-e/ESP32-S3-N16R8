include(GoogleTest)

add_executable(common_os_os_port_tests
    os_port_test.cpp
    ../os_port/os_port.c
)

target_include_directories(common_os_os_port_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_definitions(common_os_os_port_tests PRIVATE UNIT_TEST)
target_compile_features(common_os_os_port_tests PRIVATE cxx_std_17)
target_link_libraries(common_os_os_port_tests PRIVATE GTest::gmock_main)

gtest_discover_tests(common_os_os_port_tests DISCOVERY_TIMEOUT 30)

add_executable(common_os_os_clock_tests
    os_clock_test.cpp
    ../os_clock/os_clock.c
)

target_include_directories(common_os_os_clock_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_definitions(common_os_os_clock_tests PRIVATE UNIT_TEST)
target_compile_features(common_os_os_clock_tests PRIVATE cxx_std_17)
target_link_libraries(common_os_os_clock_tests PRIVATE GTest::gmock_main)

gtest_discover_tests(common_os_os_clock_tests DISCOVERY_TIMEOUT 30)
