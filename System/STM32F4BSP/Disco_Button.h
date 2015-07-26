#ifndef __DISCO_BUTTON_H__
	#define __DISCO_BUTTON_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_rcc.h>
#include "stm32f4xx_syscfg.h"
	
typedef enum
{
	PRESSED,
	RELEASE,
}BUTTON_STATUS;

void Disco_Button_Init(void);
BUTTON_STATUS Disco_Button_Get_Status(void);

		
#ifdef __cplusplus
}
#endif
#endif /* __DISCO_BUTTON_H__ */
