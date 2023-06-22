/**
 ** @file                   button_config.h
 ** @brief                  This is configuration file for button for TM4C123GH6PM
 ** @author                 Nada Abdelazim
 ** @date                   June 16, 2023
 ** @version                0.1
 */


#ifndef BUTTTON_CONFIG_H_
#define BUTTTON_CONFIG_H_


#include "gpio.h"

/*******BUTTONS CONNECTION CONFIG*******/
#define  SW1_PORT      PORTF
#define  SW1_PIN       PIN4

#define  SW2_PORT      PORTF
#define  SW2_PIN       PIN0


/*******BUTTONS PROPERTIES CONFIG*******/
#define  BUTTON_CURRENT       PORT_CURRENT_8mA
#define  BUTTON_CONNECTION    PULL_UP
#define  BUTTON_DATA          HIGH
#define  BUTTON_LOCK          UNLOCK
#define  BUTTON_STAT          PORT_DIGITAL







#endif /* BUTTON_CONFIG_H_ */