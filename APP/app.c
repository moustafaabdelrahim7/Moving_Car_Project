/**
 ** @file                   app.c
 ** @brief                  This is source file for app for TM4C123GH6PM
 ** @author               	 kateem magdy
 ** @date                   June 23, 2023
 ** @version                0.1
 */
#include "app.h"
#include "led.h"
#include "button.h"
#include "gptimer_manager.h"

#define  _1_SECOND 				1000
#define  _500_MS_SECOND 	500
	

/*  COMMENTED TO AVOID ERROR
#define FIRST_STATE   1
#define SECOND_STATE  2
#define THIRD_STATE   3
#define FOURTH_STATE  4
#define  SystemCoreClock  50000000
uint8_t buttonstate;	
uint8_t sequence;

*/





// GLOBAL VARIABLES
uint8_t u8_carMode ,u8_start ;

void f10 (void);
void f (void)
{
  pwm_pin(90,PIN2,PORTF);
	time_sec_oneshot_mode(3,f10);
}

void f10 (void)
{
pwm_timer_stop();
}

void APP_init(void)
{
		pwm_pin(50,PIN2,PORTF);
	time_sec_oneshot_mode(3,f);
	/* COMMENTED TO AVOID ERROE 
	
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
	*/
}


/*******************************************************************************************************************************************
**DESCRIPTION:-
this function used to fo the following :
 - led 3 on
 - take time that we want to stop for
 - motor stop
 - timer start counting  
 - after finshing counting increment u8_carMode by 1
*/
void car_stop_state (uint32_t u32_duration_ms)
{


}


/*******************************************************************************************************************************************
**DESCRIPTION:-
this function used to fo the following :
 - led 1 on
 - motors move forward
 - speed of motors is 50%
 - timer count 3 seconds 
 - after 3 seconds set  u8_carMode to equal 2
*/
void longSide_start()
{



}


/*******************************************************************************************************************************************
**DESCRIPTION:-
this function calculates the time nedded of rotation to turn the car 90 degree*/
void rotate_90degree_calculation (void){


}


/*******************************************************************************************************************************************
**DESCRIPTION:-
this function used to fo the following :
 - led 4 is on
 - call rotate_90degree_calculation
 - motors rotate to the right
 - increment u8_carMode by 1
*/
void rotate_90degree_state (void){


}


/*******************************************************************************************************************************************
**DESCRIPTION:-
this function used to fo the following :
 - led 2 on
 - motors move forward
 - speed of motors is 30%
 - timer count 2 seconds 
 - after 2 seconds increment u8_carMode by 1
*/
void shortSide_start()
{

}




void APP_start(void){


	if(u8_start == 1) // EX_interrupt will set this flag by 1
		{
		
			if (u8_carMode == INITIAL_STOP)
			{
				car_stop_state(_1_SECOND);
			}
	
	
			else if(u8_carMode == LONG_SIDE ){

				longSide_start();
		
			}
	
			else if (u8_carMode == STOP_AFTER_L_S)
			{
		
				car_stop_state(_500_MS_SECOND);
			}
	
			else if (u8_carMode == FIRST_ROTATION )
			{
				
				rotate_90degree_state();
				
			}
	
			else if(u8_carMode == STOP_AFTER_FIRST_ROT){
		
				
				car_stop_state(_500_MS_SECOND);

			}
			else if(u8_carMode == SHORT_SIDE){
				
				shortSide_start();

			}
			else if(u8_carMode == STOP_AFTER_S_S){
				
	
				car_stop_state(_500_MS_SECOND);

			}
			else if (u8_carMode == SECOND_ROTATION)
			{
				
				rotate_90degree_state();				
				
			}
			
			else if (u8_carMode == STOP_AFTER_SECOND_ROT)
			{
				
				car_stop_state(_500_MS_SECOND);
				
				
			}
			
		}
		else
		{
			

		}

	


}

/*
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

*/



	
	


