#include <Disco_LED.h>
#include <Disco_Clock.h>
#include <FreeRTOS.h>
#include <task.h>

#define LED1_TASK_STACK_SIZE					(configMINIMAL_STACK_SIZE)
#define LED2_TASK_STACK_SIZE					(configMINIMAL_STACK_SIZE)

#define LED1_TASK_PRIORITY						(tskIDLE_PRIORITY + 1)
#define LED2_TASK_PRIORITY						(tskIDLE_PRIORITY + 1)

void LED1_TASK(void *pvParameters);
void LED2_TASK(void *pvParameters);

int main(void)
{
	Disco_Clock_Init();
	Disco_Led_Init(LED_ALL);
	xTaskCreate(LED1_TASK, 	"LED1", LED1_TASK_STACK_SIZE, NULL, LED1_TASK_PRIORITY, NULL);	
	xTaskCreate(LED2_TASK, 	"LED2", LED2_TASK_STACK_SIZE, NULL, LED2_TASK_PRIORITY, NULL);	
	vTaskStartScheduler();
	while(1);
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
