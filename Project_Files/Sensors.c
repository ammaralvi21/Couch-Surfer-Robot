/******************************************************************************
 * Name:    Sensors.c
 * Description: STM32 SR04 Ultrasonic Sensor interface
 * Version: V1.00
 * Author: Ammar Alvi & Shannon D'Souza
 *
 * This software is supplied "AS IS" without warranties of any kind.
 ***************************************************************/
 
 #include "stm32f10x.h"
 #include "GPIO.h"
 #include "UTIL.h"

  /*
* Name:         uint32_t FrontRightUSLen(void)
								uint32_t RightUSLen(void)
								uint32_t FrontUSLen(void)
								
* Paramaters:   none
* Description: 	Write a logic 1 to trigger pin of ultrasonic sensor
								for 50 us, then the read the width of pulse returned
								from the echo pin which is proportional to the distance
								measured.
								All the pulse width on the trig and echo pins were measured
								using oscilloscopes to provide accurate readings
								Returns 32 bit value which represents the mm of distance
								measured. The result measured to be within +/- 5mm accuracy
								which is good enough for our application.
*/
 
//A timeout variabe declared in case an interrupt causes the funciton
// to get stuck in an infinite loop
 uint32_t timeout = 0;
 
 uint32_t FrontRightUSLen(void)		//Front Right Ultrasonic Sensor
 {
	 uint32_t mm = 0;
	 timeout = 0;
	 GPIOC->BSRR |= GPIO_BSRR_BR8;		//Set trigger pin to 0
	 delay(20);
		GPIOC->BSRR |= GPIO_BSRR_BS8;		//Write logic 1 to trigger pin
		delay(54);											//Aproximately 10us
		GPIOC->BSRR |= GPIO_BSRR_BR8;		//Wirte logic 0 to trigger pin
	 //Wait for the echo pin to go high with a timout incase its unable to read
	 //a logic 1
		while((GPIOC->IDR & GPIO_IDR_IDR9) != GPIO_IDR_IDR9)
		{
			timeout++;
			if (timeout > 60000)
			{
				return 100;
			}
		}
		//Measure the width of the pulse received on the echo pin
		while((GPIOC->IDR & GPIO_IDR_IDR9) == GPIO_IDR_IDR9)
		{
			delay(12);
			mm = mm+3;
		}
		mm = (mm*10)/58;		//Convert pulsewidth to milimeters
		return mm;
 }
 
 uint32_t RightUSLen(void)			//Middle Right Ultrasonic Sensor
 {
		 uint32_t mm2 = 0;
	 timeout = 0;
	  GPIOB->BSRR |= GPIO_BSRR_BR13;
	  delay(20);
		GPIOB->BSRR |= GPIO_BSRR_BS13;
		delay(54);
		GPIOB->BSRR |= GPIO_BSRR_BR13;
		while((GPIOB->IDR & GPIO_IDR_IDR14) != GPIO_IDR_IDR14)
		{
		timeout++;
			if (timeout > 60000)
			{
				return 100;
			}
		}
		while((GPIOB->IDR & GPIO_IDR_IDR14) == GPIO_IDR_IDR14)
		{
			delay(12);
			mm2 = mm2+3;
		}
		mm2 = (mm2*10)/58;		
		return mm2;
 }
 
 uint32_t FrontUSLen(void)     //Front Ultrasonic Sensor
 {
		uint32_t mm3 = 0;
		timeout = 0;
	  GPIOB->BSRR |= GPIO_BSRR_BR4;
	  delay(20);
		GPIOB->BSRR |= GPIO_BSRR_BS4;
		delay(54);
		GPIOB->BSRR |= GPIO_BSRR_BR4;
		while((GPIOA->IDR & GPIO_IDR_IDR15) != GPIO_IDR_IDR15)
		{
			timeout++;
			if (timeout > 60000)
			{
				return 100;
			}
		}
		while((GPIOA->IDR & GPIO_IDR_IDR15) == GPIO_IDR_IDR15)
		{
			delay(12);
			mm3 = mm3+3;
		}
		mm3 = (mm3*10)/58;		
		return mm3;
 }

