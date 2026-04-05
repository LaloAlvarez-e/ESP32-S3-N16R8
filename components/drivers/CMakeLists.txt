idf_component_register(
    SRCS
        "src/gpio_driver.c"
        "src/uart_driver.c"
        "src/i2c_driver.c"
        "src/spi_driver.c"
    INCLUDE_DIRS "include"
    REQUIRES
        driver
        esp_log
)
