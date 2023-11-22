#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#define TASK1_PRIORITY 3
#define TASK2_PRIORITY 2
#define TASK3_PRIORITY 1

#define TASK1_STACK_SIZE 2048
#define TASK2_STACK_SIZE 1024
#define TASK3_STACK_SIZE 1024

SemaphoreHandle_t sem;

void task1(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(sem, portMAX_DELAY)) {
            printf("Task 1 is running...\n");
            xSemaphoreGive(sem);
        }
        taskYIELD(); // Cooperative yield
    }
}

void task2(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(sem, portMAX_DELAY)) {
            printf("Task 2 is running...\n");
            xSemaphoreGive(sem);
        }
        taskYIELD(); // Cooperative yield
    }
}

void task3(void *pvParameters) {
    while (1) {
        printf("Task 3 is running...\n");
        taskYIELD(); // Cooperative yield
    }
}

void interrupt_handler(void *arg) {
    // Handle interrupt, give semaphore
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(sem, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken == pdTRUE) {
        portYIELD_FROM_ISR();
    }
}

void setup_interrupt() {
    // Configure GPIO pin for interrupt
    const gpio_num_t interrupt_pin = GPIO_NUM_2;  // Change this to your desired GPIO pin
    gpio_config_t gpio_conf = {
        .pin_bit_mask = (1ULL << interrupt_pin),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_ANYEDGE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE
    };
    gpio_config(&gpio_conf);

    // Install ISR service with default configuration
    gpio_install_isr_service(0);
    // Hook ISR handler to the ISR service
    gpio_isr_handler_add(interrupt_pin, interrupt_handler, NULL);
}

void app_main() {
    sem = xSemaphoreCreateBinary();

    xTaskCreatePinnedToCore(task1, "Task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, NULL, 0);
    xTaskCreatePinnedToCore(task2, "Task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, NULL, 0);
    xTaskCreatePinnedToCore(task3, "Task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, NULL, 0);

    // Set up and enable the interrupt
    setup_interrupt();
}
