#include "Disco_Clock.h"

void Disco_Clock_Init()
{	
	RCC_HSEConfig(RCC_HSE_ON);
	while(RCC_WaitForHSEStartUp() != SUCCESS);
	RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 4, 4);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);							
	RCC_PCLK2Config(RCC_HCLK_Div2);	
	RCC_PLLCmd(ENABLE);
	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
}
