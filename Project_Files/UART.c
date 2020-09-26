/******************************************************************************
 * Name:    UART.c
 * Description: STM32 UART initialization and functions
 * Version: V1.00
 * Author: Ammar Alvi & Shannon D'Souza
 *
 * This software is supplied "AS IS" without warranties of any kind.
 ***************************************************************/
 
 #include "stm32f10x.h"
 #include "GPIO.h"
 #include "UTIL.h"
  
 
 /*
* Name:         void UART3_init(void)
* Paramaters:   none
* Description: 	Initiazlize UART3 by writing 1 to Usart Enable
								and Transmit Enable. 9600 Baudrate
*/
 void UART3_init(void)
 {
    USART3->CR1 |= USART_CR1_UE;
	  USART3->BRR = 0x9C4;
		USART3->CR1 |= USART_CR1_TE;
 
 }
 
 /*
* Name:         void UART3_TX_Byte(uint8_t val)
* Paramaters:   8 bit value
* Description: 	Transmit a byte to HC05 bluetooth module
*/
 void UART3_TX_Byte(uint8_t val)
{

		while(((USART3->SR & USART_SR_TXE)>>7) != 1)
		{	}
		USART3->DR = val;	
		
}
 /*
* Name:         void UART3_TX_str(char data[])
* Paramaters:   array of char
* Description: 	Transmitting a null terminated string of characters
*/
void UART3_TX_str(char data[])
{
	for(int i = 0; data[i] != 0;i++)
	{
	UART3_TX_Byte(data[i]);
	}
}


