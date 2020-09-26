/******************************************************************************
 * Name:    clocks.h
 * Description: STM32 system clock initialization
 * Version: V1.00
 * Author: Ammar Alvi & Shannon D'Souza
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *
 *****************************************************************************/
#include <stdint.h>


 //Functions available for public use

  void sys_clockInit(void);
	void GPIO_clockInit(void);
	void AFIO_clockInit(void);
	void ADC_clockInit(void);
	void TIM1_clockInit(void);
	void USART3_clockInit(void);
