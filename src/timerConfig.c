/*
 * timer.c
 *
 *  Created on: Nov 1, 2017
 *      Author: otm
 */
#include "timerConfig.h"

/*
 * Enable timer 3 as PWM?
 * check timer number we want to use!
 *
 * configure gpio
 */
void initTimer(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStructure)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	uint16_t CCR1_VAL = 10;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	uint16_t PrescalerValue =(uint16_t) (SystemCoreClock / 24000000) - 1;
	TIM_TimeBaseStructure.TIM_Period = 665;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure->TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure->TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure->TIM_Pulse = CCR1_VAL; // ? looks like duty cycle
	TIM_OCInitStructure->TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIMx, TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
	GPIO_InitTypeDef GPIO_InitStructure;
	initTimerGPIO(&GPIO_InitStructure);
	TIM_Cmd(TIMx, ENABLE);
}

void initTimerGPIO(GPIO_InitTypeDef* GPIO_InitStructure)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure->GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure->GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure->GPIO_Pin = GPIO_Pin_6;

	GPIO_Init(GPIOA, GPIO_InitStructure);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);

}

/*
 * probably using TIM1
 * need to calculate prescaler and timer
 */
void initTimerADC(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStructure)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	/* Time Base configuration */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 0x3FFF;
	TIM_TimeBaseStructure.TIM_Prescaler = 0x04;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

	/* TIM1 channel1 configuration in PWM mode */
	TIM_OCInitStructure->TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure->TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure->TIM_Pulse = 0x7F;
	TIM_OCInitStructure->TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC1Init(TIMx, TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
	TIM_ITConfig(TIMx, TIM_IT_CC1, ENABLE);
	TIM_Cmd(TIMx, ENABLE);
	TIM_CtrlPWMOutputs(TIMx, ENABLE);
}

void saturate(uint16_t min, uint16_t max, uint16_t* data)
{
	if((*data) > max) {
		*data = max;
	} else if((*data) < min) {
		*data = min;
	}
}
