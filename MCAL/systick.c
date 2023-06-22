/**
 ** @file                   systick.c
 ** @brief                  This is source file for systick for cortexm4
 ** @author                 Nada Abdelazim
 ** @date                   June 19, 2023
 ** @version                0.1
 */
 
 
 #include "systick.h"
 #include "common.h"
 

 
 
/***********Pointer to function*********************/
static  void(*fptr_systick)(void);

/*---------------------------------------------------------/
/- APIs definitions -----------------------------------/
/---------------------------------------------------------*/

/**
 *  @brief 			   This function initializes the SYSTEM TICK TIMER.
 *  @param[in]		 none.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t systick_init (void)
{
	uint8_t uint8_tstatus=SUCCESS;
	
	/*Reload the value*/
	STRELOAD= TIMER_VALUE;
	/*clear the current value register*/
	STCURRENT=DUMMY_VALUE;
  // set clock source
  #if   CLOCK_SRC_SELECTOR ==  CLOCK_SRC_SYS_CLOCK
      SET_BIT(STCTRL,STCTRL_SRC);
  #elif   CLOCK_SRC_SELECTOR == CLOCK_SRC_PIOSC 
        CLEAR_BIT(STCTRL,STCTRL_SRC);
  #else
	     uint8_tstatus=ERROR ;
  #endif
	return uint8_tstatus;
}


/**
 *  @brief 			   This function to block delay for one milli second.
 *  @param[in]		 none.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t systick_delay_ms (void)
{
	 // set the value to th reload register
	 /* calculation: 
	                CLOCK_SRC_PIOSC/4 == 16/4 = 4MH 
	                1ms: 1ms/(1/4MH) = (4000-1) = F9F in hex.
	 */
	 // set the value to th reload register               
	 STRELOAD = DELAY_MS;
	 // enable system counter
	 SET_BIT(STCTRL,STCTRL_ENABLE);
	 // waith for the counter flag
	 while (READ_BIT(STCTRL,STCTRL_COUNT_FLAG) != 1) ;
		 // disable the counter
   CLEAR_BIT(STCTRL,STCTRL_ENABLE);	 	 
 }

 
/**
 *  @brief 			   This function to block delay for one second.
 *  @param[in]		 none.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t systick_delay_sec (void)
 {
	 // set the value to th reload register
	 /* calculation: 
	                CLOCK_SRC_PIOSC/4 == 16/4 = 4MH 
	                1sec: 1sec/(1/4MH) = (4000000-1) = 3D08FF  in hex.
	 */
	 // set the value to th reload register               
	 STRELOAD = DELAY_SEC;
	 // enable system counter
	 SET_BIT(STCTRL,STCTRL_ENABLE);
	 // waith for the counter flag
	 while (READ_BIT(STCTRL,STCTRL_COUNT_FLAG) != 1) ;
		 // disable the counter
   CLEAR_BIT(STCTRL,STCTRL_ENABLE);	 
	  // reset the value to th reload register               
	 STRELOAD = 0x00000000;
	 // clear the current value register
	 STCURRENT =0X01;	 
 }
 
 
/**
 *  @brief 			   This function to enable system tick timer interrupt.
 *  @param[in]		 none.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t systick_interrupt_enable (void)
 {
	 SET_BIT(STCTRL,STCTRL_INTEN);
	 
 }
 
 
/**
 *  @brief 			   This function to disable system tick timer interrupt.
 *  @param[in]		 none.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t systick_interrupt_disable (void)
 {
	 	 CLEAR_BIT(STCTRL,STCTRL_INTEN);

 }
 

/**
 *  @brief 			   This function to set the call back function for the system tick interrupt.
 *  @param[in]		 pointer to the function to be implemented at the system tick interrupt handler.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */

uint8_t systick_interrupt_setCallback (void (*fptr_fun)(void))
{
	if (fptr_fun != NULL)
	{
	  fptr_systick = fptr_fun ;
	}
}


 


/********************************************/
void SysTick_Handler(void)
{
	if (fptr_systick != NULL)
	{
	 fptr_systick ();
	}

}
 
