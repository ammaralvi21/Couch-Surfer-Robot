/******************************************************************************
 * Name:    UTIL.c
 * Description: Utility functions
 * Version: V1.00
 * Author: Ammar Alvi & Shannon D'Souza
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *
 *****************************************************************************/
 
 #include "stm32f10x.h"
 #include <stdint.h>
#include "GPIO.h"


/*
* Name:         void delay()
* Paramaters:   32 bit delay value, ( a value of 6000
                gives approximately 1 mS of delay)
* Description:  This function creates a delay
*/
void delay(uint32_t count)
{		

    int i=0;
    for(i=0; i< count; ++i)
    {
    }
}

/*
* Name:         uint8_t delay()
* Paramaters:   16 bits value to convert to its ascii form
* Description:  Adds a specific hex value to convert to its
								ascii form
*/

uint8_t to_ascii(uint16_t val)
{
	uint8_t asci = val;
	
		if (val > 0x9)
		{
			asci = asci + 0x37;
		}
		else 
		{
			asci = asci + 0x30;
		}
		return asci;
}

