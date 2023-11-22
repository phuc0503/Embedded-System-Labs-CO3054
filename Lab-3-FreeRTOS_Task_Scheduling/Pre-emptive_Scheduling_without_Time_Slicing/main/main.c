#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/projdefs.h"
#include "esp_freertos_hooks.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "FreeRTOSConfig.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"

volatile uint32_t ulTask1CycleCount = 0UL;

void task1(void *pvParameters)
{
    while(ulTask1CycleCount < 50)
    {
        printf("%lld ms : Task 1 is running\n", esp_timer_get_time() / 1000);
        printf("Task1 count: %ld\n", ulTask1CycleCount);
        ulTask1CycleCount++;
    }
    printf("Task 1 end at: %lld ms\n", esp_timer_get_time() / 1000);
    vTaskDelete(NULL);
}

void task2(void *pvParameters)
{
    while(1)
    {
        printf("%lld ms : Task 2 is running\n", esp_timer_get_time() / 1000);
    }
    vTaskDelete(NULL);
}

void task3(void *pvParameters)
{
    while(1)
    {
        printf("%lld ms : Task 3 is running\n", esp_timer_get_time() / 1000);
    }
    vTaskDelete(NULL);
}

void app_main() {
    xTaskCreate(task1, "Task1", 2048, NULL, 2, NULL);
    xTaskCreate(task2, "Task2", 2048, NULL, 1, NULL);
    xTaskCreate(task3, "Task3", 2048, NULL, 1, NULL);
}