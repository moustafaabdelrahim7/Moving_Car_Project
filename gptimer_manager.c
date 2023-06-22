
#include "gptimer_manager.h"
#include "led.h"

uint8_t timer0_init(void)
{
	uint8_t uint8_tstatus=SUCCESS;
	
	Timer_cfg_st TIMER_0;
	
	TIMER_0.timer_mode=  TIMER0_MODE;
	TIMER_0.timer_num=   TIMER0_NUM;
	TIMER_0.timer_res=   TIMER0_RES;
	TIMER_0.timer_use=   TIMER0_USE;
	TIMER_0.timer_type=  TIMER0_TYPE;
	TIMER_0.count_dir=   TIMER0_DIR;
	TIMER_0.detect_change=  TIMER0_DETECT_CHANGE;
	TIMER_0.enable_timer_type=  TIMER0_ENABLE_TIMER_TYPE;
	TIMER_0.timer_value=        TIMER0_VALUE;
	TIMER_0.timer_prescaler=    TIMER0_PRESCALER;
	
	uint8_tstatus= timer_init(&TIMER_0);
	
	return uint8_tstatus;
  
}


uint16_t timer0_delay_ms (uint16_t ms)
{
		uint8_t uint8_tstatus=SUCCESS;
  
   if (TIMER0_MODE==ONESHOT_MODE)
		 
	{
	 Timer_cfg_st TIMER_0;
	 
	 TIMER_0.timer_type=  TIMER0_TYPE;
		TIMER_0.timer_num=   TIMER0_NUM;
	
	
		/* step 1: Timer0 A  is disabled*/
	timer_stop(&TIMER_0);

	// Set the delay time in milliseconds
    uint16_t delay_ticks = (ms * 50000) / TIMER0_PRESCALER;
		
	GPTMTAILR_TIMER0 = delay_ticks;
		

		
			

	/* STEP 4: Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).*/
	//GPTMTAILR_TIMER0 = delay_ticks;
						


	
	//Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
	timer_start (&TIMER_0);
	
	//Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled
	while (READ_BIT(GPTMRIS_TIMER0,0) == TATORIS) {};
	
			/* step 1: Timer0 A  is disabled*/
	     timer_stop(&TIMER_0);
	

		 }
	  
		 else  uint8_tstatus=ERROR;
		 
		return uint8_tstatus;
	
}

/* calculations: delay on= duration*(duty_cycle/100) 
                delay off = duration- dealy on 

*/

uint8_t timer0_pwm (uint16_t duty_cycle,uint8_t pin_num, uint8_t port_num)
{
	
	uint8_t uint8_tstatus=SUCCESS;

	//pin_write (HIGH,port_num,pin_num);
	
	led_on(port_num,pin_num);
	
	uint16_t delay_high;
	
	
	
	delay_high= ((duty_cycle*50000)/TIMER0_PRESCALER);
  
	
	uint8_tstatus = timer0_delay_ms(delay_high);
	
	//pin_write (LOW,port_num,pin_num);

	led_off(port_num,pin_num);
	
	timer0_delay_ms(signal_duration-delay_high);
	
	return uint8_tstatus;

	
}


