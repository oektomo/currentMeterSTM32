/*
 * interrupt.c
 *
 *  Created on: Oct 28, 2017
 *      Author: otm2
 */

#include "interrupt.h"
#include "uart.h"
#include "platform_config.h"

//extern uint8_t RxBuffer;

/*
 * Receive interrupt configuration on NVIC
 * We need to learn a lot about NVIC
 * Receive interrupt for USART1 and USART3
 */
void
NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

/*
 * USART1 interrupt handler
 */
void
USART1_IRQHandler(void)
{
	// check if Receive Data Register not empty
	if( USART_GetITStatus(USARTrPi, USART_IT_RXNE) ) {
		uint8_t RxBuffer = USART_ReceiveData(USARTrPi);
		USART_Tx(USARTm8, RxBuffer);
		RxBuffer++;
		//USART_Tx(USARTrPi, RxBuffer);

	}
}

/*
 * USART3 interrupt handler
 */
void
USART3_IRQHandler(void)
{
	// check if Receive Data Register not empty
	if( USART_GetITStatus(USARTm8, USART_IT_RXNE) ) {
		uint8_t RxBuffer = USART_ReceiveData(USARTm8);
		USART_Tx(USARTrPi, RxBuffer);

	}
}
