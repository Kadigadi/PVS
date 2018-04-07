#include "main.h"
#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>
#include <misc.h>

#define SWITCH_DELAY 500000

int next_led = 1;

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

void TIM6_DAC_IRQHandler(){
 
  /* Так как этот обработчик вызывается и для ЦАП, нужно проверять,
   * произошло ли прерывание по переполнению счётчика таймера TIM6.
   */
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
    /* Очищаем бит обрабатываемого прерывания */
      TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
      next_led = blink_next(next_led);
    }
}
void init_timer(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); // включаем тактирование таймера
   /* Другие параметры структуры TIM_TimeBaseInitTypeDef
   * не имеют смысла для базовых таймеров.
   */
 
    TIM_TimeBaseInitTypeDef base_timer;
    TIM_TimeBaseStructInit(&base_timer);
  /* Делитель учитывается как TIM_Prescaler + 1, поэтому отнимаем 1 */
    base_timer.TIM_Prescaler = 24000 - 1; // делитель 24000
    base_timer.TIM_Period = 3000; //период 1000 импульсов
    TIM_TimeBaseInit(TIM6, &base_timer);
 
  /* Разрешаем прерывание по обновлению (в данном случае -
   * по переполнению) счётчика таймера TIM6.
   */
 
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM6, ENABLE);  // Включаем таймер
 
  /* Разрешаем обработку прерывания по переполнению счётчика
   * таймера TIM6. это же прерывание
   * отвечает и за опустошение ЦАП.
   */
 
    NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

int main()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
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

  init_timer();
  do {
  } while(1);
}
     