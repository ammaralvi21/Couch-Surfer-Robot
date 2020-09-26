/******************************************************************************
 * Name:    TIM.c
 * Description: STM32 Timer initiziation and functions
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
* Name:         void TIM1_PWM_init(void)
* Paramaters:   none
* Description: 	Writes to TIM1 registers for PWM initialization on
								PA8, PA9, PA10, PA11
*/

void TIM1_PWM_init(void)
{
	TIM1->CR1 |= TIM_CR1_CEN;
	TIM1->CR2 |= TIM_CR2_OIS1 | TIM_CR2_OIS2 | TIM_CR2_OIS3 | TIM_CR2_OIS4;
	TIM1->EGR |= TIM_EGR_UG;

	TIM1->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	TIM1->CCMR1 |= TIM_CCMR1_OC2PE | TIM_CCMR1_OC2FE | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;	
	TIM1->CCMR2 |= TIM_CCMR2_OC3PE | TIM_CCMR2_OC3FE | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;	
	TIM1->CCMR2 |= TIM_CCMR2_OC4PE | TIM_CCMR2_OC4FE | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;	
	TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;		//Enable Capture compare register

	TIM1->PSC = 0x095F;						//Devide 24Mhz by 24, PSC_CLK = 1000000 Hz, 1 count = 0.000001s = 1us
	TIM1->ARR = 20;								//20 counts = 20us   f = 50 KHz  (PWM frequency)
	TIM1->CCR1 = 21;							//21 countes = 100% duty cycle = logic 1
	TIM1->CCR2 = 21;	
	TIM1->CCR3 = 21;	
	TIM1->CCR4 = 21;	
	TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI; //Main Output Enable, Force Idle Level First
	TIM1->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; //Enable Timer 1
}

/*
* Name:         void TIM1_Brake(void)
* Paramaters:   none
* Description: 	Writes logic 1 to all 4 ports to stop left and right side motors
*/
void TIM1_Brake(void)
{
	TIM1->CCR1 = 21;							
	TIM1->CCR2 = 21;	
	TIM1->CCR3 = 21;	
	TIM1->CCR4 = 21;	
}

/*
* Name:         void TIM1_Forward(void)
* Paramaters:   none
* Description: 	Writes logic 1 to PA9, and PA11 but logic 0 to PA8, and PA10 
								to make both sides of the motor run at full speed
*/
void TIM1_Forward(void)
{
	TIM1->CCR1 = 1;							
	TIM1->CCR2 = 21;	
	TIM1->CCR3 = 1;	
	TIM1->CCR4 = 21;	
}
/*
* Name:         void TIM1_ForwardAdj(void)
* Paramaters:   8bit value to set the duty cycle of the PWM
* Description: 	Writes logic 1 to PA9, and PA11 but varying duty cycle to PA8, and PA10 
								to make both sides of the motor run at adjustable speed
*/
void TIM1_ForwardAdj(uint8_t val)
{
	TIM1->CCR1 = val;							
	TIM1->CCR2 = 21;	
	TIM1->CCR3 = val;	
	TIM1->CCR4 = 21;	
}

/*
* Name:         void TIM1_TurnLeft(void)
* Paramaters:   none
* Description: 	Writes logic 1 to PA8, PA9, and PA11 but logic 0 to PA10 
								to make Right side of the motor run at full speed to make 
								a left turn (differential steering)
*/
void TIM1_TurnLeft(void)
{
	TIM1->CCR1 = 21;
	TIM1->CCR2 = 21;	
	TIM1->CCR3 = 1;	
	TIM1->CCR4 = 21;	
}
/*
* Name:         void TIM1_TurnRight(void)
* Paramaters:   none
* Description: 	Writes logic 1 to PA9, PA10, PA11 but logic 0 to PA8 
								to make Left side of the motor run at full speed to make 
								a Right turn (differential steering)
*/
void TIM1_TurnRight(void)
{
	TIM1->CCR1 = 1;							
	TIM1->CCR2 = 21;	
	TIM1->CCR3 = 21;	
	TIM1->CCR4 = 21;	
}
