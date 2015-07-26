#include <Disco_LED.h>
#include <Disco_Clock.h>
#include <DISCO_USART.h>
#include <DISCO_Button.h>
#include <FreeRTOS.h>
#include <task.h>
#include <Queue.h>
#include <semphr.h>

#define LED1_TASK_STACK_SIZE					(configMINIMAL_STACK_SIZE)
#define LED2_TASK_STACK_SIZE					(configMINIMAL_STACK_SIZE)
#define LED3_TASK_STACK_SIZE					(configMINIMAL_STACK_SIZE)
#define USART_TASK_STACK_SIZE					(configMINIMAL_STACK_SIZE)

#define LED1_TASK_PRIORITY						(tskIDLE_PRIORITY + 1)
#define LED2_TASK_PRIORITY						(tskIDLE_PRIORITY + 1)
#define LED3_TASK_PRIORITY						(tskIDLE_PRIORITY + 1)
#define USART_TASK_PRIORITY						(tskIDLE_PRIORITY + 1)


xQueueHandle USART_Queue;

xSemaphoreHandle USART_Semphr;
xSemaphoreHandle BUTTON_Semphr;

typedef enum{BUT_ID, USART_ID} SYSTEM_ID;

typedef struct DataFlow
{
	SYSTEM_ID ID;
	unsigned char Value;
}Data_TypeDef;


void LED1_TASK(void *pvParameters);
void LED2_TASK(void *pvParameters);
void LED3_TASK(void *pvParameters);
void USART_TASK(void *pvParameters);

int main(void)
{
	Disco_Clock_Init();
	Disco_Led_Init(LED_ALL);
	DISCO_USART_Init();
	Disco_Button_Init();
	USART_Queue = xQueueCreate(200, sizeof(Data_TypeDef));
	USART_Semphr = xSemaphoreCreateCounting(200, 0);
	BUTTON_Semphr = xSemaphoreCreateCounting(20, 0);
	if (USART_Queue != NULL && USART_Semphr != NULL && BUTTON_Semphr != NULL)
	{
		xTaskCreate(LED1_TASK, 	"LED1", LED1_TASK_STACK_SIZE, NULL, LED1_TASK_PRIORITY, NULL);	
		xTaskCreate(LED2_TASK, 	"LED2", LED2_TASK_STACK_SIZE, NULL, LED2_TASK_PRIORITY, NULL);	
		xTaskCreate(LED3_TASK, 	"LED3", LED3_TASK_STACK_SIZE, NULL, LED3_TASK_PRIORITY, NULL);	
		xTaskCreate(USART_TASK, 	"USART", USART_TASK_STACK_SIZE, NULL, USART_TASK_PRIORITY, NULL);	
		vTaskStartScheduler();
	}
	while(1);
}

void LED3_TASK(void *pvParameters)
{
	while(1)
	{
		xSemaphoreTake(BUTTON_Semphr, portMAX_DELAY);
		Disco_Led_Toggle(LED_D6);
	}
}
void USART_TASK(void *pvParameters)
{
	portBASE_TYPE xStatus;
	Data_TypeDef Data;
	while(1)
	{
		xSemaphoreTake(USART_Semphr, portMAX_DELAY);
		if (uxQueueMessagesWaiting(USART_Queue) != NULL)
		{
			xStatus = xQueueReceive(USART_Queue, &Data, 1);
			if (xStatus == pdPASS)
			{
				if (Data.ID == USART_ID)
				{
					printf("%c", Data.Value);
				}
			}
		}
	}
}
void LED1_TASK(void *pvParameters)
{
	while(1)
	{
		Disco_Led_Toggle(LED_D4);
		vTaskDelay(50);
	}
}
void LED2_TASK(void *pvParameters)
{
	while(1)
	{
		Disco_Led_Toggle(LED_D5);
		vTaskDelay(200);
	}
}
void USART1_IRQHandler(void)
{
	static Data_TypeDef Data;
	static portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
		Data.ID = USART_ID;
		Data.Value = USART_ReceiveData(USART1);
		xQueueSendToBackFromISR(USART_Queue, &Data, &xHigherPriorityTaskWoken);
		xSemaphoreGiveFromISR(USART_Semphr, &xHigherPriorityTaskWoken);
	}
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
void EXTI0_IRQHandler(void)
{
	static portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line0);
		xSemaphoreGiveFromISR(BUTTON_Semphr, &xHigherPriorityTaskWoken);
  }
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

