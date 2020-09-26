/*  ENEL 387 Lab Project */
/* Author – Ammar Alvi & Shannon D'Souza, April 5, 2020 */

#include "stm32f10x.h"
#include "AFIO.h"
#include "clocks.h"
#include "GPIO.h"
#include "UTIL.h"
#include "TIM.h"
#include "UART.h"
#include "Sensors.h"


uint8_t cntr = 0;			//Global counter value to be used to count the number of stripes
uint8_t nav = 1, avoid = 0;			//Variables that control the state of the car
int main(void)
{

	sys_clockInit(); 		//Initilizing system clock
	GPIO_clockInit();		//Initializing GPIO clock
	AFIO_clockInit();		//Initializing AFIO clock
	TIM1_clockInit();		//Initializing Timer 1 clock
	USART3_clockInit();	//Initializing USART 3 clock
	AFIO_config();			//Configuring the AFIO pins
	GPIO_config();			//Configuring GPIO pins

	
	EXTI->IMR |= EXTI_IMR_MR12;		//Unmasking the interrupt at pin 12
	EXTI->FTSR |= EXTI_FTSR_TR12;	//Setting intterrupt to trigger at rising edge
	
	//Programming the NVIC interrupt set enable to enable EXTI15_10 at position 40
	NVIC->ISER[1] |= NVIC_ISER_SETENA_8;  
	
	TIM1_PWM_init();		//Initializing the 4 PWM outputs for TIMER 1
	UART3_init();				//Initializing the UART Tx ouput for HC-05 Bluetooth module
	
	uint8_t pb = 0;			//Variable to track state of blue pushbutton
	
	while(1)
	{
		//If the Blue push button on descovery board is pressed
		if(GPIOA->IDR & GPIO_IDR_IDR0)	
		{
			pb = 1;							//Indicating blue push button was pressed	
			UART3_TX_str("Button Pressed\n");	//Ouptut to bluetooth terminal screen
			
			//Keep looping until the input from the IR Sensor no longer detects white paper
			while((GPIOB->IDR & GPIO_IDR_IDR12) != GPIO_IDR_IDR12)
			{
				//If the Front Right sensor measures distance less than 4cm
				if((FrontRightUSLen() < 40))		
				{
					TIM1_TurnLeft();							//Turn left
				}
				//If Front Right and Middle Right sensor measure greater than 7cm
				else if((FrontRightUSLen() > 70) && (RightUSLen() > 70))	
				{
					TIM1_TurnRight();							//Turn Right
				}
				else
				{			
					TIM1_ForwardAdj(5);						//Go forward at 75% speed
				}
				
			}
		}
		
		//Because the Blue Push buton was pressed enter this loop
		while(pb)
		{
			//Output the to bluetooth terminal that car is now navigating around the couch
			UART3_TX_str("Navigating Around Couch...\n");
			
			//Navigation loop which is true only when the couch is navigating (nav = 1)
			while(nav)		
			{
				
				//If the infared sensor detects a white surface, while navigating 
				if((GPIOB->IDR & GPIO_IDR_IDR12) != GPIO_IDR_IDR12)
				{
					TIM1_Brake();					//Stop the car
					
					//Indicate that the navigation is complete
					UART3_TX_str("Start Position sensed, navigation complete!!\n");
					//End the program
					return 0;
				}
				
				//If the Front Right sensor measures distance less than 4cm			
				if((FrontRightUSLen() < 40))
				{
					TIM1_TurnLeft();		//Too close to couch, turn left
				}
				//If Front Right and Middle Right sensor measure greater than 7cm
				else if((FrontRightUSLen() > 70) && (RightUSLen() > 70))
				{
					TIM1_TurnRight();		//Too far from couch, turn right
				}
				else{			
					TIM1_ForwardAdj(4);	//Go forward at 80% speed
				}
				
				//The front sensor detects something at less than 10cm
				if(FrontUSLen() < 100)
				{
					TIM1_Brake();	//Brake
					//Output to Bluetooth to indicate that Object was detected
					UART3_TX_str("Going around the obstacle...\n");
					//Indicating the change in state of navigation to avoiding state
					nav = 0;
					avoid = 1;
				}
				
			}
			//Turn left until the front sensor no longer detects the object
			TIM1_TurnLeft();
			while(FrontUSLen() < 1000) {}
			//This delay was set to make the car turn extra to avoid crashing of car	
			delay(4000000);
			//At this point the car should have turned left facing away from the couch	
			//Loop until the Front Right and Middle right no longer sense the object
			while((RightUSLen() < 1000) && (FrontRightUSLen() < 1000))
			{
				//If the Front Right or Middle Right sensor detect the object
				if((RightUSLen() < 100) || (FrontRightUSLen() < 100))
				{
					TIM1_TurnLeft();		//Turn left
				}
				else{			
					TIM1_ForwardAdj(7);	//Go forward at 65% speed
				}
	
			}
				
			//Start to turn Right when the Middle Right sensor doesn't detect the object
			TIM1_TurnRight();

			cntr = 0;			//Set the stripe counter to 0
			//The number of stripes will be counted using interrups during this loop
			//Avoiding loop is true only if the car is in avoiding state (avoid = 1)
			while(avoid)
			{
				//If the Front Right sensor gets closer than 6cm
				if(FrontRightUSLen() < 60)
				{
					TIM1_TurnLeft();	//Turn left
				}
				//If the Front Right Sensor and Middle Right sensor detect...
				//...distance greater than 7cm 
				else if((FrontRightUSLen() > 70) && (RightUSLen() > 70))
				{
					TIM1_TurnRight();		//Turn Right
				}
				else{								
					TIM1_ForwardAdj(7);	//Go forward at 65% speed
				}
				
				//If the front sensor detects a distance less than 10cm
				if(FrontUSLen() < 100)
				{
					//Object has been avoided and couch has been detected
					//Car brakes
					TIM1_Brake();
					//Change the state of the car from avoiding to navigating..
					//...to exit the loop
					avoid = 0;
					nav = 1;
				}
				
			}
			//Send the number of stripes counted by the IR sensor....
			//...corresponding with the box number to bluetooth
			UART3_TX_str("Box #");
			UART3_TX_Byte(to_ascii(cntr));
			UART3_TX_str(" was detected\n");
			
			//Turn left until the front sensor doesn't detect the couch anymore
			TIM1_TurnLeft();
			while(FrontUSLen() < 1000) {}
			delay(3000000);				//Extra delay is added to ensure approx 90 degree turn
					
		}

	}
}


//Exception handler for GPIOB12 (EXTI12)
//This is called when IR detects a white color
void EXTI15_10_IRQHandler(void)
{
	//This delay was added out of neccessity to avoid initial bouncing error
	delay(50000);			
	EXTI->PR |= EXTI_PR_PR12; // Clear the pending interrupt bit
	//If the car is not navtigating and the IR sensor detects white surface
	if((nav == 0)&&(GPIOB->IDR & GPIO_IDR_IDR12) != GPIO_IDR_IDR12)
	{	
		cntr++;		//Increment counter
		
		//Wait for the IR sensor to detect non white surface
		while((GPIOB->IDR & GPIO_IDR_IDR12) != GPIO_IDR_IDR12){}
	
	}
	//Delay added to avoid input from bouncing of sensor inputs
	delay(50000);
}

