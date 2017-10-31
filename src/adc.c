/*
 * adc.c
 *
 *  Created on: Oct 31, 2017
 *      Author: otm2
 */

#include "adc.h"

/*
 * Need to read more about ADC mode with DMA
 */
void initADC(ADC_InitTypeDef* ADC_InitStructure)
{
	ADC_InitStructure->ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure->ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, ADC_InitStructure);
	ADC_DMACmd(ADC1, ENABLE);
}


