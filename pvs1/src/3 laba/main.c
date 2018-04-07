#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_adc.h>
#include "main.h"

#define SWITCH_DELAY 500000

void leds_init() 
{
		GPIO_InitTypeDef  GPIO_InitStructure;
		/* Enable peripheral clock for GPIOD port */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

		/* Init leds */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
		GPIO_Init(GPIOE, &GPIO_InitStructure);
  
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
  
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
}
void adc_init() 
{
 
        ADC_InitTypeDef ADC_InitStructure;
        ADC_StructInit(&ADC_InitStructure);
        ADC_CommonInitTypeDef ADC_CommonInitStructure;
 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
 
        ADC_InitStructure.ADC_ScanConvMode = DISABLE;
        ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
        ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
        ADC_InitStructure.ADC_NbrOfConversion = 1;
        ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b;
        ADC_Init(ADC1, &ADC_InitStructure);
 
        ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_3Cycles);
 
        ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
        ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
        ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
        ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
        ADC_CommonInit(&ADC_CommonInitStructure);
 
        ADC_Cmd(ADC1, ENABLE);
 }
 
 void button_init()
 {
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
 
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
 
      GPIO_Init(GPIOA, &GPIO_InitStructure);
 
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
 
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
 
      GPIO_Init(GPIOA, &GPIO_InitStructure);
 
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
 }

int main()
{
	
     leds_init();  // инициализация светодиодов
	 button_init(); // инициализация кнопки
	 adc_init();  // инициализация ацп
     GPIO_SetBits(GPIOA, GPIO_Pin_5);
 
 
     ADC_TempSensorVrefintCmd(ENABLE);  // разрешаем преобразование
      do 
	  {
         ADC_SoftwareStartConv(ADC1);
		 while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
         uint16_t adc_result = ADC_GetConversionValue(ADC1);
         GPIO_ResetBits(GPIOE, GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15);		 // сбрасываем состояние диодов
         GPIO_ResetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15);
		 GPIO_ResetBits(GPIOD, GPIO_Pin_9 | GPIO_Pin_11);
		 
		  if (adc_result >= 1 && adc_result <= 30) 
		  {
              GPIO_SetBits(GPIOE, GPIO_Pin_11);
		  }
          if (adc_result > 30 && adc_result <= 60) 
		  {
              GPIO_SetBits(GPIOE, GPIO_Pin_11 | GPIO_Pin_13);
          }
		  if (adc_result > 60 && adc_result <= 90)
		  {
              GPIO_SetBits(GPIOE, GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15);
          }
		  if (adc_result > 90 && adc_result <= 120) 
		  {
              GPIO_SetBits(GPIOE, GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15);
			  GPIO_SetBits(GPIOB, GPIO_Pin_11);
 
          } 
		  if (adc_result > 120 && adc_result <= 150)
		  {
              GPIO_SetBits(GPIOE, GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15);
			  GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_13 );
 
          }
		  if (adc_result > 150 && adc_result <= 180) 
		  {
              GPIO_SetBits(GPIOE, GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15);
			  GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15 );
		  }
		  if (adc_result > 180 && adc_result <= 210) 
		  {
              GPIO_SetBits(GPIOE, GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15);
			  GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15 );
			  GPIO_SetBits(GPIOD, GPIO_Pin_9);
          }
		  if (adc_result > 210) 
		  {
              GPIO_SetBits(GPIOE, GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15);
			  GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15 );
			  GPIO_SetBits(GPIOD, GPIO_Pin_9 | GPIO_Pin_11);
          }
		 }while (1);
}
