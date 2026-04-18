if(ESP_PLATFORM)
    idf_component_register(
        SRCS
            os_port/os_port.c
            os_clock/os_clock.c
        INCLUDE_DIRS
            .
    )
else()
    add_library(common_os STATIC
        os_port/os_port.c
        os_clock/os_clock.c
    )

    target_include_directories(common_os
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_compile_features(common_os PUBLIC c_std_11)

    if(BUILD_TESTING)
        add_subdirectory(test)
    endif()
endif()
