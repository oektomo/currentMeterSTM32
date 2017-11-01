/*
 * platform_config.h
 *
 *  Created on: Oct 19, 2017
 *      Author: otm
 */

#ifndef PLATFORM_CONFIG_H_
#define PLATFORM_CONFIG_H_

#include "stm32f10x.h"

#define INLINE_CODE
//#define USE_TRACE
#define AS_DUMMY_LOAD
//#define DC_BOOSTER
//#define CHARGER
//#define DISCHARGER

  #define USARTrPi                   USART1
  #define USARTrPi_GPIO              GPIOA
  #define USARTrPi_CLK_APB2          RCC_APB2Periph_USART1
  #define USARTrPi_GPIO_CLK          RCC_APB2Periph_GPIOA
  #define USARTrPi_RxPin             GPIO_Pin_10
  #define USARTrPi_TxPin             GPIO_Pin_9
  #define USARTrPi_IRQn              USART1_IRQn
  #define USARTrPi_IRQHandler        USART1_IRQHandler

  #define USARTm8                   USART3
  #define USARTm8_GPIO              GPIOB
  #define USARTm8_CLK_APB1          RCC_APB1Periph_USART3
  #define USARTm8_GPIO_CLK          RCC_APB2Periph_GPIOB
  #define USARTm8_RxPin             GPIO_Pin_11
  #define USARTm8_TxPin             GPIO_Pin_10
  #define USARTm8_IRQn              USART3_IRQn
  #define USARTm8_IRQHandler        USART3_IRQHandler

  #define USARTdbg                   USART2
  #define USARTdbg_GPIO              GPIOA
  #define USARTdbg_CLK               RCC_APB1Periph_USART2
  #define USARTdbg_GPIO_CLK          RCC_APB2Periph_GPIOA
  #define USARTdbg_RxPin             GPIO_Pin_3
  #define USARTdbg_TxPin             GPIO_Pin_2
  #define USARTdbg_IRQn              USART2_IRQn
  #define USARTdbg_IRQHandler        USART2_IRQHandler

#define INPUT_PB_CLK_APB2	RCC_APB2Periph_GPIOB
#define INPUT_PA_CLK_APB2	RCC_APB2Periph_GPIOA
#define INPUT_PC_CLK_APB2	RCC_APB2Periph_GPIOC

#define INPUT_PH1_PIN	1
#define INPUT_PH1_PORT	GPIOB
#define INPUT_PH2_PIN	0
#define INPUT_PH2_PORT	GPIOB
#define INPUT_PH3_PIN	7
#define INPUT_PH3_PORT	GPIOA
#define INPUT_PH4_PIN	6
#define INPUT_PH4_PORT	GPIOA
#define INPUT_PH5_PIN	5
#define INPUT_PH5_PORT	GPIOA
#define INPUT_PH6_PIN	4
#define INPUT_PH6_PORT	GPIOA
#define INPUT_PH7_PIN	15
#define INPUT_PH7_PORT	GPIOC
#define INPUT_PH8_PIN	14
#define INPUT_PH8_PORT	GPIOC
#define INPUT_PH9_PIN	13
#define INPUT_PH9_PORT	GPIOC
#define INPUT_PH10_PIN	3
#define INPUT_PH10_PORT	GPIOA
#define INPUT_PH11_PIN	1
#define INPUT_PH11_PORT	GPIOA
#define INPUT_PH12_PIN	0
#define INPUT_PH12_PORT	GPIOA
#endif /* PLATFORM_CONFIG_H_ */
