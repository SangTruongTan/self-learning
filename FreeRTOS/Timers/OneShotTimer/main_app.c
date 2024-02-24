/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>

/* FreeRTOS submodule includes. */
#include <task.h>
#include <timers.h> /* Include this file to use timer API functions. */

/* Primitive libraries. */
#include <stdio.h>
#include <string.h>

/* Defined one-shot timer period in ticks. */
#define TIMER_PERIOD ((TickType_t)800)

/* The functions `vTask1` and `vTask2` are task functions that will be executed
 * by separate tasks in the FreeRTOS scheduler. */
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

/* Define the strings that will be passed in as the task parameters. They are to
 * be printed to the console when tasks are running. */
const char *pcTextForTask1 = "Task 1 is running\r\n";
const char *pcTextForTask2 = "Task 2 is running\r\n";

/* The one-shot timer is configured to use a callback function that increments
 * ucTimerCounter each time it's called. */
static TimerHandle_t xOneShotTimer = NULL;               /* Timer handle */
static void timerCallback(TimerHandle_t pxExpiredTimer); /* Timer Callback
                                                          * function. */
static uint8_t ucTimerCounter = (uint8_t)0;              /* Timer counters. */

/*-----------------------------------------------------------*/

int main_app(void) {
    /* Create tasks. */
    xTaskCreate(vTask1, "Task 1", 100, (void *)pcTextForTask1, 2, NULL);
    xTaskCreate(vTask2, "Task 2", 100, (void *)pcTextForTask2, 1, NULL);

    /* Start the scheduler to start the tasks executing. */
    vTaskStartScheduler();
    return (0);
}
/*-----------------------------------------------------------*/

void vTask1(void *pvParameters) {
    char *pcTaskString;
    pcTaskString = (char *)pvParameters;

    /* As per most tasks, this task is implemented in an infinite loop. */
    for (;;) {
        /* Print out the string parameter of this task. */
        printf(pcTaskString);

        vTaskDelay((TickType_t)500);
    }
}
/*-----------------------------------------------------------*/
void vTask2(void *pvParameters) {
    char *pcTaskString;
    pcTaskString = (char *)pvParameters;

    /* Create a one-shot timer. */
    xOneShotTimer = xTimerCreate(
        "Oneshot Timer", /* Text name to facilitate debugging. */
        TIMER_PERIOD,    /* The period for the timer. */
        pdFALSE,         /* Don't auto-reload - hence  a one shot timer. */
        (void *)NULL, /* Timer identifier. Initialise to 0, then increment each
                         time it is called. */
        timerCallback); /* The callback to be called when the timer expires. */
    if (xOneShotTimer == NULL) {
        configASSERT(pdFAIL);
    }

    /* Start the one shot timer and check that it reports its state correctly.
     */
    xTimerStart(xOneShotTimer, (TickType_t)0);
    if (xTimerIsTimerActive(xOneShotTimer) == pdFALSE) {
        configASSERT(pdFAIL);
    }
    /* As per most tasks, this task is implemented in an infinite loop. */
    for (;;) {
        /* Print out the string parameter of the task and timer counter. */
        printf((char *)"%s ==> Counter:%hu\n", pcTaskString, ucTimerCounter);

        /* Delay the task for 500 ticks. */
        vTaskDelay((TickType_t)500);

    }
}

static void timerCallback(TimerHandle_t pxExpiredTimer) {
    (void) pxExpiredTimer;
    printf((char *)"Timer callback is called!\n");
    ucTimerCounter++;
}
