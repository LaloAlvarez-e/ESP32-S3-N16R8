if(ESP_PLATFORM)
    idf_component_register(
        SRCS
            util_status/util_status.c
            util_math/util_math.c
        INCLUDE_DIRS
            .
    )
else()
    add_library(common_utils STATIC
        util_status/util_status.c
        util_math/util_math.c
    )

    target_include_directories(common_utils
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_compile_features(common_utils PUBLIC c_std_11)

    if(BUILD_TESTING)
        add_subdirectory(test)
    endif()
endif()
