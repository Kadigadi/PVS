/**
 * Definitions for STM32F4DISCOVERY_EVAL's Leds, push-buttons
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4DISC_EVAL_H
#define __STM32F4DISC_EVAL_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32_eval_legacy.h"

#if !defined (USE_STM32F4DISC_EVAL)
#define USE_STM32F4DISC_EVAL
#endif

typedef enum {
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3,
  LED5 = 4,
  LED6 = 5,
  LED7 = 6,
  LED8 = 7
} Led_TypeDef;


typedef enum {
  BTN1 = 0,
  BTN2 = 1,
  BTN3 = 2,
  BTN4 = 3,
  BTN5 = 4,
  BTN6 = 5,
  BTN7 = 6,
  BTN8 = 7
} Btn_TypeDef;



typedef struct led_s {
  const uint16_t    pin;
  GPIO_TypeDef*     port;
  const uint32_t    clk;
} led_t;


typedef enum {
  BUTTON_WAKEUP = 0,
  BUTTON_TAMPER = 1,
  BUTTON_KEY    = 2,
  BUTTON_RIGHT  = 3,
  BUTTON_LEFT   = 4,
  BUTTON_UP     = 5,
  BUTTON_DOWN   = 6,
  BUTTON_SEL    = 7
} Button_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

typedef enum
{
  JOY_NONE  = 0,
  JOY_SEL   = 1,
  JOY_DOWN  = 2,
  JOY_LEFT  = 3,
  JOY_RIGHT = 4,
  JOY_UP    = 5
} JOYState_TypeDef;


#ifndef USE_EXT_LEDS
/** Low-level LED constants  */
#define LEDn                             4

/* LED1 is a green LED, I/O PD12 */
#define LED1_PIN                         GPIO_Pin_12
#define LED1_GPIO_PORT                   GPIOD
#define LED1_GPIO_CLK                    RCC_AHB1Periph_GPIOD

/* LED2 is an orange LED, I/O PD13 */
#define LED2_PIN                         GPIO_Pin_13
#define LED2_GPIO_PORT                   GPIOD
#define LED2_GPIO_CLK                    RCC_AHB1Periph_GPIOD

/* LED3 is a red LED, I/O PD14 */
#define LED3_PIN                         GPIO_Pin_14
#define LED3_GPIO_PORT                   GPIOD
#define LED3_GPIO_CLK                    RCC_AHB1Periph_GPIOD

/* LED4 is a blue LED, I/O PD15 */
#define LED4_PIN                         GPIO_Pin_15
#define LED4_GPIO_PORT                   GPIOD
#define LED4_GPIO_CLK                    RCC_AHB1Periph_GPIOD

#else /* defined USE_EXT_LEDS */

/** Low-level LED constants  */
#define LEDn                             8

#define SMP
#if defined SMP

#define LED1_PIN                         GPIO_Pin_11
#define LED1_GPIO_PORT                   GPIOE
#define LED1_GPIO_CLK                    RCC_AHB1Periph_GPIOE

#define LED2_PIN                         GPIO_Pin_13
#define LED2_GPIO_PORT                   GPIOE
#define LED2_GPIO_CLK                    RCC_AHB1Periph_GPIOE

#define LED3_PIN                         GPIO_Pin_15
#define LED3_GPIO_PORT                   GPIOE
#define LED3_GPIO_CLK                    RCC_AHB1Periph_GPIOE

#define LED4_PIN                         GPIO_Pin_11
#define LED4_GPIO_PORT                   GPIOB
#define LED4_GPIO_CLK                    RCC_AHB1Periph_GPIOB

#define LED5_PIN                         GPIO_Pin_13
#define LED5_GPIO_PORT                   GPIOB
#define LED5_GPIO_CLK                    RCC_AHB1Periph_GPIOB

#define LED6_PIN                         GPIO_Pin_15
#define LED6_GPIO_PORT                   GPIOB
#define LED6_GPIO_CLK                    RCC_AHB1Periph_GPIOB

#define LED7_PIN                         GPIO_Pin_9
#define LED7_GPIO_PORT                   GPIOD
#define LED7_GPIO_CLK                    RCC_AHB1Periph_GPIOD

#define LED8_PIN                         GPIO_Pin_11
#define LED8_GPIO_PORT                   GPIOD
#define LED8_GPIO_CLK                    RCC_AHB1Periph_GPIOD

#else /* not defined SMP */

#define LED1_PIN                         GPIO_Pin_2
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK                    RCC_AHB1Periph_GPIOB

#define LED2_PIN                         GPIO_Pin_11
#define LED2_GPIO_PORT                   GPIOE
#define LED2_GPIO_CLK                    RCC_AHB1Periph_GPIOE

#define LED3_PIN                         GPIO_Pin_14
#define LED3_GPIO_PORT                   GPIOE
#define LED3_GPIO_CLK                    RCC_AHB1Periph_GPIOE

#define LED4_PIN                         GPIO_Pin_13
#define LED4_GPIO_PORT                   GPIOB
#define LED4_GPIO_CLK                    RCC_AHB1Periph_GPIOB

#define LED5_PIN                         GPIO_Pin_9
#define LED5_GPIO_PORT                   GPIOD
#define LED5_GPIO_CLK                    RCC_AHB1Periph_GPIOD

#define LED6_PIN                         GPIO_Pin_11
#define LED6_GPIO_PORT                   GPIOD
#define LED6_GPIO_CLK                    RCC_AHB1Periph_GPIOD

#define LED7_PIN                         GPIO_Pin_5
#define LED7_GPIO_PORT                   GPIOC
#define LED7_GPIO_CLK                    RCC_AHB1Periph_GPIOC

#define LED8_PIN                         GPIO_Pin_15
#define LED8_GPIO_PORT                   GPIOB
#define LED8_GPIO_CLK                    RCC_AHB1Periph_GPIOB
#endif
#endif /* ifndef USE_EXT_LEDS */


/** Low-level button constants */

#if defined SMP
#define BUTTONn                          6
#else
#define BUTTONn                          8
#endif

/**
 * Wakeup push-button
 */
#define WAKEUP_BUTTON_PIN                GPIO_Pin_0
#define WAKEUP_BUTTON_GPIO_PORT          GPIOA
#define WAKEUP_BUTTON_GPIO_CLK           RCC_AHB1Periph_GPIOA
#define WAKEUP_BUTTON_EXTI_LINE          EXTI_Line0
#define WAKEUP_BUTTON_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOA
#define WAKEUP_BUTTON_EXTI_PIN_SOURCE    EXTI_PinSource0
#define WAKEUP_BUTTON_EXTI_IRQn          EXTI0_IRQn

#if defined SMP
/* PC4 */
#define BTN1_PIN                         GPIO_Pin_4
#define BTN1_GPIO_PORT                   GPIOC
#define BTN1_GPIO_CLK                    RCC_AHB1Periph_GPIOC

/* PB2 */
#define BTN2_PIN                         GPIO_Pin_2
#define BTN2_GPIO_PORT                   GPIOB
#define BTN2_GPIO_CLK                    RCC_AHB1Periph_GPIOB

/* PE10 */
#define BTN3_PIN                         GPIO_Pin_10
#define BTN3_GPIO_PORT                   GPIOE
#define BTN3_GPIO_CLK                    RCC_AHB1Periph_GPIOE

/* PE14 */
#define BTN4_PIN                         GPIO_Pin_14
#define BTN4_GPIO_PORT                   GPIOE
#define BTN4_GPIO_CLK                    RCC_AHB1Periph_GPIOE

/* PB14 */
#define BTN5_PIN                         GPIO_Pin_14
#define BTN5_GPIO_PORT                   GPIOB
#define BTN5_GPIO_CLK                    RCC_AHB1Periph_GPIOB

/* PD10 */
#define BTN6_PIN                         GPIO_Pin_10
#define BTN6_GPIO_PORT                   GPIOD
#define BTN6_GPIO_CLK                    RCC_AHB1Periph_GPIOD

#else

/* PC4 */
#define BTN1_PIN                         GPIO_Pin_4
#define BTN1_GPIO_PORT                   GPIOC
#define BTN1_GPIO_CLK                    RCC_AHB1Periph_GPIOC

/* PB1 */
#define BTN2_PIN                         GPIO_Pin_1
#define BTN2_GPIO_PORT                   GPIOB
#define BTN2_GPIO_CLK                    RCC_AHB1Periph_GPIOB

/* PE9 */
#define BTN3_PIN                         GPIO_Pin_9
#define BTN3_GPIO_PORT                   GPIOE
#define BTN3_GPIO_CLK                    RCC_AHB1Periph_GPIOE

/* PE13 */
#define BTN4_PIN                         GPIO_Pin_13
#define BTN4_GPIO_PORT                   GPIOE
#define BTN4_GPIO_CLK                    RCC_AHB1Periph_GPIOE

/* PB11 */
#define BTN5_PIN                         GPIO_Pin_11
#define BTN5_GPIO_PORT                   GPIOB
#define BTN5_GPIO_CLK                    RCC_AHB1Periph_GPIOB

/* PB14 */
#define BTN6_PIN                         GPIO_Pin_14
#define BTN6_GPIO_PORT                   GPIOB
#define BTN6_GPIO_CLK                    RCC_AHB1Periph_GPIOB

/* PD8  */
#define BTN7_PIN                         GPIO_Pin_8
#define BTN7_GPIO_PORT                   GPIOD
#define BTN7_GPIO_CLK                    RCC_AHB1Periph_GPIOD

/* PD10 */
#define BTN8_PIN                         GPIO_Pin_10
#define BTN8_GPIO_PORT                   GPIOD
#define BTN8_GPIO_CLK                    RCC_AHB1Periph_GPIOD
#endif


/** Exported functions */
void ledInit(Led_TypeDef Led);
void ledOn(Led_TypeDef Led);
void ledOff(Led_TypeDef Led);
void ledToggle(Led_TypeDef Led);

void init_btn(uint16_t btn);
//void sw_del(void);
//void switch_leds(void);


void STM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t STM_EVAL_PBGetState(Button_TypeDef Button);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4DISC_EVAL_H */
