#include "car_control.h"



/************************************************************************
*description : used to initlize the two motor 
*input       : this function take two pointers to motor structure
*return      : MOTOR_OK, MOTOR_NOK                                                             
************************************************************************/
en_car_error_t CAR_init(const str_motor_config_t *strPtr_a_motor_0_config,const str_motor_config_t *strPtr_a_motor_1_config)
{
	  en_car_error_t en_l_ret = CAR_E_OK;
	  en_motor_error_t en_l_retForMotor = MOTOR_E_OK;
		if((strPtr_a_motor_0_config!= NULL) && (strPtr_a_motor_1_config!= NULL))
		{ 
			en_l_retForMotor = MOTOR_INIT(strPtr_a_motor_0_config);
			if(MOTOR_E_NOK==en_l_retForMotor)
			{
				 en_l_ret = CAR_E_NOK;
			}
			else
			{
				 en_l_ret = CAR_E_OK;
			}
			en_l_retForMotor = MOTOR_INIT(strPtr_a_motor_1_config);
			if(MOTOR_E_NOK==en_l_retForMotor)
			{
				 en_l_ret = CAR_E_NOK;
			}
			else
			{
				 en_l_ret = CAR_E_OK;
			}
			
		}
		else
		{
			en_l_ret = CAR_E_NOK;
		}
		return en_l_ret;
}


/************************************************************************
*description : used to move the car forward 
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
en_car_error_t CAR_forward(const str_motor_config_t *strPtr_a_motor_0_config,const str_motor_config_t *strPtr_a_motor_1_config)
{
		en_car_error_t en_l_ret = CAR_E_OK;
	  en_motor_error_t en_l_retForMotor = MOTOR_E_OK;
		if((strPtr_a_motor_0_config!= NULL) && (strPtr_a_motor_1_config!= NULL))
		{ 
			en_l_retForMotor = MOTOR_FORWARD(strPtr_a_motor_0_config);
			if(MOTOR_E_NOK==en_l_retForMotor)
			{
				 en_l_ret = CAR_E_NOK;
			}
			else
			{
				 en_l_ret = CAR_E_OK;
			}
			en_l_retForMotor = MOTOR_FORWARD(strPtr_a_motor_1_config);
			if(MOTOR_E_NOK==en_l_retForMotor)
			{
				 en_l_ret = CAR_E_NOK;
			}
			else
			{
				 en_l_ret = CAR_E_OK;
			}
			
		}
		else
		{
			en_l_ret = CAR_E_NOK;
		}
		return en_l_ret;
}

/************************************************************************
*description : used to move the car backward 
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
en_car_error_t CAR_backward(const str_motor_config_t *strPtr_a_motor_0_config,const str_motor_config_t *strPtr_a_motor_1_config)
{
	en_car_error_t en_l_ret = CAR_E_OK;
	  en_motor_error_t en_l_retForMotor = MOTOR_E_OK;
		if((strPtr_a_motor_0_config!= NULL) && (strPtr_a_motor_1_config!= NULL))
		{ 
			en_l_retForMotor = MOTOR_BACKWARD(strPtr_a_motor_0_config);
			if(MOTOR_E_NOK==en_l_retForMotor)
			{
				 en_l_ret = CAR_E_NOK;
			}
			else
			{
				 en_l_ret = CAR_E_OK;
			}
			en_l_retForMotor = MOTOR_BACKWARD(strPtr_a_motor_1_config);
			if(MOTOR_E_NOK==en_l_retForMotor)
			{
				 en_l_ret = CAR_E_NOK;
			}
			else
			{
				 en_l_ret = CAR_E_OK;
			}
			
		}
		else
		{
			en_l_ret = CAR_E_NOK;
		}
		return en_l_ret;
}

/************************************************************************
*description : used to turn the car to the right
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
en_car_error_t CAR_right(const str_motor_config_t *strPtr_a_motor_0_config,const str_motor_config_t *strPtr_a_motor_1_config)
{
	  en_car_error_t en_l_ret = CAR_E_OK;
	  en_motor_error_t en_l_retForMotor = MOTOR_E_OK;
		if((strPtr_a_motor_0_config!= NULL) && (strPtr_a_motor_1_config!= NULL))
		{ 
			en_l_retForMotor = MOTOR_BACKWARD(strPtr_a_motor_0_config);
			if(MOTOR_E_NOK==en_l_retForMotor)
			{
				 en_l_ret = CAR_E_NOK;
			}
			else
			{
				 en_l_ret = CAR_E_OK;
			}
			en_l_retForMotor = MOTOR_FORWARD(strPtr_a_motor_1_config);
			if(MOTOR_E_NOK==en_l_retForMotor)
			{
				 en_l_ret = CAR_E_NOK;
			}
			else
			{
				 en_l_ret = CAR_E_OK;
			}
			
		}
		else
		{
			en_l_ret = CAR_E_NOK;
		}
		return en_l_ret;
}

/************************************************************************
*description : used to turn the car to the left
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
en_car_error_t CAR_left(const str_motor_config_t *strPtr_a_motor_0_config,const str_motor_config_t *strPtr_a_motor_1_config)
{
		en_car_error_t en_l_ret = CAR_E_OK;
	  en_motor_error_t en_l_retForMotor = MOTOR_E_OK;
		if((strPtr_a_motor_0_config!= NULL) && (strPtr_a_motor_1_config!= NULL))
		{ 
			en_l_retForMotor = MOTOR_FORWARD(strPtr_a_motor_0_config);
			if(MOTOR_E_NOK==en_l_retForMotor)
			{
				 en_l_ret = CAR_E_NOK;
			}
			else
			{
				 en_l_ret = CAR_E_OK;
			}
			en_l_retForMotor = MOTOR_BACKWARD(strPtr_a_motor_1_config);
			if(MOTOR_E_NOK==en_l_retForMotor)
			{
				 en_l_ret = CAR_E_NOK;
			}
			else
			{
				 en_l_ret = CAR_E_OK;
			}
			
		}
		else
		{
			en_l_ret = CAR_E_NOK;
		}
		return en_l_ret;
}


/************************************************************************
*description : used to stop the car
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
en_car_error_t CAR_stop(const str_motor_config_t *strPtr_a_motor_0_config,const str_motor_config_t *strPtr_a_motor_1_config)
{
		en_car_error_t en_l_ret = CAR_E_OK;
	  en_motor_error_t en_l_retForMotor = MOTOR_E_OK;
		if((strPtr_a_motor_0_config!= NULL) && (strPtr_a_motor_1_config!= NULL))
		{ 
			en_l_retForMotor = MOTOR_STOP(strPtr_a_motor_0_config);
			if(MOTOR_E_NOK==en_l_retForMotor)
			{
				 en_l_ret = CAR_E_NOK;
			}
			else
			{
				 en_l_ret = CAR_E_OK;
			}
			en_l_retForMotor = MOTOR_STOP(strPtr_a_motor_1_config);
			if(MOTOR_E_NOK==en_l_retForMotor)
			{
				 en_l_ret = CAR_E_NOK;
			}
			else
			{
				 en_l_ret = CAR_E_OK;
			}
			
		}
		else
		{
			en_l_ret = CAR_E_NOK;
		}
		return en_l_ret;
}