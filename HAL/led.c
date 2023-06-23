/**
 ** @file                   led.c
 ** @brief                  This is source file for led for TM4C123GH6PM
 ** @author                 NADA ABDELAZIM
 ** @date                   June 16, 2023
 ** @version                0.1
 */
 
 #include "led.h"
 
 /*---------------------------------------------------------/
/- APIs DEFINITION-----------------------------------/
/---------------------------------------------------------*/
/**
 *  @brief 			   This function initializes LED.
 *  @param[in]		 pin and port numbers
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t led_init(uint8_t port_num,uint8_t pin_num)
{
	
	uint8_t u8_status_t=SUCCESS;
	
	gpio_init_st led;
	
	led.port_num=port_num;
	led.pin_num=pin_num;
	led.pin_current=LED_CURRENT;
	led.pin_con=LED_CONNECTION;
	led.pin_dir=OUTPUT;
	led.pin_data=LED_DATA;
	led.pin_lock=LED_LOCK;
	led.pin_stat=LED_STAT;
	led.pin_type=led_type;
	
	u8_status_t= pin_init(&led);
	
	return u8_status_t;
}
/**
 *  @brief 			   This function turns LED ON.
 *  @param[in]		 pin and port numbers.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t led_on(uint8_t port_num,uint8_t pin_num)
{
	uint8_t u8_status_t=SUCCESS;
	
	u8_status_t= pin_write(HIGH,port_num,pin_num);
	
	return u8_status_t;
}
/**
 *  @brief 			   This function turns LED off.
 *  @param[in]		 pin and port numbers.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t led_off(uint8_t port_num,uint8_t pin_num)
{
	uint8_t u8_status_t=SUCCESS;
	
	u8_status_t= pin_write(LOW,port_num,pin_num);
	
	return u8_status_t;
}



