/**
 ** @file                   gptimer_manager_config.h
 ** @brief                  This is header file for gptimer_manager 
 ** @author                 Nada Abdelazim
 ** @date                   June 21, 2023
 ** @version                0.1
 */

#ifndef GPTIMER_MANAGER_CONFIG_H_
#define GPTIMER_MANAGER_CONFIG_H_



/******* TIMERS CONFIGURATIONS DONE BY THE USER*******/
#define TIMER_US     TIMER0_m
#define TIMER_MS     TIMER1_m
#define TIMER_S      TIMER0_m

/******* TIMER0 CONFIGURATIONS DONE BY THE USER*******/
#define    TIMER0_MODE               ONESHOT_MODE       
#define    TIMER0_NUM                TIMER0_m 
#define    TIMER0_RES                RES16BIT
#define    TIMER0_USE                INDIVADUAL
#define    TIMER0_TYPE               TIMER_A
#define    TIMER0_DIR                COUNT_DOWN;
#define    TIMER0_DETECT_CHANGE      AFTER_CYCLE
#define    TIMER0_ENABLE_TIMER_TYPE  JUST_ENABLE
#define    TIMER0_VALUE               59999
#define    TIMER0_PRESCALER           200 


/******* SYSTEM CONFIGURATIONS DONE BY THE USER******/

#define   SIGNAL_DURATION          1000     
#define   SYSTEM_CLOCK             4000







#endif