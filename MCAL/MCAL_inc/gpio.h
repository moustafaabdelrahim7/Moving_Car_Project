/**
 ** @file                   gpio.h
 ** @brief                  This is header file for GPIO for TM4C123GH6PM
 ** @author                 Mohamed Sayed
 ** @date                   June 16, 2023
 ** @version                0.1
 */


#ifndef GPIO_H_
#define GPIO_H_

#include "common.h"
#include "gpio_config.h"
#include "TM4C123.h"

/*---------------------------------------------------------/
/- APIs IMPLEMENTATION -----------------------------------/
/---------------------------------------------------------*/
/**
 *  @brief 			   This function initializes the GPIO Pin.
 *  @param[in]		 pgpio pointer to input configuration structure.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t pin_init(gpio_init_st* gpio);

/**
 *  @brief 			   This function enable the gpio interrupt.
 *  @param[in]		 enedge for interrupt edge type, uint8_t port &  uint8_t pin.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t port_interrupt_enable(port_edge_en edge,uint8_t port,uint8_t pin);

/**
 *  @brief 			   This function disable the gpio interrupt.
 *  @param[in]		 uint8_t port &  uint8_t pin.
 *  @return        ::Nothing
 */
void port_interrupt_disable(uint8_t port,uint8_t pin);

/**
 *  @brief 			   This function set callback function for interrupt.
 *  @param[in]		 Fptr (pointer to function), uint8_t port.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t port_interrupt_setcallback(void (*Fptr)(void),uint8_t port,uint8_t pin);

/**
 *  @brief 			   This function write the value of gpio pin.
 *  @param[in]		 data (enum type), uint8_t port &  uint8_t pin.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
 
uint8_t pin_write(PORT_PIN_DATA data,uint8_t port,uint8_t pin);

/**
 *  @brief 			   This function read the value of gpio pin.
 *  @param[in]		 Pdata, uint8_t port &  uint8_t pin.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */

uint8_t pin_read(uint8_t* data,uint8_t port,uint8_t pin);









#endif /* GPIO_H_ */




