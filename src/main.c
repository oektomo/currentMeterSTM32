//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "uart.h"
#include "adc.h"
#include "interrupt.h"
#include "platform_config.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F1 empty sample (trace via NONE).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the NONE output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.
	USART_InitTypeDef USART_InitStructure;
	initUART(&USART_InitStructure);
	ADC_InitTypeDef ADC_InitStructure;
	initADC(ADC1, &ADC_InitStructure);

	  NVIC_Config();

	  USART_SendString(USARTrPi, "Current Meter Started v0.2 \n\r");
	  uint16_t data;
	  float volt;

  while (1)
    {
       data = getADCConv(ADC1);
       // manually start the convertion after get the Data
       ADC_SoftwareStartConvCmd(ADC1, ENABLE);
       volt = (float) data;
       volt = volt*3.3/2048;
       uart_printf("ADC1 %.2f\n\r", volt);
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
