/*
 * timer.h
 *
 *  Created on: Nov 1, 2017
 *      Author: otm
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"

void initTimer(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStructure);
void initTimerGPIO(GPIO_InitTypeDef* GPIO_InitStructure);
void initTimerADC(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStructure);
void saturate(uint16_t min, uint16_t max, uint16_t* data);

#endif /* TIMER_H_ */
