#include "main.h"

#define SWITCH_DELAY 500000

void it_init() 
{
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
    EXTI_InitTypeDef exti;  // структура для настроки
    exti.EXTI_Line = EXTI_Line0;    /// кнопка на линии 0
    exti.EXTI_Mode = EXTI_Mode_Interrupt;    // прерывание (а не событие)
    exti.EXTI_Trigger = EXTI_Trigger_Rising;  // срабатываем по переднему фронту импульса
    exti.EXTI_LineCmd = ENABLE;    /// вкл
 
    EXTI_Init(&exti);
 
    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = EXTI0_IRQn;  // указываем канал IRQ
    nvic.NVIC_IRQChannelPreemptionPriority = 2;  // приоритет канала ( 0 (самый приоритетный) - 15)
    nvic.NVIC_IRQChannelSubPriority = 2;  // приоритет подгруппы
    nvic.NVIC_IRQChannelCmd = ENABLE;
 
    NVIC_Init(&nvic);
}

void EXTI0_IRQHandler(void)
{
     /* нужно проверять состояние линии прерывания  */
    if (EXTI_GetITStatus(EXTI_Line0) != RESET){
		button_handler();
        EXTI_ClearITPendingBit(EXTI_Line0);  // сбрасываем флаг прерывания
    }
}

int blink_next(int led)
{
	int next_led;
	switch(led)
	{
		case 1: 
			GPIOD->BSRRH = 0xffff;
			LED1_GPIO_PORT->BSRRL = LED1_PIN;
			next_led = led + 1;
			break;
		case 2:
			GPIOD->BSRRH = 0xffff;
			LED2_GPIO_PORT->BSRRL = LED2_PIN;
			next_led = led + 1;
			break;
		case 3: 
			GPIOD->BSRRH = 0xffff;
			LED3_GPIO_PORT->BSRRL = LED3_PIN;
			next_led = led + 1;
			break;
		case 4: 
			GPIOD->BSRRH = 0xffff;
			LED4_GPIO_PORT->BSRRL = LED4_PIN;
			next_led = 1;
			break;
	}
	return next_led;
}

int blink_prev(int led)
{
	int next_led;
	switch(led)
	{
		case 1: 
			GPIOD->BSRRH = 0xffff;
			LED1_GPIO_PORT->BSRRL = LED1_PIN;
			next_led = 4;
			break;
		case 2:
			GPIOD->BSRRH = 0xffff;
			LED2_GPIO_PORT->BSRRL = LED2_PIN;
			next_led = led - 1;
			break;
		case 3: 
			GPIOD->BSRRH = 0xffff;
			LED3_GPIO_PORT->BSRRL = LED3_PIN;
			next_led = led - 1;
			break;
		case 4: 
			GPIOD->BSRRH = 0xffff;
			LED4_GPIO_PORT->BSRRL = LED4_PIN;
			next_led = led - 1;
			break;
	}
	return next_led;
}	

int g_button_state = 0;
void button_handler()
{
	int i;
	
	for (i=0; i < SWITCH_DELAY/100; i++)
	{
	    /* empty cycle */
	}
	
	if (g_button_state)
	{
		g_button_state = 0;
	}
	else
	{
	  g_button_state = 1;	
	}
}

typedef enum led_direction_e
{
  FORWARD,
  REVERSE,
} led_direction_t;

int main(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  led_direction_t direction = FORWARD;
  int next_led = 1;
  
#if defined USE_EXT_LEDS
  
  /* Enable peripheral clock for GPIOD port */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Init leds */
  GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = LED4_PIN | LED5_PIN | LED6_PIN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = LED7_PIN | LED8_PIN;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

#else
	 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  // init RCC wakeup button
  RCC_AHB1PeriphClockCmd(WAKEUP_BUTTON_GPIO_CLK, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = WAKEUP_BUTTON_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(WAKEUP_BUTTON_GPIO_PORT, &GPIO_InitStructure);
#endif
	
  GPIOD->BSRRH = 0xffff;

  it_init();
  
  while (1)
  {
	int i;
	
	if (g_button_state)
    //if (GPIO_ReadInputDataBit(WAKEUP_BUTTON_GPIO_PORT, WAKEUP_BUTTON_PIN))
	{
		next_led = blink_next(next_led);
	}
	else
	{
		next_led = blink_prev(next_led);
	}
	
	for (i=0; i < SWITCH_DELAY; i++)
	{
	    /* empty cycle */
	}
	
  }
}
     