/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>
#include <task.h>

/* Primitive libraries. */
#include <stdio.h>
#include <string.h>

/* The task functions. */
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

/* Handles for the tasks create by main_app(). */
static TaskHandle_t xTask1 = NULL, xTask2 = NULL;

/* Define the strings that will be passed in as the task parameters.
   They are to be printed to the console when tasks are running. */
const char *pcTextForTask1 = "Task 1 is running\r\n";
const char *pcTextForTask2 = "Task 2 is running\r\n";

/*-----------------------------------------------------------*/

int main_app(void) {
    /* Create tasks. */
    xTaskCreate(vTask1, "Task 1", 100, (void *)pcTextForTask1, 1, &xTask1);
    xTaskCreate(vTask2, "Task 2", 100, (void *)pcTextForTask2, 2, &xTask2);

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
        vTaskDelay((TickType_t)500);
        /* Print out the name of thii task. */
        printf(pcTaskString);

        /* Send a notification to vTask2(), bringing it out of the Blocked
        state. */
        xTaskNotifyGive(xTask2);

        /* Block to wait for vTask2() to notify this task. */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
/*-----------------------------------------------------------*/
void vTask2(void *pvParameters) {
    char *pcTaskString;
    pcTaskString = (char *)pvParameters;

    /* As per most tasks, this task is implemented in an infinite loop. */
    for (;;) {
        vTaskDelay((TickType_t)500);

        /* Print out the name of this task. */
        printf(pcTaskString);

        /* Blocks to wait for vTask1() to notify this task. */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf((char *)"Task2 was notified!\n");

        /* Send a notification to vTask1(), bringing it out of the Blocked
        state. */
        xTaskNotifyGive(xTask1);
    }
}
