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
	RCC_APB2PeriphClockCmd(ADC_CLK_APB2, ENABLE);

	ADC_InitStructure->ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure->ADC_ScanConvMode = DISABLE;
	ADC_InitStructure->ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure->ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure->ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure->ADC_NbrOfChannel = 1;
	ADC_Init(ADCx, ADC_InitStructure);
	// let's see what is rank means and what is ADC sample time?
	ADC_RegularChannelConfig(ADCx, ADC_Channel_0, 1, ADC_SampleTime_28Cycles5);
	ADC_Cmd(ADCx, ENABLE);

	ADC_ResetCalibration(ADCx);
	while(ADC_GetResetCalibrationStatus(ADCx));
	// WHAT IS calibration means?
	ADC_StartCalibration(ADCx);
	while(ADC_GetCalibrationStatus(ADCx));
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);
}

#define ADC_CAL
void initADCTimTrigger(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStructure)
{

	initGPIO_ADC();
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitStructure->ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure->ADC_ScanConvMode = DISABLE;
	ADC_InitStructure->ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure->ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure->ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure->ADC_NbrOfChannel = 1;
	ADC_Init(ADCx, ADC_InitStructure);

	// let's see what is rank means and what is ADC sample time?
	ADC_RegularChannelConfig(ADCx, ADC_Channel_0, 1, ADC_SampleTime_28Cycles5);
	//ADC_RegularChannelConfig(ADCx, ADC_Channel_0, 1, ADC_SampleTime_13Cycles5);
	//ADC_ExternalTrigConvCmd(ADCx, ENABLE);
	ADC_Cmd(ADCx, ENABLE);

#ifdef ADC_CAL
	  /* Enable ADC1 reset calibration register */
	  ADC_ResetCalibration(ADCx);
	  /* Check the end of ADC1 reset calibration register */
	  while(ADC_GetResetCalibrationStatus(ADCx));

	  /* Start ADC1 calibration */
	  ADC_StartCalibration(ADCx);
	  /* Check the end of ADC1 calibration */
	  while(ADC_GetCalibrationStatus(ADCx));
#endif
	//ADC_SoftwareStartConvCmd(ADCx, ENABLE);
}

void initADCScan(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStructure)
{
	initGPIO_ADC();
	initGPIO2_ADC();
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitStructure->ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure->ADC_ScanConvMode = ENABLE;
	ADC_InitStructure->ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure->ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure->ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure->ADC_NbrOfChannel = 2;
	ADC_Init(ADCx, ADC_InitStructure);

	// let's see what is rank means and what is ADC sample time?
	ADC_RegularChannelConfig(ADCx, ADC_Channel_0, 1, ADC_SampleTime_41Cycles5);
	ADC_RegularChannelConfig(ADCx, ADC_Channel_1, 2, ADC_SampleTime_41Cycles5);
	//ADC_RegularChannelConfig(ADCx, ADC_Channel_0, 1, ADC_SampleTime_13Cycles5);
	//ADC_ExternalTrigConvCmd(ADCx, ENABLE);
	ADC_Cmd(ADCx, ENABLE);

#ifdef ADC_CAL
	  /* Enable ADC1 reset calibration register */
	  ADC_ResetCalibration(ADCx);
	  /* Check the end of ADC1 reset calibration register */
	  while(ADC_GetResetCalibrationStatus(ADCx));

	  /* Start ADC1 calibration */
	  ADC_StartCalibration(ADCx);
	  /* Check the end of ADC1 calibration */
	  while(ADC_GetCalibrationStatus(ADCx));
#endif
}

/*
 * Make sure it's in GPIOA PIN 0
 */
void initGPIO_ADC()
{
	RCC_APB2PeriphClockCmd(ADC_GPIO_CLK_APB2, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void initGPIO2_ADC()
{
	RCC_APB2PeriphClockCmd(ADC_GPIO_CLK_APB2, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
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
