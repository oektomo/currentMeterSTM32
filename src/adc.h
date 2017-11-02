/*
 * adc.h
 *
 *  Created on: Oct 31, 2017
 *      Author: otm2
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f10x_adc.h"
#include "platform_config.h"

void initADC(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStructure);
void initADCTimTrigger(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStructure);
void initGPIO_ADC();
uint16_t getADCConv(ADC_TypeDef* ADCx);

#endif /* ADC_H_ */
