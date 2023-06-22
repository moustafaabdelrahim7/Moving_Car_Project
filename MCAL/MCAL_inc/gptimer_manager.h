

#include "gptimer_manager_config.h"
#include "gpio.h"


#define  GPTMTAILR_TIMER0        *((volatile uint32_t*)(0x40030000+0x028)) 
	


#define  GPTMRIS_TIMER0         *((volatile uint32_t*)(0x40030000+0x01C)) 
#define  TATORIS                  0


uint8_t timer0_init ( void) ;

uint8_t timer0_pwm (uint16_t duty_cycle,uint8_t pin_num, uint8_t port_num);

uint16_t timer0_delay_ms (uint16_t ms);