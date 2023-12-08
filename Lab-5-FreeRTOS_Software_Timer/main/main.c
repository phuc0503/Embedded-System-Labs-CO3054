#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "FreeRTOSConfig.h"
#include "string.h"
#include "esp_timer.h"

#define NUM_TIMERS 2

/* An array to hold handles to the created timers. */
TimerHandle_t xTimers[ NUM_TIMERS ];

/* Define a callback function that will be used by multiple timer
instances.  The callback function prints ahihi if timer1, ihaha if timer2 and count the number
of times the associated timer expires, and stop the timer once the
timer1 has expired 10 times and timer2 has expired 5 times.  The count is saved as the ID of the
timer. */
void vTimerCallback( TimerHandle_t xTimer )
{
    uint32_t ulCount;
    const char *pcTimerName1 = "Timer1";
    const char *pcTimerName2 = "Timer2";

    /* Optionally do something if the pxTimer parameter is NULL. */
    configASSERT( xTimer );

    /* The number of times this timer has expired is saved as the
    timer's ID.  Obtain the count. */
    ulCount = (uint32_t) pvTimerGetTimerID(xTimer);

    /* Increment the count, then test to see if the timer has expired yet. */
    ulCount++;

    if(strcmp(pcTimerGetName(xTimer), pcTimerName1) == 0) {
        if(ulCount > 10) {
            xTimerStop(xTimer, 0);
        } else {
            vTimerSetTimerID(xTimer, (void *)ulCount);
            printf("%lld s: ahihi\n", esp_timer_get_time()/1000000);
        }
    } else if(strcmp(pcTimerGetName(xTimer), pcTimerName2) == 0) {
        if(ulCount > 5) {
            xTimerStop(xTimer, 0);
        } else {
            vTimerSetTimerID(xTimer, (void *)ulCount);
            printf("%lld s: ihaha\n", esp_timer_get_time()/1000000);
        }
    }
}

void app_main( void )
{
    /* Create then start some timers.  Starting the timers before
    the RTOS scheduler has been started means the timers will start
    running immediately that the RTOS scheduler starts. */
    xTimers[0] = xTimerCreate("Timer1", pdMS_TO_TICKS(2000), pdTRUE, (void*)0, vTimerCallback);
    xTimers[1] = xTimerCreate("Timer2", pdMS_TO_TICKS(3000), pdTRUE, (void*)0, vTimerCallback);

    /* Start timer */
    xTimerStart(xTimers[0], 0);
    xTimerStart(xTimers[1], 0);
}