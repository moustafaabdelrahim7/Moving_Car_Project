/**
 ** @file                   gpio.h
 ** @brief                  This is configuration file for GPIO for TM4C123GH6PM
 ** @author                 Mohamed Sayed
 ** @date                   June 16, 2023
 ** @version                0.1
 */


#ifndef GPIO_CONFIG_H_
#define GPIO_CONFIG_H_

#include "common.h"

/**************************************Macros************************************/

/*************************Accroding to misra rules*******************************/

#define PORTA       0
#define PORTB       1
#define PORTC       2
#define PORTD       3
#define PORTE       4
#define PORTF       5
#define PORT_TOTAL  6

#define PIN0        0
#define PIN1        1
#define PIN2        2
#define PIN3        3
#define PIN4        4
#define PIN5        5
#define PIN6        6
#define PIN7        7
#define PIN_TOTAL   8

    

/**************************************Enums*************************************/
typedef enum
{
	PORT_DIGITAL,
	PORT_ANALOG,	
	PORT_STATUS_TOTAL
}port_status_en;

typedef enum
{
	OUTPUT,
	INPUT,	
	PORT_DIRECTION_TOTAL
}port_direcion_en;


typedef enum
{
	PULL_UP,
	PULL_DOWN,
  OPEN_DRAIN,	
	PORT_CONNECTION_TOTAL
}port_conaction_en;

typedef enum
{
	GPIO,
	ALTERNATE,	
	PORT_TYPE_TOTAL
}port_type_en;

typedef enum
{
	LOCK,
	UNLOCK,
  PORT_LOCK_TOTAL	
}port_lock_en;

//typedef enum
//{
//	INTERRUPT_ENABLE,
//	INTERRUPT_DISABLE,
//  PORT_INTERRUPT_TOTAL	
//}port_interrupt_en;

typedef enum
{
	RISING_EDGE,
	FALLING_EDGE,
	BOTH_RISNG_FALLNG,
	LEVEL,
  PORT_EDGE_TOTAL	
}port_edge_en;

typedef enum
{
	PORT_CURRENT_2mA,
	PORT_CURRENT_4mA,
  PORT_CURRENT_8mA,
  PORT_CURRENT_TOTAL	
}port_current_en;

typedef enum
{
	HIGH,
	LOW,
	PORT_PIN_DATA_TOTAL
}PORT_PIN_DATA;

 typedef void(*Fptr)(void);

typedef struct 
{
	uint8_t                       port_num;
	uint8_t                       pin_num;
	port_status_en                pin_stat;
	port_direcion_en              pin_dir;
	port_conaction_en             pin_con;
	port_type_en                  pin_type;
	port_lock_en                  pin_lock;
	port_current_en               pin_current;
	PORT_PIN_DATA                 pin_data;
}gpio_init_st;

#endif /* GPIO_CONFIG_H_ */
