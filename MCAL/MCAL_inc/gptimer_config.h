/**
 ** @file                   gpt.h
 ** @brief                  This is header file for GPT for TM4C123GH6PM
 ** @author                 Mohamed Sayed
 ** @date                   June 16, 2023
 ** @version                0.1
 */


#ifndef GPT_CONFIG_H_
#define GPT_CONFIG_H_



#include "common.h"

/*********************************Timers**********************************************************/
#define    TIMER0_m          0
#define    TIMER1_m          1
#define    TIMER2_m          2
#define    TIMER3_m          3
#define    TIMER4_m          4
#define    TIMER5_m          5
#define    WTIMER0_m         6
#define    WTIMER1_m         7
#define    WTIMER2_m         8
#define    WTIMER3_m         9
#define    WTIMER4_m         10
#define    WTIMER5_m         11


/********************************Macros***********************************************************/
#define    CONCATENATED_VALUE               0x0
#define    INDIVADUAL_VALUE                 0x4

#define    ONESHOT_PATTERN                  0x1
#define    PERIODIC_MODE_PATTERN            0x2

/*******************************Enums************************************************************/
typedef enum 
{
	ONESHOT_MODE,
	PERIODIC_MODE,
	PWM_MODE
}Timer_mode_en;

typedef enum
{
	RES16BIT,
	RES32BIT,
	RES64BIT
}Timer_resoluation_en;

typedef enum
{
	INDIVADUAL,
	CONCATENATED
}Timer_use_en;

typedef enum
{
	TIMER_A,
	TIMER_B
	
}timer_type_en;

typedef enum
{
	COUNT_DOWN,
	COUNT_UP
	
}count_directional_en;

typedef enum
{
	AFTER_CYCLE,
	AFTER_TIMEOUT
	
}detect_change_timer_value_en;

typedef enum
{
	JUST_ENABLE,
	WAIT_TRIGGER
	
}enable_timer_type_en;


typedef struct
{
	Timer_mode_en                          timer_mode;
	uint8_t                                timer_num;
	Timer_resoluation_en                   timer_res;
	Timer_use_en                           timer_use;
	timer_type_en                          timer_type;
	count_directional_en                   count_dir;
	detect_change_timer_value_en           detect_change;
	enable_timer_type_en                   enable_timer_type;
	uint64_t                               timer_value;
	uint16_t                               timer_prescaler;
	
}Timer_cfg_st;




 #endif /* GPT_H_ */
 
 
