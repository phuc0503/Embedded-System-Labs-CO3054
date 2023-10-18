#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#define BUTTON_PIN    0
#define DEBOUNCE_TIME 50

static uint32_t current_ms()
{
    // get current time (ms)
    return esp_timer_get_time() / 1000;
}

//Task 1: A cyclic task printing student ID every second.
void printStudentID(void *param)
{
    while(1)
    {
        printf("%lld s: 2011867\n", esp_timer_get_time() / 1000000);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
//Task 2: An acyclic task polling a button and print "ESP32" every when the button is pressed.
void printESP32(void *param)
{
    //Set up pin G0 as a GPIO INPUT
    esp_rom_gpio_pad_select_gpio(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    //initial variable
    int previousStableState = 1; //Using after DEBOUNCE_TIME
    int previousState = 1; //Every times
    int currentState;

    uint32_t lastDebounceTime = 0; // the last time input pin was toggled

    while(1)
    {
       // read the state of the button:
        currentState = gpio_get_level(GPIO_NUM_17);
        // If the button changed, due to noise or pressing:
        if (currentState != previousState)
        {
            lastDebounceTime = current_ms();
            previousState = currentState;
        }
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:
        if ((current_ms() - lastDebounceTime) > DEBOUNCE_TIME)
        {
            // if the button state has changed
            if (previousStableState == 1 && currentState == 0)
            {
                printf("ESP32\n");
            }

            previousStableState = currentState;
        }
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    
    vTaskDelete(NULL);
}

void app_main(void)
{
    xTaskCreate(printStudentID, "print student ID", 2048, NULL, 3, NULL);
    xTaskCreate(printESP32, "print ESP32", 2048, NULL, 4, NULL);
}
