/**
 ** @file                   app.c
 ** @brief                  This is source file for app for TM4C123GH6PM
 ** @author               	 kateem magdy
 ** @date                   June 23, 2023
 ** @version                0.2
 */
#include "app.h"
#include "led.h"
#include "button.h"
#include "gptimer_manager.h"
#include "motor_config.h"
#include "car_control.h"


#define  _500_MS_SECOND 	1
#define  _1_SECOND 				1
#define  _2_SECOND 				2
#define  _3_SECOND 				3

#define  PWM_EN_1_PIN	   	PIN7
#define  PWM_EN_1_Port	 PORTB 	



// GLOBAL VARIABLES
uint8_t u8_carMode = 0, u8_start = 0 ;
extern str_motor_config_t str_motor_config_motor_1;
extern str_motor_config_t str_motor_config_motor_2;

// call back functions
void  TimerCallBack_carMode (void)
{
	u8_carMode++;
}

void  SW1_CallBack_start (void)
{
	u8_start = CAR_START;
	
}

void  SW2_CallBack_start (void)
{
	u8_start = CAR_STOP;
}


// INITIALIZATION
void APP_init(void)
{	
	pwm_pin(0,PWM_EN_1_PIN,PWM_EN_1_Port);
	// LEDs init
	led_init(GREEN_LED_PORT,GREEN_LED_PIN);
	led_init(RED_LED_PORT,RED_LED_PIN);
	led_init(BLUE_LED_PORT,BLUE_LED_PIN);

	// button init
	button_init(SW1_PORT,SW1_PIN);
	button_init(SW2_PORT,SW2_PIN);
	
	port_interrupt_enable(FALLING_EDGE,SW1_PORT,SW1_PIN);
	port_interrupt_setcallback(SW1_CallBack_start,SW1_PORT,SW1_PIN);
	
	port_interrupt_enable(RISING_EDGE,SW2_PORT,SW2_PIN);
	port_interrupt_setcallback(SW2_CallBack_start,SW2_PORT,SW2_PIN);
	
	// motor init
	 CAR_init(&str_motor_config_motor_1,&str_motor_config_motor_2); 
	
	
	// Initially, all LEDs are OFF
	led_off(GREEN_LED_PORT,GREEN_LED_PIN);
	led_off(RED_LED_PORT,RED_LED_PIN);	
	led_off(BLUE_LED_PORT,BLUE_LED_PIN);		

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
void car_stop_state (uint32_t u32_a_duration_ms)
{
	pwm_timer_stop();
	led_on(RED_LED_PORT,RED_LED_PIN);	
	led_off(GREEN_LED_PORT,GREEN_LED_PIN);
	led_off(BLUE_LED_PORT,BLUE_LED_PIN);	
	CAR_stop(&str_motor_config_motor_1,&str_motor_config_motor_2); 
		time_sec_oneshot_mode(u32_a_duration_ms ,TimerCallBack_carMode);
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
  led_on(GREEN_LED_PORT,GREEN_LED_PIN);
	led_off(RED_LED_PORT,RED_LED_PIN);	
	led_off(BLUE_LED_PORT,BLUE_LED_PIN);
	pwm_pin(50,PWM_EN_1_PIN,PWM_EN_1_Port);					
	CAR_forward(&str_motor_config_motor_1,&str_motor_config_motor_2);	
  time_sec_oneshot_mode( _3_SECOND,TimerCallBack_carMode);

}


/*******************************************************************************************************************************************
**DESCRIPTION:-
this function calculates the time nedded of rotation to turn the car 90 degree and return it*/
uint32_t rotate_90degree_calculation (void)
{
																															// --> [TODO] need to config calculation or try ny hardware and delete this api
	return _3_SECOND;
}


/*******************************************************************************************************************************************
**DESCRIPTION:-
this function used to fo the following :
 - led 4 is on
 - call rotate_90degree_calculation
 - motors rotate to the right
 - increment u8_carMode by 1
*/
void rotate_90degree_state (void)
{
	
	led_on(GREEN_LED_PORT,GREEN_LED_PIN);
	led_on(RED_LED_PORT,RED_LED_PIN);	
	led_on(BLUE_LED_PORT,BLUE_LED_PIN);
	
	uint32_t u32_l_RotationTime = rotate_90degree_calculation(); 
	time_sec_oneshot_mode( u32_l_RotationTime , TimerCallBack_carMode);
	pwm_pin(20,PWM_EN_1_PIN,PWM_EN_1_Port);
	CAR_right(&str_motor_config_motor_1,&str_motor_config_motor_2); 

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
	led_on(BLUE_LED_PORT,BLUE_LED_PIN);
	led_off(GREEN_LED_PORT,GREEN_LED_PIN);
	led_off(RED_LED_PORT,RED_LED_PIN);	

	
		pwm_pin(30,PWM_EN_1_PIN,PWM_EN_1_Port);																			
	time_sec_oneshot_mode( _2_SECOND,TimerCallBack_carMode);
	CAR_forward(&str_motor_config_motor_1,&str_motor_config_motor_2); 
	
}




void APP_start(void){


	if(u8_start == CAR_START) // EX_interrupt will set this flag by 1
		{
			
			if (u8_carMode == INITIAL_STOP)
			{
				car_stop_state(_1_SECOND);
			}
			else if(u8_carMode == LONG_SIDE )
				{

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
				//u8_carMode = LONG_SIDE ;				
			}
			else if (u8_carMode == REPEAT)
			{
				
				u8_carMode = LONG_SIDE ;			
			}
			
		}
		else if(u8_start == CAR_STOP)
		{
			CAR_stop(&str_motor_config_motor_1,&str_motor_config_motor_2);
			led_off(GREEN_LED_PORT,GREEN_LED_PIN);
	    led_off(RED_LED_PORT,RED_LED_PIN);	
	    led_off(BLUE_LED_PORT,BLUE_LED_PIN);	
		}
		else
		{
			//do nothing
		}
}



