// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "Timer.h"
#include "uart.h"
#include "adc.h"
#include "timerConfig.h"
#include "interrupt.h"
#include "platform_config.h"

#define PERIOD  (TIMER_FREQUENCY_HZ * 100 / 1000)

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
extern volatile timer_ticks_t timer_delayCount;

int
main(int argc, char* argv[])
{
	USART_InitTypeDef USART_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	initUART(&USART_InitStructure);
	USART_SendString(USARTrPi, "Current Meter Started v0.2 \n\r");
	USART_SendString(USARTrPi, "UART Started\n\r");
	uart_printf("TIM1_BDTR %04x\n\r",TIM1->BDTR);
	//uint32_t seconds = 0;
#ifdef AS_DUMMY_LOAD
	initADC(ADC1, &ADC_InitStructure);
#endif
#ifdef DC_BOOSTER
	timer_start();
	initADCTimTrigger(ADC1, &ADC_InitStructure);
	uart_printf("ADC started\n\r");
	initTimerADC(TIM1, &TIM_OCInitStructure);
	uart_printf("Timer1 started\n\r");
#endif

#ifdef CHARGER
	timer_start();
	initADCScan(ADC1, &ADC_InitStructure);
	uart_printf("ADC started\n\r");
#endif
	initTimer(TIM3, &TIM_OCInitStructure);
	uart_printf("Timer3 started\n\r");

	NVIC_Config();
	uart_printf("NVIC started\n\r");

	uint16_t data, data2, outputPWM;
	float volt;
	uint32_t counter = 0;
	uart_printf("TIM1_BDTR %04x\n\r",TIM1->BDTR);
	uart_printf("LOOP STARTing\n\r");

	timer_start();
	timer_delayCount = 0;
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (1)
    {
#ifdef AS_DUMMY_LOAD

       data = getADCConv(ADC1);
       // manually start the convertion after get the Data
       ADC_SoftwareStartConvCmd(ADC1, ENABLE);
       volt = (float) data;
       outputPWM = data * 650 / 4096;
       TIM_SetCompare1(TIM3, outputPWM);
       volt = volt*3.3/4096;
       uart_printf("%u ADC1 %.2f PWM: %u\n\r", counter, volt, outputPWM*100/650);
       counter++;
#endif

#ifdef DC_BOOSTER
       data = getADCConv(ADC1);
       //data = TIM_GetCounter(TIM1);
       uart_printf("timer: %u\n\r",timer_delayCount);

       check_timer();
       timer_set (PERIOD);
       ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	   outputPWM = data * 650 / 4096;
	   TIM_SetCompare1(TIM3, outputPWM);
#define AJAIB
#ifdef AJAIB
       volt = (float) data;
	   volt = volt*3.3/4096;
	   uart_printf("%u ADC1 %.2f PWM: %u\n\r", counter, volt, outputPWM*100/650);
	   //uart_printf("%u ADC1 %.2f TIM1 counter: %u\n\r", counter, volt, data);
#endif
	   counter++;
#endif

#ifdef CHARGER
       data = getADCConv(ADC1);
       ADC_SoftwareStartConvCmd(ADC1, ENABLE);
       data2 = getADCConv(ADC1);

       uart_printf("timer: %u\n\r",timer_delayCount);

       check_timer();
       timer_set (PERIOD);
       ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	   outputPWM = data * 650 / 4096;
	   TIM_SetCompare1(TIM3, outputPWM);

       volt = (float) data;
	   volt = volt*3.3/4096;
	   uart_printf("%u ADC1 %.2f ADC2 %u PWM: %u\n\r", counter, volt, data2, outputPWM*100/650);
#endif

#ifdef DISCHARGER
#endif
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
