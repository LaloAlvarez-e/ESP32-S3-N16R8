idf_component_register(
    SRCS "src/http_server.c"
    INCLUDE_DIRS "include"
    REQUIRES
        esp_http_server
        esp_wifi
        esp_event
        esp_netif
        nvs_flash
        esp_log
        camera_driver
)
