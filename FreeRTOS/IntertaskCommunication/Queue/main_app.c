/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>   /* Queue include file. */

/* Primitive libraries. */
#include <stdio.h>

/* The task functions. */
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

/* Handles for the tasks created in main_app(). */
static TaskHandle_t xTask1 = NULL, xTask2 = NULL;

/* Define the strings that will be passed in as the task parameters.
   They are to be printed to the console when tasks are running. */
const char *pcTextForTask1 = "Task 1 is running\r\n";
const char *pcTextForTask2 = "Task 2 is running\r\n";

/* Queue definitions. */
typedef struct Message { /* Define the data type that will be queued. */
   uint32_t ucId;
   char ucData[15];
} Message;

#define QUEUE_LENGTH 1
#define QUEUE_ITEM_SIZE sizeof( struct Message * )

QueueHandle_t xQueue1;

/*-----------------------------------------------------------*/

int main_app(void) {
   /* Create tasks. */
   xTaskCreate(vTask1, "Task 1", 100, (void *)pcTextForTask1, 1, &xTask1);
   xTaskCreate(vTask2, "Task 2", 100, (void *)pcTextForTask2, 2, &xTask2);

   /* Start the scheduler to start the tasks executing. */
   vTaskStartScheduler();
   return(0);
}
/*-----------------------------------------------------------*/

void vTask1(void *pvParameters) {
   char *pcTaskString;
   pcTaskString = (char *)pvParameters;

   uint32_t counter = 0;
   struct Message *pxMessage;

   xQueue1 = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
   if (xQueue1 == NULL) {
      printf("Failed to create queue");
      while(1);
   }
   /* As per most tasks, this task is implemented in an infinite loop. */
   for(;;) {
      vTaskDelay((TickType_t)500);
      /* Print out the string parameter of this task. */
      printf(pcTaskString);

      struct Message msg = {counter++, "Hello, IoT!"};
      pxMessage = &msg;
      xQueueSendToBack(xQueue1, (void *)&pxMessage, (TickType_t)0);
   }
}
/*-----------------------------------------------------------*/
void vTask2(void *pvParameters) {
   char *pcTaskString;
   pcTaskString = (char *)pvParameters;

   struct Message *xReceivedFromQueue1;
   /* As per most tasks, this task is implemented in an infinite loop. */
   for(;;) {
      vTaskDelay((TickType_t)200);

      /* Print out the string parameter of this task. */
      printf(pcTaskString);

      /* Receive and print data from Queue1 after a brief waiting for 10 ticks. */
      if (xQueueReceive(xQueue1, &(xReceivedFromQueue1), (TickType_t)10)) {
         printf((char *)"Received from Queue1: ");

         /* Print recieved data received. */
         printf("%s => %lu\n", (char *)((struct Message *)xReceivedFromQueue1)->ucData,
               ((struct Message *)xReceivedFromQueue1)->ucId);
      }
   }
}