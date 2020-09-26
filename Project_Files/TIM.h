/******************************************************************************
 * Name:    TIM.h
 * Description: STM32 Timer 1 initialization and functions
 * Version: V1.00
 * Author: Ammar Alvi & Shannon D'Souza
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *****************************************************************************/
#include <stdint.h>

void TIM1_PWM_init(void);
void TIM1_Brake(void);
void TIM1_Forward(void);
void TIM1_TurnLeft(void);
void TIM1_TurnRight(void);
void TIM1_ForwardAdj(uint8_t val);

