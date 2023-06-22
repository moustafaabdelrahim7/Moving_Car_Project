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
 
 

/*---------------------------------------------------------/
/- APIs IMPLEMENTATION -----------------------------------/
/---------------------------------------------------------*/

uint8_t timer_init( Timer_cfg_st* timer_Cfg_st);

uint8_t timer_start( Timer_cfg_st* timer_Cfg_st);

uint8_t timer_stop( Timer_cfg_st* timer_Cfg_st);

uint8_t timer_A_interrupt_enable( Timer_cfg_st* timer_Cfg_st);

uint8_t timer_B_interrupt_disable( Timer_cfg_st* timer_Cfg_st);

uint8_t timer_interrupt_setcallback( Timer_cfg_st* timer_Cfg_st,void(*Fptr)(void));


 

 
 
 #endif /* GPT_H_ */
 
 
 
 
 
 