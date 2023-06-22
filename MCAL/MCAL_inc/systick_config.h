/**
** @file                   systick.h
 ** @brief                  This is configuration file for systick for cortexm4
 ** @author                 Nada Abdelazim
 ** @date                   June 19, 2023
 ** @version                0.1
 */

#ifndef SYSTICK_CONFIG_H_
#define SYSTICK_CONFIG_H_



/*******CONFIG. CLOCK SOURCE*******/
#define CLOCK_SRC_PIOSC       0
#define CLOCK_SRC_SYS_CLOCK   1

/******* SELECT DESIRED CLOCK SOURCE FROM ABOVE*******/
#define  CLOCK_SRC_SELECTOR   CLOCK_SRC_PIOSC


/*******CONFIG THE DESIRED TIMER RELOAD VALUE*******/
#define TIMER_VALUE   3999999

/************CONFIG DELAY RELOAD VALUE FOR DELAY FUNCTIONS*******/
	 /* calculation: 
	                CLOCK_SRC_PIOSC/4 == 16/4 = 4MH 
	                1sec: 1sec/(1/4MH) = (4000000-1) = 3D08FF  in hex.
	 */
#define  DELAY_SEC     3999999
	 
	 

	 /* calculation: 
	                CLOCK_SRC_PIOSC/4 == 16/4 = 4MH 
	                1ms: 1ms/(1/4MH) = (4000-1) = F9F in hex.
	 */
#define  DELAY_MS    3999


#endif /* SYSTICK_CONFIG_H_ */