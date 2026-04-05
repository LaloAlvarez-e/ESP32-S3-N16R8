# ESP32-S3-N16R8 — Host-based unit tests (Google Test)
#
# Build & run (requires CMake ≥ 3.14, a C++17 compiler, and internet access
# to download GoogleTest the first time):
#
#   cd tests
#   cmake -B build -DCMAKE_BUILD_TYPE=Debug
#   cmake --build build
#   ctest --test-dir build --output-on-failure
#
cmake_minimum_required(VERSION 3.14)
project(esp32s3_unit_tests CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------
# GoogleTest — fetched automatically the first time
# ---------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
# Prevent GoogleTest from overriding our compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ---------------------------------------------------------------------------
# Mock / stub include path
#   tests/mocks/ provides lightweight replacements for ESP-IDF headers so
#   that driver logic can be compiled and tested on the host without real
#   hardware or the full IDF tool-chain.
# ---------------------------------------------------------------------------
set(MOCK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mocks)
set(DRIVERS_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/drivers/include)
set(DRIVERS_SRC_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/../components/drivers/src)

# ---------------------------------------------------------------------------
# Unit-test executable
# ---------------------------------------------------------------------------
add_executable(unit_tests
    unit/test_gpio_driver.cpp
    unit/test_uart_driver.cpp
    unit/test_i2c_driver.cpp
    unit/test_spi_driver.cpp
    unit/test_drivers_main.cpp

    # Driver sources compiled against mock headers
    ${DRIVERS_SRC_DIR}/gpio_driver.c
    ${DRIVERS_SRC_DIR}/uart_driver.c
    ${DRIVERS_SRC_DIR}/i2c_driver.c
    ${DRIVERS_SRC_DIR}/spi_driver.c

    # Mock implementations (C-linkage state + stub functions)
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks/src/gpio_mock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks/src/uart_mock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks/src/i2c_mock.c
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks/src/spi_mock.c
)

target_include_directories(unit_tests PRIVATE
    ${MOCK_INCLUDE_DIR}
    ${DRIVERS_INCLUDE_DIR}
)

target_compile_definitions(unit_tests PRIVATE
    UNIT_TEST   # guard used in driver sources when needed
)

target_link_libraries(unit_tests
    GTest::gtest
    GTest::gmock
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
