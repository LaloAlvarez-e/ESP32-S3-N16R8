if(ESP_PLATFORM)
    idf_component_register(
        SRCS
            gpio_driver/gpio_driver.c
            uart_driver/uart_driver.c
        INCLUDE_DIRS
            .
    )
else()
    add_library(common_driver STATIC
        gpio_driver/gpio_driver.c
        uart_driver/uart_driver.c
    )

    target_include_directories(common_driver
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_compile_features(common_driver PUBLIC c_std_11)

    if(BUILD_TESTING)
        add_subdirectory(test)
    endif()
endif()
