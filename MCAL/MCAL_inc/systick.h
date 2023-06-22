/**
 ** @file                   systick.h
 ** @brief                  This is header file for systick for cortexm4
 ** @author                 Nada Abdelazim
 ** @date                   June 19, 2023
 ** @version                0.1
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_
 
#include "systick_config.h"
#include "common.h"

/*******Registers MAP**********/

#define STCTRL    *((volatile uint32_t*)(0xE000E010))
#define STRELOAD  *((volatile uint32_t*)(0xE000E014))
#define STCURRENT *((volatile uint32_t*)(0xE000E018))
	
#define  DUMMY_VALUE      7
	

#define  STCTRL_ENABLE   (0U)
#define  STCTRL_INTEN    (1U)
#define  STCTRL_SRC      (2U)
#define  STCTRL_COUNT_FLAG    (16U)

#define STRELOAD_RELOAD  (0U)

/*---------------------------------------------------------/
/- APIs declerations -----------------------------------/
/---------------------------------------------------------*/

/**
 *  @brief 			   This function initializes the SYSTEM TICK TIMER.
 *  @param[in]		 none.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t systick_init (void);
/**
 *  @brief 			   This function to block delay for one milli second.
 *  @param[in]		 none.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t systick_delay_ms (void);
/**
 *  @brief 			   This function to block delay for one second.
 *  @param[in]		 none.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t systick_delay_sec (void);
/**
 *  @brief 			   This function to enable system tick timer interrupt.
 *  @param[in]		 none.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t systick_interrupt_enable (void);
/**
 *  @brief 			   This function to disable system tick timer interrupt.
 *  @param[in]		 none.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t systick_interrupt_disable (void);
/**
 *  @brief 			   This function to set the call back function for the system tick interrupt.
 *  @param[in]		 pointer to the function to be implemented at the system tick interrupt handler.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */

uint8_t systick_interrupt_setCallback (void (*fptr_fun)(void));






#endif /* SYSTICK_H_ */
