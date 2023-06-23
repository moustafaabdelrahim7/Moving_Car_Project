/**
 ** @file                   led_config.h
 ** @brief                  This is configuration file for led for TM4C123GH6PM
 ** @author                 Nada Abdelazim
 ** @date                   June 16, 2023
 ** @version                0.1
 */


#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_

#include "gpio.h"
#include "gpio_config.h"

/*******LEDS CONNECTION CONFIG*******/
#define  RED_LED_PORT      PORTF
#define  RED_LED_PIN       PIN1

#define  BLUE_LED_PORT     PORTF
#define  BLUE_LED_PIN      PIN2

#define  GREEN_LED_PORT    PORTF
#define  GREEN_LED_PIN     PIN3

/*******LED PROPERTIES CONFIG*******/
#define  LED_CURRENT       PORT_CURRENT_8mA
#define  LED_CONNECTION    PULL_UP
#define  LED_DATA          LOW
#define  LED_LOCK          UNLOCK
#define  LED_STAT          PORT_DIGITAL
#define  led_type					 GPIO







#endif /* LED_CONFIG_H_ */