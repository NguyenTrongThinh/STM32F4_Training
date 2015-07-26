#ifndef __DISCO_LED_H__
	#define __DISCO_LED_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>	

typedef enum
{
	LED_D3 = 0x00,
	LED_D4,
	LED_D5,
	LED_D6,
	LED_ALL,
}DISCO_LED;

void Disco_Led_Init(DISCO_LED Led);
void Disco_Led_On(DISCO_LED Led);
void Disco_Led_Off(DISCO_LED Led);
void Disco_Led_Toggle(DISCO_LED Led);
	
#ifdef __cplusplus
}
#endif
#endif /* __DISCO_CLOCK_H__ */
