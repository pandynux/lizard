#include "esp_log.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
static const char *TAG = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "Project Initialized!");

    // Your application code goes here.
    // For example, initialize Wi-Fi, Bluetooth, or other components.

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
