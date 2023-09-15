/* FreeRTOS kernel include. */
#include <FreeRTOS.h>

/* FreeRTOS kernel modules include. */
#include "semphr.h" /* Semaphore include file */
#include <task.h>

/* Primitive libraries. */
#include <stdio.h>
#include <string.h>

/* The task functions. */
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

/* Define the strings that will be passed in as the task parameters.
   They are to be printed to the console when tasks are running. */
const char *pcTextForTask1 = "Task 1 is running\r\n";
const char *pcTextForTask2 = "Task 2 is running\r\n";

/* Define the string as the shared data accessed by Task 1 and Task 2. */
static char *sharedData = "It's the shared data.";

/* Create the semaphore handle. */
SemaphoreHandle_t xSemaphore1 = NULL;

/*-----------------------------------------------------------*/

int main_app(void) {
    /* Create tasks. */
    xTaskCreate(vTask1, "Task 1", 100, (void *)pcTextForTask1, 1, NULL);
    xTaskCreate(vTask2, "Task 2", 100, (void *)pcTextForTask2, 2, NULL);

    /* Start the scheduler to start the tasks executing. */
    vTaskStartScheduler();
    return (0);
}
/*-----------------------------------------------------------*/

void vTask1(void *pvParameters) {
    char *pcTaskString;
    pcTaskString = (char *)pvParameters;

    TickType_t xLastWakeTime;

    /* The xLastWakeTime variable needs to be initialized with the current tick
    count.  Note that this is the only time we access this variable.  From this
    point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
    API function. */
    xLastWakeTime = xTaskGetTickCount();

    /* Create a sempahore for mutex. */
    xSemaphore1 = xSemaphoreCreateMutex();

    /* Check if the semaphore is created successfully. */
    if (xSemaphore1 == NULL) {
        configASSERT(pdFALSE);
    }
    /* As per most tasks, this task is implemented in an infinite loop. */
    for (;;) {
        /* Print out the name of this task. */
        printf(pcTaskString);

        if (xSemaphore1 != NULL) {
            /* Obtain the semaphore without blocking the task if the semaphore
               isn't immediately available. */
            if (xSemaphoreTake(xSemaphore1, (TickType_t)0)) {
                /* Now the task can access the shared resource. Do something
                 * here. */
                sharedData = (char *)"Shared data changed by Task1";
                if (strcmp(sharedData, "Shared data changed by Task1") != 0) {
                    configASSERT(pdFALSE);
                }

                {
                    printf("%s\r\n", sharedData);
                    fflush(stdout);
                }

                /* Delay for a period of time. */
                vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(300UL));

                /* When finished accessing the shared resource, free the
                   semaphore. */
                if (xSemaphoreGive(xSemaphore1) != pdTRUE) {
                    configASSERT(pdFALSE);
                }
            }
        }
    }
}

/*-----------------------------------------------------------*/
void vTask2(void *pvParameters) {
    char *pcTaskString;
    pcTaskString = (char *)pvParameters;

    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();

    printf(pcTaskString);

    /* As per most tasks, this task is implemented in an infinite loop. */
    for (;;) {
        sharedData = (char *)"Shared data changed by Task2.";
        {
            printf("%s\r\n", sharedData);
            fflush(stdout);
        }
        /* Delay for a period of time. */
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(500UL));
    }
}
