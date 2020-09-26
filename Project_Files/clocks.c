/******************************************************************************
 * Name:    clocks.c
 * Description: STM32 system clock initialization and functions
 * Version: V1.00
 * Author: Ammar Alvi & Shannon D'Souza
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *
 *****************************************************************************/
 #include "stm32f10x.h"


// CLOCK AND TIMING FUNCTIONS

/*
* Name:         void sys_clockInit()
* Paramaters:   none
* Description: This function will initialize the device system
               clock to 24 Mhz
*/
void sys_clockInit(void)
{
    uint32_t temp = 0x00;
    //If you hover over the RCC you can go to the definition and then
    //see it is a structure of all the RCC registers.  Then you can
    //simply assign a value.
    RCC->CFGR = 0x00050002;     // Output PLL/2 as MCO,
                                // PLLMUL X3, PREDIV1 is PLL input

    RCC->CR =  0x01000081;      // Turn on PLL, HSE, HSI

    while (temp != 0x02000000)  // Wait for the PLL to stabilize
    {
        temp = RCC->CR & 0x02000000; //Check to see if the PLL lock bit is set
    }

}



/*
* Name:         void GPIO_clockInit()
* Paramaters:   none
* Description: This function will enable the GPIO port A, B, C
               clock 
*/

void GPIO_clockInit(void)
{
    

    //Enable peripheral clocks for various ports and subsystems
    //Bit 4: Port C Bit3: Port B Bit 2: Port A
    RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
	  //Enable peripheral clocks for various ports and subsystems



}


/*
* Name:         void AFIO_clockInit()
* Paramaters:   none
* Description: This function will enable the AFIO clock
               
*/

void AFIO_clockInit(void)
{
    

    //Enable peripheral clocks for various ports and subsystems
    //Bit 4: Port C Bit3: Port B Bit 2: Port A
    RCC->APB2ENR |=  RCC_APB2ENR_AFIOEN;
	  //Enable peripheral clocks for various ports and subsystems


}

/*
* Name:         void TIM1_clockInit()
* Paramaters:   none
* Description: This function will enable the TIM1 clock
               
*/
void TIM1_clockInit(void)
{
    

	//Enabling TIM1 clock
    RCC->APB2ENR |=  RCC_APB2ENR_TIM1EN;


}


/*
* Name:         void USART3_clockInit()
* Paramaters:   none
* Description: This function will enable the USART3 clock
               
*/

void USART3_clockInit(void)
{
    

	//Enabling USART3 clock
    RCC->APB1ENR |=  RCC_APB1ENR_USART3EN;


}

