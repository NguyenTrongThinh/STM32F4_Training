#ifndef __DISCO_USART_H__
	#define __DISCO_USART_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>
#include <stdio.h>
	

void DISCO_USART_Init(void);	
void USART_puts(USART_TypeDef* USARTx, volatile char *s);
	
#ifdef __cplusplus
}
#endif
#endif /* __DISCO_USART_H__ */
