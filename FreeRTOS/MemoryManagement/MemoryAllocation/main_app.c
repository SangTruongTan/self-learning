/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>

/* FreeRTOS submodule includes. */
#include "stream_buffer.h" /* Include this file for this example. */
#include <task.h>

/* Primitive libraries. */
#include <string.h>
#include <stdio.h>

/* The task functions. */
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

/* Define the strings that will be passed in as the task parameters.
   They are to be printed to the console when tasks are running. */
const char *pcTextForTask1 = "Task 1 is running\r\n";
const char *pcTextForTask2 = "Task 2 is running\r\n";

/* The number of bytes of storage in the buffer. */
#define BUFFER_LENGTH_BYTES ((size_t)100)
StreamBufferHandle_t xStreamBuffer;

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

    const size_t xTriggerLevel = 10;
    size_t xBytesSent;
    char cStringToSend[30];
    int32_t iCounter = 0;

    /* Create a stream buffer in the heap memory. */
    xStreamBuffer = xStreamBufferCreate(BUFFER_LENGTH_BYTES, xTriggerLevel);

    if (xStreamBuffer == NULL) {
        /* There was not enough heap memory space available to create the stream
        buffer. */
        configASSERT(pdFALSE);
    }

    /* As per most tasks, this task is implemented in an infinite loop. */
    for (;;) {
        vTaskDelay((TickType_t)500);
        /* Print out the string parameter of this task. */
        printf(pcTaskString);

        memset(cStringToSend, 0x00, sizeof(cStringToSend));
        sprintf(cStringToSend, "%s => %d", "Hello, IoT", (int)iCounter);

        /* Send the string to the stream buffer. Return immediately if there is
        not enough space in the buffer. */
        xBytesSent = xStreamBufferSend(xStreamBuffer, (void *)cStringToSend,
                                       strlen(cStringToSend), 0);
        if (xBytesSent != strlen(cStringToSend)) {
            /* The entire string could not be added to the stream buffer because
            there was not enough free space in the buffer, but xBytesSent bytes
            were sent. Could try again to send the remaining bytes. */
            configASSERT(pdFALSE);
        }
        iCounter++;
    }
}
/*-----------------------------------------------------------*/
void vTask2(void *pvParameters) {
    char *pcTaskString;
    pcTaskString = (char *)pvParameters;

    size_t xReceivedBytes;
    char *pucBuffer;

    /* Create the buffer from the heap. */
    pucBuffer = (char *)pvPortMalloc(BUFFER_LENGTH_BYTES);
    configASSERT(pucBuffer);

    /* As per most tasks, this task is implemented in an infinite loop. */
    for (;;) {
        vTaskDelay((TickType_t)500);
        /* Print out the name of this task. */
        printf(pcTaskString);

        /* Receive up to another BUFFER_LENGTH_BYTES bytes from the stream
        buffer. Wait in the Blocked state (not using any CPU processing time)
        indefinitely till the full number of BUFFER_LENGTH_BYTES bytes to be
        available. */
        xReceivedBytes = xStreamBufferReceive(xStreamBuffer, (void *)pucBuffer,
                                              BUFFER_LENGTH_BYTES,
                                              portMAX_DELAY);
        if (xReceivedBytes > 0) {
            /* A pucBuffer contains another xReceivedBytes bytes of data, which
            can be processed here... */
            printf((char *)"Buffer received: ");
            printf((char *)pucBuffer);
            printf((char *)"\nNum. of bytes:%u\n", xReceivedBytes);
        }
    }
}
