if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
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
    project(sample_project)
else()
    add_library(sample_project STATIC
        main.c
        app_core/app_core.c
        app_core/telemetry/telemetry.c
        app_support/app_support.c
    )

    target_include_directories(sample_project
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_link_libraries(sample_project
        PUBLIC
            common_utils
            common_os
            common_driver
    )

    target_compile_features(sample_project PUBLIC c_std_11)

    if(BUILD_TESTING)
        add_subdirectory(test)
    endif()
endif()

