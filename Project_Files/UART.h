/******************************************************************************
 * Name:    UART.h
 * Description: STM32 UART initizalization and functions
 * Version: V1.00
 * Author: Ammar Alvi & Shannon D'Souza
 *
 * This software is supplied "AS IS" without warranties of any kind.
 ***************************************************************/

#include <stdint.h>

void UART3_init(void);
void UART3_TX_Byte(uint8_t val);
void UART3_TX_str(char data[]);

