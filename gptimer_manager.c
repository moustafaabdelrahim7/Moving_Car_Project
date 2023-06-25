/**
 ** @file                   gptimer_manager.c
 ** @brief                  This is source file for gptimer 
 ** @author                 Nada Abdelazim
 ** @date                   June 21, 2023
 ** @version                0.1
 */
 
/*******INCLUDES*******/
#include "gptimer_manager.h"

#include "button.h"

#include "led.h"


/***************Defines**************************/
#define MAX_ONESHOT_TIME_S  3
#define PRESCALER_US     2
#define MINIMUM_US       1
#define PRESCALER_MS     20
#define MINIMUM_MS       99
#define PRESCALER_S      200
#define MINIMUM_S        9999
#define TIME_FACTOR      2
#define ENABLE           1
#define DISABLE          0

/***************Pointer to function**************************/
 static void(*Fptr_us)(void)=NULLPTR;
 static void(*Fptr_ms)(void)=NULLPTR;
 static void(*Fptr_s)(void)=NULLPTR;
 static void(*Fptr_sec_oneshot_mod)(void)=NULLPTR;
/***************Global variables****************************/
static volatile uint16_t  count_us=0;
static volatile uint16_t  count_ms=0;
static volatile uint16_t  count_s=0;
static volatile uint8_t  flag_us=DISABLE;
static volatile uint8_t  flag_ms=DISABLE;
static volatile uint8_t  flag_s=0;
static volatile uint8_t port=100;
static volatile uint8_t pin=100;
static volatile uint16_t count_on=0;
static volatile uint16_t count_off=0;
static volatile uint8_t flag_sec_one_shot=0;

volatile uint8_t flag=0;
volatile uint8_t flag_ON=0;
volatile uint8_t flag_OFF=0;

/***************Local Functions****************************/
static void Time_us(void);
static void Time_ms(void);
static void Time_s(void);
static void PWM_gen(void);
static void Time_sec_oneshot_mode(void);


/*---------------------------------------------------------/
/- APIs declerations -----------------------------------/
/---------------------------------------------------------*/

/**
 *  @brief 			   This function initializes TIMER 0 according to user's cnfigurations.
 *  @param[in]		 none.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
 
uint8_t timer0_init(void)
{
	uint8_t uint8_tstatus=SUCCESS;
	
	Timer_cfg_st TIMER_0;
	
	TIMER_0.timer_mode=         TIMER0_MODE;
	TIMER_0.timer_num=          TIMER0_NUM;
	TIMER_0.timer_res=          TIMER0_RES;
	TIMER_0.timer_use=          TIMER0_USE;
	TIMER_0.timer_type=         TIMER0_TYPE;
	TIMER_0.count_dir=          TIMER0_DIR;
	TIMER_0.detect_change=      TIMER0_DETECT_CHANGE;
	TIMER_0.enable_timer_type=  TIMER0_ENABLE_TIMER_TYPE;
	TIMER_0.timer_value=        TIMER0_VALUE;
	TIMER_0.timer_prescaler=    TIMER0_PRESCALER;
	
	uint8_tstatus= timer_init(&TIMER_0);
	
	return uint8_tstatus;
  
}

/**
 *  @brief 			   This function to generate pwm in specific pin.
 *  @param[in]		 port and pin number to generate pwm on it and the desired duty cycle in percenatge.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */

uint8_t pwm_pin (uint16_t a_u16_duty_cycle,uint8_t a_u8_pin_num, uint8_t a_u8_port_num)
{
	uint8_t uint8_tstatus=SUCCESS;
	uint8_t u8_Secureflag=0;
	if ((a_u8_pin_num < PIN_TOTAL) && (a_u8_port_num < PORT_TOTAL))
	{
		u8_Secureflag=1;
	  port=a_u8_port_num;
	  pin=a_u8_pin_num;
	  count_on= (((uint64_t)SIGNAL_DURATION * a_u16_duty_cycle)/PERCENTAGE);
	  count_off=SIGNAL_DURATION-count_on;
		if(u8_Secureflag==1)
		{
			time_ms(ONE,PWM_gen);
		}
		else
		{
			//do nothing
		}
	
	}
	else
	{
		uint8_tstatus=ERROR;
	}
	return uint8_tstatus;
}

static void PWM_gen(void)
{
	static uint64_t count=0;
	count++;
	if (count==count_off)
	{
		pin_write (HIGH,port,pin);
	}
	else if (count==count_off+count_on)
	{
		pin_write (LOW,port,pin);
		count=0;
	}
	
}

/**
 *  @brief 			   This function stop the pwm generation.
 *  @param[in]		 none
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t pwm_timer_stop (void)
{
	 uint8_t uint8_tstatus=SUCCESS;
	
	Timer_cfg_st TIMER={.timer_num=TIMER_MS,.timer_type=TIMER_A};
	
	 uint8_tstatus=timer_stop( &TIMER);
	return uint8_tstatus;

}

/**
 *  @brief 			   This function generation the interrupt after the input time by using periodic mode timer.
 *  @param[in]		 The Required time in microsecond, Fptr (pointer to function).
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t time_us(uint16_t time , void(*fptr)(void))
{
	uint8_t uint8_tstatus=SUCCESS;
	if (fptr!=NULLPTR && flag_us==DISABLE  )
 {
	 flag_us=ENABLE;
	 Fptr_us=fptr;
	 count_us=time;
	Timer_cfg_st TIMER=
	{
	.timer_mode=PERIODIC_MODE,
	.timer_num=TIMER_US,
	.timer_res=RES16BIT,
	.timer_use=INDIVADUAL,
	.timer_type=TIMER_A,
	.count_dir=COUNT_DOWN,
	.detect_change=AFTER_CYCLE,
	.enable_timer_type=JUST_ENABLE,
	.timer_value=MINIMUM_US,
	.timer_prescaler=PRESCALER_US
	};
	timer_init(&TIMER);
	timer_interrupt_setcallback(&TIMER,&Time_us);
	timer_interrupt_enable(&TIMER);
	timer_start(&TIMER);
 }
	else
	{
		uint8_tstatus=ERROR;
	}
	return uint8_tstatus;
}

static void Time_us(void)
{
	static uint16_t count_timeout=0;
	count_timeout++;
	if (count_timeout==count_us)
	{
		Fptr_us();
		count_timeout=0;
	}
}

/**
 *  @brief 			   This function generation the interrupt after the input time by using periodic mode timer.
 *  @param[in]		 The Required time in millesecond, Fptr (pointer to function).
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t time_ms(uint16_t time , void(*fptr)(void))	
{
	uint8_t uint8_tstatus=SUCCESS;
	if (fptr!=NULLPTR && flag_ms==DISABLE)
 {
	 flag_ms=ENABLE;
	 Fptr_ms=fptr;
	 count_ms=time*TIME_FACTOR;
	Timer_cfg_st TIMER=
	{
	.timer_mode=PERIODIC_MODE,
	.timer_num=TIMER_MS,
	.timer_res=RES16BIT,
	.timer_use=INDIVADUAL,
	.timer_type=TIMER_A,
	.count_dir=COUNT_DOWN,
	.detect_change=AFTER_CYCLE,
	.enable_timer_type=JUST_ENABLE,
	.timer_value=MINIMUM_MS,
	.timer_prescaler=PRESCALER_MS
	};
	timer_init(&TIMER);
	timer_interrupt_setcallback(&TIMER,&Time_ms);
	timer_interrupt_enable(&TIMER);
	timer_start(&TIMER);
 }
	else
	{
		uint8_tstatus=ERROR;
	}
	return uint8_tstatus;
}

static void Time_ms(void)
{
	static uint16_t count_timeout=0;
	count_timeout++;
	if (count_timeout==count_ms)
	{
		Fptr_ms();
		count_timeout=0;
	}
}

/**
 *  @brief 			   This function generation the interrupt after the input time by using periodic mode timer.
 *  @param[in]		 The Required time in second, Fptr (pointer to function).
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t time_s(uint16_t time , void(*fptr)(void))
{
	uint8_t uint8_tstatus=SUCCESS;
	if (fptr!=NULLPTR && flag_s==DISABLE)
 {
	 flag_s=ENABLE;
	 Fptr_s=fptr;
	 count_s=time*TIME_FACTOR;
	Timer_cfg_st TIMER=
	{
	.timer_mode=PERIODIC_MODE,
	.timer_num=TIMER_S,
	.timer_res=RES16BIT,
	.timer_use=INDIVADUAL,
	.timer_type=TIMER_A,
	.count_dir=COUNT_DOWN,
	.detect_change=AFTER_CYCLE,
	.enable_timer_type=JUST_ENABLE,
	.timer_value=MINIMUM_S,
	.timer_prescaler=PRESCALER_S
	};
	timer_init(&TIMER);
	timer_interrupt_setcallback(&TIMER,&Time_s);
	timer_interrupt_enable(&TIMER);
	timer_start(&TIMER);
 }
	else
	{
		uint8_tstatus=ERROR;
	}
	return uint8_tstatus;
}
static void Time_s(void)
{
	static uint16_t count_timeout=0;
	count_timeout++;
	if (count_timeout==count_s)
	{
		Fptr_s();
		count_timeout=0;
	}
}

/**
 *  @brief 			   This function generation the interrupt after the input time by using oneshot mode timer.
 *  @param[in]		 The Required time in second, Fptr (pointer to function).
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t time_sec_oneshot_mode(uint16_t time,void(*fptr)(void)) //maximum 3 sec
{
	uint8_t uint8_tstatus=SUCCESS;
	if ((fptr!=NULLPTR) && (time <= MAX_ONESHOT_TIME_S) && (flag_sec_one_shot == DISABLE))
	{
		
		flag_sec_one_shot = ENABLE ;
	uint16_t  count_sec_oneshot_mod=0;
	Fptr_sec_oneshot_mod=fptr;
	count_sec_oneshot_mod=((uint64_t)time*4000000)/PRESCALER_S;
	Timer_cfg_st TIMER=
	{
	.timer_mode=ONESHOT_MODE,
	.timer_num=TIMER_S,
	.timer_res=RES16BIT,
	.timer_use=INDIVADUAL,
	.timer_type=TIMER_A,
	.count_dir=COUNT_DOWN,
	.detect_change=AFTER_CYCLE,
	.enable_timer_type=JUST_ENABLE,
	.timer_value=count_sec_oneshot_mod,
	.timer_prescaler=PRESCALER_S
	};
	timer_init(&TIMER);
	timer_interrupt_setcallback(&TIMER,&Time_sec_oneshot_mode);
	timer_interrupt_enable(&TIMER);
	timer_start(&TIMER);
}
	else
	{
		uint8_tstatus=ERROR;
	}
	return uint8_tstatus;
}

static void Time_sec_oneshot_mode(void)
{
	Fptr_sec_oneshot_mod();
	flag_sec_one_shot = DISABLE;
	
}

/*******************************************************************************************************************************/











