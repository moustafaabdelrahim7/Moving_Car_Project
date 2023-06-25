/**
 ** @file                   gptimer_manager.h
 ** @brief                  This is header file for gptimer_manager 
 ** @author                 Nada Abdelazim
 ** @date                   June 21, 2023
 ** @version                0.1
 */

#ifndef GPTIMER_MANAGER_H_
#define GPTIMER_MANAGER_H_

/*******INCLUDES*******/
#include "gptimer_manager_config.h"
#include "gptimer.h"
#include "gpio.h"


#define PERCENTAGE                100
#define ONE                        1


/*---------------------------------------------------------/
/- APIs definitions -----------------------------------/
/---------------------------------------------------------*/
/**
 *  @brief 			   This function initializes TIMER 0 according to user's cnfigurations.
 *  @param[in]		 none.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t timer0_init ( void) ;
/**
 *  @brief 			   This function to delay in ms using TIMER 0 in one_shot mode.
 *  @param[in]		 uint16_t milli_sec of the time desired to be delayed.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint16_t timer0_delay_ms (uint16_t a_u16_milli_sec);
/**
 *  @brief 			   This function to generate pwm in specific pin.
 *  @param[in]		 port and pin number to generate pwm on it and the desired duty cycle in percenatge.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t pwm_pin (uint16_t a_u16_duty_cycle,uint8_t a_u8_pin_num, uint8_t a_u8_port_num);
/**
 *  @brief 			   This function generation the interrupt after the input time by using periodic mode timer.
 *  @param[in]		 The Required time in microsecond, Fptr (pointer to function).
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t time_us(uint16_t time , void(*fptr)(void)); //time in microsecond

/**
 *  @brief 			   This function generation the interrupt after the input time by using periodic mode timer.
 *  @param[in]		 The Required time in millesecond, Fptr (pointer to function).
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t time_ms(uint16_t time , void(*fptr)(void)); //time in millesecond

/**
 *  @brief 			   This function generation the interrupt after the input time by using periodic mode timer.
 *  @param[in]		 The Required time in second, Fptr (pointer to function).
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t time_s(uint16_t time , void(*fptr)(void)); //time in second

/**
 *  @brief 			   This function generation the interrupt after the input time by using oneshot mode timer.
 *  @param[in]		 The Required time in second, Fptr (pointer to function).
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t time_sec_oneshot_mode(uint16_t time , void(*fptr)(void));

/**
 *  @brief 			   This function stop the pwm generation.
 *  @param[in]		 none
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t pwm_timer_stop (void);


#endif 
