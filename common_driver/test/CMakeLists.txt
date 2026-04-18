include(GoogleTest)

add_executable(common_driver_gpio_driver_tests
    gpio_driver_test.cpp
    ../gpio_driver/gpio_driver.c
)

target_include_directories(common_driver_gpio_driver_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_definitions(common_driver_gpio_driver_tests PRIVATE UNIT_TEST)
target_compile_features(common_driver_gpio_driver_tests PRIVATE cxx_std_17)
target_link_libraries(common_driver_gpio_driver_tests PRIVATE GTest::gmock_main)

gtest_discover_tests(common_driver_gpio_driver_tests DISCOVERY_TIMEOUT 30)

add_executable(common_driver_uart_driver_tests
    uart_driver_test.cpp
    ../uart_driver/uart_driver.c
)

target_include_directories(common_driver_uart_driver_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_definitions(common_driver_uart_driver_tests PRIVATE UNIT_TEST)
target_compile_features(common_driver_uart_driver_tests PRIVATE cxx_std_17)
target_link_libraries(common_driver_uart_driver_tests PRIVATE GTest::gmock_main)

gtest_discover_tests(common_driver_uart_driver_tests DISCOVERY_TIMEOUT 30)
