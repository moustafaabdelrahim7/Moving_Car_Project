/**
 ** @file                   app.c
 ** @brief                  This is source file for app for TM4C123GH6PM
 ** @author                 Nada Abdelazim
 ** @date                   June 16, 2023
 ** @version                0.1
 */
#include "app.h"
#include "led.h"
#include "button.h"
#include "gptimer_manager.h"


#define FIRST_STATE   1
#define SECOND_STATE  2
#define THIRD_STATE   3
#define FOURTH_STATE  4

#define  SystemCoreClock  50000000


uint8_t buttonstate;
		
uint8_t sequence;

void APP_init(void)
{
	 buttonstate=released;	
	 sequence=FIRST_STATE;

	// TIMER0 INIT
	timer0_init () ;
	// LEDs init
	led_init(GREEN_LED_PORT,GREEN_LED_PIN);
	// button init
	button_init(SW1_PORT,SW1_PIN);
	// Initially, all LEDs are OFF
	led_off(GREEN_LED_PORT,GREEN_LED_PIN);	
}
void APP_start(void)
	{
		
		                     timer0_pwm(30,GREEN_LED_PIN,GREEN_LED_PORT);
				                 sequence=SECOND_STATE;
		
		button_read(SW1_PORT,SW1_PIN,&buttonstate);
		
		if (buttonstate==pressed)
		{
			switch (sequence)
			{
				case FIRST_STATE: 
	                       timer0_pwm(30,GREEN_LED_PIN,GREEN_LED_PORT);
				                 sequence=SECOND_STATE;
                 				 break;
				case SECOND_STATE:
			                    timer0_pwm(60,GREEN_LED_PIN,GREEN_LED_PORT);
				                  sequence=THIRD_STATE;
                 				  break;
				case THIRD_STATE: 
				                  
                          timer0_pwm(90,GREEN_LED_PIN,GREEN_LED_PORT);
				                  sequence=FOURTH_STATE;
                 				  break;
				case FOURTH_STATE:
                          led_off(GREEN_LED_PORT,GREEN_LED_PIN);
				                  sequence=FIRST_STATE;
                 				  break;

				default:
					                //ERROR Handling
				                  sequence=FIRST_STATE;
				                  
			}
		}
		
		
	}





	
	


