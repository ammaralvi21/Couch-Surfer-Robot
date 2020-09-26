/******************************************************************************
 * Name:    AFIO.c
 * Description: STM32 AFIO configuration
 * Version: V1.00
 * Author: Ammar Alvi & Shannon D'Souza
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *****************************************************************************/
 #include "stm32f10x.h"
 #include "GPIO.h"
 #include "UTIL.h"



/*
* Name:         void AFIO_config()
* Paramaters:   none
* Description: 	Writes to AFIO registers.
								Disables JTAG, and remaps that pin to its actual GPIO port
								Enables external interrupt at PB12
*/


void AFIO_config(void)
{
     
		AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_1;
		AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI12_PB;

}
