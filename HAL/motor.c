
#include "motor.h"

#include "gpio.h"

/************************************************************************
* description : this function used to init the motor as output
* input       : pointer to structure which have port and two pin number
* return      :MOTOR_OK or MOTR_NOK                                                                     
************************************************************************/

en_motor_error_t MOTOR_INIT(const str_motor_config_t *strPtr_l_motor_config)
{
		en_motor_error_t en_l_ret = MOTOR_E_OK;
		if((strPtr_l_motor_config) != NULL)
		{
			gpio_init_st st_l_motor_0_pin = {
				 .port_num 		= strPtr_l_motor_config->motor_port_0_ ,
				 .pin_num  		= strPtr_l_motor_config->motor_pin_0_ ,
				 .pin_stat 		= PORT_DIGITAL,
				 .pin_dir  		= OUTPUT,
				 .pin_con	 		= PULL_DOWN,
				 .pin_type 		= GPIO,
				 .pin_lock 		= UNLOCK,
				 .pin_current = PORT_CURRENT_8mA,
				 .pin_data 		= LOW,		
			};
			gpio_init_st st_l_motor_1_pin = {
				 .port_num 		= strPtr_l_motor_config->motor_port_1_ ,
				 .pin_num  		= strPtr_l_motor_config->motor_pin_1_ ,
				 .pin_stat 		= PORT_DIGITAL,
				 .pin_dir  		= OUTPUT,
				 .pin_con	 		= PULL_DOWN,
				 .pin_type 		= GPIO,
				 .pin_lock 		= UNLOCK,
				 .pin_current = PORT_CURRENT_8mA,
				 .pin_data 		= LOW,		
			};
			en_l_ret = pin_init(&st_l_motor_0_pin);
			if(ERROR==en_l_ret)
			{
				 en_l_ret = MOTOR_E_NOK;
			}
			else
			{
				en_l_ret = MOTOR_E_OK;
			}
			en_l_ret = pin_init(&st_l_motor_1_pin);
			if(ERROR==en_l_ret)
			{
				 en_l_ret = MOTOR_E_NOK;
			}
			else
			{
				en_l_ret = MOTOR_E_OK;
			}
		}
		else
		{
			en_l_ret = MOTOR_E_NOK;
		}
		return en_l_ret;
}





/************************************************************************
* description : this function used to move the motor forward
* input       : pointer to structure which have port and two pin number and speed of motor
* return      :MOTOR_OK or MOTR_NOK
************************************************************************/
en_motor_error_t MOTOR_FORWARD(const str_motor_config_t *strPtr_l_motor_config)
{
	en_motor_error_t en_l_ret = MOTOR_E_OK;
		if((strPtr_l_motor_config) != NULL)
		{ 
			en_l_ret = pin_write(HIGH,strPtr_l_motor_config->motor_port_0_,strPtr_l_motor_config->motor_pin_0_);
			if(ERROR==en_l_ret)
			{
				 en_l_ret = MOTOR_E_NOK;
			}
			else
			{
				 en_l_ret = MOTOR_E_OK;
			}
			en_l_ret = pin_write(LOW,strPtr_l_motor_config->motor_port_1_,strPtr_l_motor_config->motor_pin_1_);
			if(ERROR==en_l_ret)
			{
				 en_l_ret = MOTOR_E_NOK;
			}
			else
			{
				 en_l_ret = MOTOR_E_OK;
			}
		}
		else
		{
			en_l_ret = MOTOR_E_NOK;
		}
		return en_l_ret;
}


/************************************************************************
* description : this function used to move the motor backward
* input       : pointer to structure which have port and two pin number and speed of motor
* return      :MOTOR_OK or MOTR_NOK
************************************************************************/
en_motor_error_t MOTOR_BACKWARD(const str_motor_config_t *strPtr_l_motor_config)
{
	en_motor_error_t en_l_ret = MOTOR_E_OK;
		if((strPtr_l_motor_config) != NULL)
		{ 
			en_l_ret = pin_write(LOW,strPtr_l_motor_config->motor_port_0_,strPtr_l_motor_config->motor_pin_0_);
			if(ERROR==en_l_ret)
			{
				 en_l_ret = MOTOR_E_NOK;
			}
			else
			{
				 en_l_ret = MOTOR_E_OK;
			}
			en_l_ret = pin_write(HIGH,strPtr_l_motor_config->motor_port_1_,strPtr_l_motor_config->motor_pin_1_);
			if(ERROR==en_l_ret)
			{
				 en_l_ret = MOTOR_E_NOK;
			}
			else
			{
				 en_l_ret = MOTOR_E_OK;
			}
		}
		else
		{
			en_l_ret = MOTOR_E_NOK;
		}
		return en_l_ret;
}


/************************************************************************
* description : this function used to stop the motor
* input       : pointer to structure which have port and two pin number 
* return      :MOTOR_OK or MOTR_NOK
************************************************************************/
en_motor_error_t MOTOR_STOP(const str_motor_config_t *strPtr_l_motor_config)
{
	en_motor_error_t en_l_ret = MOTOR_E_OK;
		if((strPtr_l_motor_config) != NULL)
		{ 
			en_l_ret = pin_write(LOW,strPtr_l_motor_config->motor_port_0_,strPtr_l_motor_config->motor_pin_0_);
			if(ERROR==en_l_ret)
			{
				 en_l_ret = MOTOR_E_NOK;
			}
			else
			{
				 en_l_ret = MOTOR_E_OK;
			}
			en_l_ret = pin_write(LOW,strPtr_l_motor_config->motor_port_1_,strPtr_l_motor_config->motor_pin_1_);
			if(ERROR==en_l_ret)
			{
				 en_l_ret = MOTOR_E_NOK;
			}
			else
			{
				 en_l_ret = MOTOR_E_OK;
			}
		}
		else
		{
			en_l_ret = MOTOR_E_NOK;
		}
		return en_l_ret;
}













