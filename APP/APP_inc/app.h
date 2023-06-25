/**
 ** @file                   app.h
 ** @brief                  This is header file for app for TM4C123GH6PM
 ** @author                 Nada Abdelazim
 ** @date                   June 16, 2023
 ** @version                0.1
 */


#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "common.h"


typedef enum {
	
	INITIAL_STOP 						= 0 ,
	LONG_SIDE								= 1 ,
	STOP_AFTER_L_S					= 2 ,
	FIRST_ROTATION					= 3 ,
	STOP_AFTER_FIRST_ROT		= 4 ,
	SHORT_SIDE							= 5 ,
	STOP_AFTER_S_S					= 6 ,
	SECOND_ROTATION					= 7 ,
	STOP_AFTER_SECOND_ROT		= 8 ,

}enu_car_mode;

typedef enum {
	CAR_STOP									 	= 0,
	CAR_START										=	1
}enu_car_start_stop;

// stages
void ready_State(void);
void shortSide_start();
void longSide_start();
void car_stop_state (uint32_t u32_a_duration_ms);
uint32_t rotate_90degree_calculation (void);
void rotate_90degree_state (void);

// app
void APP_init(void);
void APP_start(void);



#endif /* APPLICATION_H_ */