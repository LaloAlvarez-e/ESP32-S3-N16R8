idf_component_register(
    SRCS "src/camera_driver.c"
    INCLUDE_DIRS "include"
    REQUIRES
        esp_camera
        esp_log
        driver
)
