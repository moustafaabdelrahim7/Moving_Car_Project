
/**
 ** @file                   car_control.h
 ** @brief                  This is header file for car_control for TM4C123GH6PM
 ** @author                 Mohammed Abdel-wahab
 ** @date                   June 21, 2023
 ** @version                0.1
 */
 
 
#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_
 
 /**********************************  section 1: Includes ********************************************************/
#include "common.h"
#include "motor.h"
/**********************************  section 2: Macro Declarations ***********************************************/

/**********************************  section 3: Macro Like Function Declarations *************************** *****/


/**********************************  section 4: Data Type Declarations  ******************************************/
typedef enum  
{ 
   CAR_E_NOK =0,
	 CAR_E_OK = 1,
}en_car_error_t;


/**********************************  section 5: Function Declarations ********************************************/


/************************************************************************
*description : used to initlize the two motor 
*input       : this function take two pointers to motor structure
*return      : MOTOR_OK, MOTOR_NOK                                                             
************************************************************************/
en_car_error_t CAR_init(const str_motor_config_t *strPtr_a_motor_0_config,const str_motor_config_t *strPtr_a_motor_1_config);


/************************************************************************
*description : used to move the car forward 
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
en_car_error_t CAR_forward(const str_motor_config_t *strPtr_a_motor_0_config,const str_motor_config_t *strPtr_a_motor_1_config);
/************************************************************************
*description : used to move the car backward 
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
en_car_error_t CAR_backward(const str_motor_config_t *strPtr_a_motor_0_config,const str_motor_config_t *strPtr_a_motor_1_config);


/************************************************************************
*description : used to turn the car to the right
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
en_car_error_t CAR_right(const str_motor_config_t *strPtr_a_motor_0_config,const str_motor_config_t *strPtr_a_motor_1_config);

/************************************************************************
*description : used to turn the car to the left
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
en_car_error_t CAR_left(const str_motor_config_t *strPtr_a_motor_0_config,const str_motor_config_t *strPtr_a_motor_1_config);

/************************************************************************
*description : used to stop the car
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
en_car_error_t CAR_stop(const str_motor_config_t *strPtr_a_motor_0_config,const str_motor_config_t *strPtr_a_motor_1_config);




#endif /* CAR_CONTROL_H_ */