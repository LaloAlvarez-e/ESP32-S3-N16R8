cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED ENV{IDF_PATH})
    message(FATAL_ERROR "IDF_PATH is not set. Run the ESP-IDF export script or use the helper scripts under tools/esp32/.")
endif()

set(EXTRA_COMPONENT_DIRS
    "${CMAKE_CURRENT_LIST_DIR}/../common_utils"
    "${CMAKE_CURRENT_LIST_DIR}/../common_os"
    "${CMAKE_CURRENT_LIST_DIR}/../common_driver"
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(hello_world_project)