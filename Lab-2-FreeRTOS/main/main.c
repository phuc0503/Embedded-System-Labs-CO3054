#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#define LED_PIN       0
#define BUTTON_PIN    17
#define DEBOUNCE_TIME 50

// get current time (ms)
static uint32_t current_ms()
{
    return esp_timer_get_time() / 1000;
}

// define GPIO
void define_IO(int GPIO_Pin, char direction)
{
    esp_rom_gpio_pad_select_gpio(GPIO_Pin);
    gpio_set_direction(GPIO_Pin, direction);
}

//Task 1: A cyclic task printing student ID every second.
int led_state = 1;
void printStudentID(void *param)
{
    //Set up LED_PIN as an GPIO OUTPUT
    //We will use this LED to verify whether task 1 is running correctly or not 
    define_IO(LED_PIN, GPIO_MODE_OUTPUT);
    while(1)
    {
        gpio_set_level(LED_PIN, led_state);
        printf("%lld s: 2011867    2012103\n", esp_timer_get_time() / 1000000);
        led_state = !led_state;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

//Task 2: An acyclic task polling a button and print "ESP32" every when the button is pressed.
void printESP32(void *param)
{
    //Set up BUTTON_PIN as a GPIO INPUT
    define_IO(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    //initial variable
    int previousStableState = 1; //Using after DEBOUNCE_TIME
    int previousState = 1; //Every times
    int currentState;

    uint32_t lastDebounceTime = 0; // the last time input pin was toggled

    while(1)
    {
       // read the state of the button:
        currentState = gpio_get_level(BUTTON_PIN);
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
