/**
 ** @file                   gpt.h
 ** @brief                  This is header file for GPT for TM4C123GH6PM
 ** @author                 Mohamed Sayed
 ** @date                   June 16, 2023
 ** @version                0.1
 */


#ifndef GPT_H_
#define GPT_H_
 
 #include "common.h"
 #include "TM4C123.h"
 #include "gptimer_config.h"
 
 
#define  GPTMTAILR_TIMER0        *((volatile uint32_t*)(0x40030000+0x028)) 
#define  GPTMRIS_TIMER0          *((volatile uint32_t*)(0x40030000+0x01C)) 
#define  TATORIS                  0

/*---------------------------------------------------------/
/- APIs IMPLEMENTATION -----------------------------------/
/---------------------------------------------------------*/

/**
 *  @brief 			   This function initializes the GPT.
 *  @param[in]		 pgpio pointer to input configuration structure.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t timer_init( Timer_cfg_st* timer_Cfg_st);

/**
 *  @brief 			   This function start the GPT.
 *  @param[in]		 pgpio pointer to input configuration structure.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t timer_start( Timer_cfg_st* timer_Cfg_st);

/**
 *  @brief 			   This function stop the GPT.
 *  @param[in]		 pgpio pointer to input configuration structure.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t timer_stop( Timer_cfg_st* timer_Cfg_st);

/**
 *  @brief 			   This function enable the interrupt the GPT.
 *  @param[in]		 pgpio pointer to input configuration structure.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t timer_interrupt_enable( Timer_cfg_st* timer_Cfg_st);

/**
 *  @brief 			   This function disable the interrupt the GPT.
 *  @param[in]		 pgpio pointer to input configuration structure.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t timer_B_interrupt_disable( Timer_cfg_st* timer_Cfg_st);

/**
 *  @brief 			   This function set callback function for interrupt.
 *  @param[in]		 Fptr (pointer to function), pgpio pointer to input configuration structure.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t timer_interrupt_setcallback( Timer_cfg_st* timer_Cfg_st,void(*Fptr)(void));


 

 
 
 #endif /* GPT_H_ */
 
 
 
 
 
 