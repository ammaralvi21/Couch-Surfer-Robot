/******************************************************************************
 * Name:    GPIO.c
 * Description: STM32 GPIO initialization and functions
 * Version: V1.00
 * Author: Ammar Alvi & Shannon D'Souza
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *****************************************************************************/
 #include "stm32f10x.h"
 #include "GPIO.h"

/*
* Name:         void GPIO_config()
* Paramaters:   none
* Description: This function will configure the outputs of 
							 the GPIO pins A8, A9, A10, A11, B4, B8, B10, B13, C8
               
*/


void GPIO_config(void)
{
     

   //Set the config and mode bits for Port B, pin 10 so they will
   // be AFIO outputs (up to 50 MHz)
	GPIOB->CRH |= GPIO_CRH_MODE10 | GPIO_CRH_CNF10_1;
	GPIOB->CRH &= ~GPIO_CRH_CNF10_0;

	//Ultrasonic Trigger Outputs Pushpull configuration (up to 50 MHz)
	GPIOC->CRH |= GPIO_CRH_MODE8;
	GPIOC->CRH &= ~GPIO_CRH_CNF8;
	GPIOB->CRH |= GPIO_CRH_MODE13;
	GPIOB->CRH &= ~GPIO_CRH_CNF13;
	GPIOB->CRL |= GPIO_CRL_MODE4;
	GPIOB->CRL &= ~GPIO_CRL_MODE4;
	//Configuring the A8 to A11 as AFIO outputs for TIM1
	GPIOA->CRH |= GPIO_CRH_MODE8 | GPIO_CRH_CNF8_1 | GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1 | GPIO_CRH_MODE10 | GPIO_CRH_CNF10_1 | GPIO_CRH_MODE11 | GPIO_CRH_CNF11_1;
	GPIOA->CRH &= ~GPIO_CRH_CNF8_0 & ~GPIO_CRH_CNF9_0 & ~GPIO_CRH_CNF10_0 & ~GPIO_CRH_CNF11_0;

   
}






