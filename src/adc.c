/*
 * adc.c
 *
 *  Created on: Oct 31, 2017
 *      Author: otm2
 */

#include "adc.h"

/*
 * Need to read more about ADC mode with DMA
 * it's resolution is 12 bit
 * for STM32F103x8
 */
void initADC(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStructure)
{
	initGPIO_ADC();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitStructure->ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure->ADC_ScanConvMode = DISABLE;
	ADC_InitStructure->ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure->ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure->ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure->ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, ADC_InitStructure);
	// let's see what is rank means and what is ADC sample time?
	ADC_RegularChannelConfig(ADCx, ADC_Channel_0, 1, ADC_SampleTime_28Cycles5);
	ADC_Cmd(ADCx, ENABLE);

	ADC_ResetCalibration(ADCx);
	while(ADC_GetResetCalibrationStatus(ADCx));
	// WHAT IS calibration means?
	ADC_StartCalibration(ADCx);
	while(ADC_GetCalibrationStatus(ADCx));
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);
	//ADC_DMACmd(ADC1, ENABLE);
}

void initADCTimTrigger(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStructure)
{
	initGPIO_ADC();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitStructure->ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure->ADC_ScanConvMode = DISABLE;
	ADC_InitStructure->ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure->ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure->ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, ADC_InitStructure);
}
/*
 * Make sure it's in GPIOA PIN 0
 */
void initGPIO_ADC()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

/*
 * return the ADC converted data
 */
uint16_t getADCConv(ADC_TypeDef* ADCx)
{
	uint16_t data = 0;
	while ( !ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) );
	data = ADCx->DR;
	return data;
}
