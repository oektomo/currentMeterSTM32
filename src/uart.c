/*
 * uart.c
 *
 *  Created on: Oct 19, 2017
 *      Author: otm
 */

#include "platform_config.h"
#include "uart.h"
#include <stdarg.h>
#include <stdio.h>

/*
 * to initialize our UART we need 3 things
 * RCC UART
 * UART configuration
 * UART ENABLE
 *
 * RCC GPIO
 * GPIO AF configuration
 */
void initUART(USART_InitTypeDef* USART_InitStructure)
{
	/* Configure GPIO for USART	 */
	initUART_GPIO();

	  /* Enable USARTrPi Clock */
	  RCC_APB2PeriphClockCmd(USARTrPi_CLK_APB2, ENABLE);

	  USART_InitStructure->USART_BaudRate = 115200;
	  USART_InitStructure->USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure->USART_StopBits = USART_StopBits_1;
	  USART_InitStructure->USART_Parity = USART_Parity_No;
	  USART_InitStructure->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	  USART_Init(USARTrPi, USART_InitStructure);

	  /* Enable USARTm8 Clock */
	  RCC_APB1PeriphClockCmd(USARTm8_CLK_APB1, ENABLE);

	  USART_InitStructure->USART_BaudRate = 115200;
	  USART_InitStructure->USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure->USART_StopBits = USART_StopBits_1;
	  USART_InitStructure->USART_Parity = USART_Parity_No;
	  USART_InitStructure->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	  USART_Init(USARTm8, USART_InitStructure);

	  // Enable interrupt
	  USART_ITConfig(USARTrPi, USART_IT_RXNE, ENABLE);
	  USART_ITConfig(USARTm8, USART_IT_RXNE, ENABLE);

	  USART_Cmd(USARTrPi, ENABLE);
	  USART_Cmd(USARTm8, ENABLE);
}

/*
 * Enable RCC GPIO
 * initialize GPIO to AF
 */
void initUART_GPIO()
{
	  /* Enable GPIO UART clock */
	  RCC_APB2PeriphClockCmd(USARTm8_GPIO_CLK , ENABLE);

	  /* Enable GPIO UART clock */
	  RCC_APB2PeriphClockCmd(USARTrPi_GPIO_CLK , ENABLE);

	  GPIO_InitTypeDef GPIO_InitStructure;

	  /* Configure USARTrPi_RxPin Rx as input floating */
	  GPIO_InitStructure.GPIO_Pin = USARTrPi_RxPin;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(USARTrPi_GPIO, &GPIO_InitStructure);

	  /* Configure USARTm8_RxPin Rx as input floating */
	  GPIO_InitStructure.GPIO_Pin = USARTm8_RxPin;
	  GPIO_Init(USARTm8_GPIO, &GPIO_InitStructure);

	  /* Configure USARTrPi_TxPin Tx as alternate function push-pull */
	  GPIO_InitStructure.GPIO_Pin = USARTrPi_TxPin;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_Init(USARTrPi_GPIO, &GPIO_InitStructure);

	  /* Configure USARTm8 Tx as alternate function push-pull */
	  GPIO_InitStructure.GPIO_Pin = USARTm8_TxPin;
	  GPIO_Init(USARTm8_GPIO, &GPIO_InitStructure);
}

#ifdef INLINE_CODE
inline void
__attribute__((always_inline))
#else
void
#endif
USART_Tx(USART_TypeDef* USARTx, uint8_t Data)
{

	while( !USART_GetFlagStatus(USARTx, USART_FLAG_TXE) );
	USART_SendData(USARTx, Data);
}

uint8_t USART_SendString(USART_TypeDef* USARTx, const char* AoChar)
{
	uint8_t i = 0;
	while(AoChar[i] != '\0')
	{
		USART_Tx(USARTx, AoChar[i]);
		i++;
	}
	return i;
}

int
uart_printf(const char* format, ...)
{
  int ret;
  va_list ap;

  va_start (ap, format);

  // TODO: rewrite it to no longer use newlib, it is way too heavy

  static char buf[OS_INTEGER_UART_PRINTF_TMP_ARRAY_SIZE];

  // Print to the local buffer
  ret = vsnprintf (buf, sizeof(buf), format, ap);
  if (ret > 0)
    {
      // Transfer the buffer to the device
      //ret = trace_write (buf, (size_t)ret);
	  ret = (int)USART_SendString(USARTrPi, buf);
    }

  va_end (ap);
  return ret;
}
