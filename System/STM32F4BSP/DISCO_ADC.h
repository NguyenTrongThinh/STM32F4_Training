#ifndef __DISCO_ADC_H__
	#define __DISCO_ADC_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_dma.h>	
#include <stm32f4xx_adc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_syscfg.h>

typedef struct ADC_Value_T
{
	uint16_t ADC_Value_1;
	uint16_t ADC_Value_2;
}ADC_MultiTypeDef;

void DISCO_ADC_Init(void);
ADC_MultiTypeDef DISCO_ADC_GetValue(void);
	
#ifdef __cplusplus
}
#endif
#endif /* __DISCO_CLOCK_H__ */
