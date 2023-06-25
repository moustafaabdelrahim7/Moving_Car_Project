/**
 ** @file                   motor.h
 ** @brief                  This is header file for motor for TM4C123GH6PM
 ** @author                 Mohammed Abdel-wahab
 ** @date                   June 21, 2023
 ** @version                0.1
 */
 
#ifndef MOTOR_H_
#define MOTOR_H_
 
 /**********************************  section 1: Includes ********************************************************/
#include "common.h"
#include "motor_config.h"
/**********************************  section 2: Macro Declarations ***********************************************/

/**********************************  section 3: Macro Like Function Declarations *************************** *****/


/**********************************  section 4: Data Type Declarations  ******************************************/
typedef enum
{ 
   MOTOR_E_NOK =0,
	 MOTOR_E_OK = 1,
}en_motor_error_t;

typedef struct 
{
	uint8_t        motor_port_0_;
	uint8_t        motor_pin_0_;
	uint8_t        motor_port_1_;
	uint8_t        motor_pin_1_;
}str_motor_config_t;


/**********************************  section 5: Function Declarations ********************************************/


/************************************************************************
* description : this function used to init the motor as output
* input       : pointer to structure which have port and two pin number
* return      :MOTOR_OK or MOTR_NOK                                                                     
************************************************************************/
en_motor_error_t MOTOR_INIT(const str_motor_config_t *strPtr_a_motor_config);

/************************************************************************
* description : this function used to move the motor forward
* input       : pointer to structure which have port and two pin number and speed of motor
* return      :MOTOR_OK or MOTR_NOK
************************************************************************/
en_motor_error_t MOTOR_FORWARD(const str_motor_config_t *strPtr_a_motor_config);


/************************************************************************
* description : this function used to move the motor backward
* input       : pointer to structure which have port and two pin number and speed of motor
* return      :MOTOR_OK or MOTR_NOK
************************************************************************/
en_motor_error_t MOTOR_BACKWARD(const str_motor_config_t *strPtr_a_motor_config);


/************************************************************************
* description : this function used to stop the motor
* input       : pointer to structure which have port and two pin number 
* return      :MOTOR_OK or MOTR_NOK
************************************************************************/
en_motor_error_t MOTOR_STOP(const str_motor_config_t *strPtr_a_motor_config);





#endif /* MOTOR_H_ */












