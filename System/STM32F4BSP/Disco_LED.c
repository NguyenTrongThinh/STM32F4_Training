#include "Disco_LED.h"

#define LED_PORT GPIOD

#define LED_D3_PIN GPIO_Pin_13
#define LED_D4_PIN GPIO_Pin_12
#define LED_D5_PIN GPIO_Pin_14
#define LED_D6_PIN GPIO_Pin_15


void Disco_Led_Init(DISCO_LED Led)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	switch(Led)
	{
		case LED_D3: 
			GPIO_InitStructure.GPIO_Pin = LED_D3_PIN;
			break;
		case LED_D4:
			GPIO_InitStructure.GPIO_Pin = LED_D4_PIN;
			break;
		case LED_D5:
			GPIO_InitStructure.GPIO_Pin = LED_D5_PIN;
			break;
		case LED_D6:
			GPIO_InitStructure.GPIO_Pin = LED_D6_PIN;
			break;
		case LED_ALL:
			GPIO_InitStructure.GPIO_Pin = LED_D3_PIN | LED_D4_PIN | LED_D5_PIN | LED_D6_PIN;
		break;
	}
	GPIO_Init(LED_PORT, &GPIO_InitStructure);
}
void Disco_Led_On(DISCO_LED Led)
{
	switch (Led)
	{
		case LED_D3: 
			GPIO_SetBits(LED_PORT, LED_D3_PIN);
			break;
		case LED_D4: 
			GPIO_SetBits(LED_PORT, LED_D4_PIN);
			break;
		case LED_D5: 
			GPIO_SetBits(LED_PORT, LED_D5_PIN);
			break;
		case LED_D6: 
			GPIO_SetBits(LED_PORT, LED_D6_PIN);
			break;
		case LED_ALL:
			GPIO_SetBits(LED_PORT, LED_D6_PIN | LED_D5_PIN | LED_D4_PIN | LED_D3_PIN);
			break;
	}
}
void Disco_Led_Off(DISCO_LED Led)
{
		switch (Led)
	{
		case LED_D3: 
			GPIO_ResetBits(LED_PORT, LED_D3_PIN);
			break;
		case LED_D4: 
			GPIO_ResetBits(LED_PORT, LED_D4_PIN);
			break;
		case LED_D5: 
			GPIO_ResetBits(LED_PORT, LED_D5_PIN);
			break;
		case LED_D6: 
			GPIO_ResetBits(LED_PORT, LED_D6_PIN);
			break;
		case LED_ALL:
			GPIO_ResetBits(LED_PORT, LED_D6_PIN | LED_D5_PIN | LED_D4_PIN | LED_D3_PIN);
			break;
	}
}
void Disco_Led_Toggle(DISCO_LED Led)
{
	static unsigned char mod = 0;
	mod = (mod + 1) % 2;
	if (mod)
		Disco_Led_On(Led);
	else
		Disco_Led_Off(Led);
}
