/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>
#include <task.h>

/* Primitive libraries. */
#include <stdio.h>
#include <string.h>

/* This is the interrupt that should execute whenever taskYIELD()/portYIELD() is called. */
// #undef portYIELD
// #define portYIELD() vPortGenerateSimulatedInterrupt(portINTERRUPT_YIELD)
// #define portINTERRUPT_YIELD 2

/* The task functions. */
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

/* Define the strings that will be passed in as the task parameters.
   They are to be printed to the console when tasks are running. */
const char *pcTextForTask1 = "Task 1 is running\r\n";
const char *pcTextForTask2 = "Task 2 is running\r\n";

/* Define the string as the shared data accessed by Task 1 and Task 2 */
static char *sharedData = "It's the shared data.";

/*-----------------------------------------------------------*/

int main_app(void) {
   /* Create tasks. */
   xTaskCreate(vTask1, "Task 1", 100, (void *)pcTextForTask1, 1, NULL);
   xTaskCreate(vTask2, "Task 2", 100, (void *)pcTextForTask2, 2, NULL);

   /* Start the scheduler to start the tasks executing. */
   vTaskStartScheduler();
   return(0);
}
/*-----------------------------------------------------------*/

void vTask1(void *pvParameters) {
   TickType_t xLastWakeTime;
   const TickType_t xDelay300ms = pdMS_TO_TICKS(300UL);
   char *pcTaskString;
   pcTaskString = (char *)pvParameters;

   /* The xLastWakeTime variable needs to be initialized with the current tick count. Note that this is the only time we access this variable. From this point on xLastWakeTime is managed automaticall by the vTaskDelayUntil() API function. */
   xLastWakeTime = xTaskGetTickCount();

   /* As per most tasks, this task is implemented in an infinite loop. */
   for(;;) {
      /* Print out the string parameter of this task. */
      printf(pcTaskString);

      /* Enter Critical */
      taskENTER_CRITICAL();
      /* Execute the code that requires the critical section here. */
      sharedData = (char *) "Shared data changed by Task1";
      if (strcmp(sharedData, "Shared data changed by Task1") != 0) {
         configASSERT(pdFALSE);
      }
      {
         printf("%s\r\n", sharedData);
         fflush(stdout);
      }

      /* Delay for a period of time. */
      vTaskDelayUntil(&xLastWakeTime, xDelay300ms);

      if (strcmp(sharedData, "Shared data changed by Task1") != 0) {
         configASSERT(pdFALSE);
      }

      /* Exit Critical */
      taskEXIT_CRITICAL();

   }
}
/*-----------------------------------------------------------*/
void vTask2(void *pvParameters) {
   TickType_t xLastWakeTime;
   const TickType_t xDelay500ms = pdMS_TO_TICKS(500UL);
   char *pcTaskString;
   pcTaskString = (char *)pvParameters;

   xLastWakeTime = xTaskGetTickCount();

   /* As per most tasks, this task is implemented in an infinite loop. */
   for(;;) {
      /* Print out the string parameter of this task. */
      printf(pcTaskString);

      sharedData = (char *) "Shared data changed by Task2";
      {
         printf("%s\r\n", sharedData);
         fflush(stdout);
      }

      /* Delay for a period of time. */
      vTaskDelayUntil(&xLastWakeTime, xDelay500ms);
   }
}