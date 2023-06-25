/**
 ** @file                   gptimer.c
 ** @brief                  This is source file for gptimer for TM4C123GH6PM
 ** @author                 Mohamed Sayed
 ** @date                   June 21, 2023
 ** @version                0.1
 */


#include "gptimer.h"



/*GPT Registers****************/
/********************************/

#define GPT_OFFSET(x)              (x<8?((0x40030000)+((x)*0x1000)):((0x4004C000)+((x-8)*0x1000)))



/*******Registers MAP**********/
/*Timer Clock register*/
#define RCGCTIMER                  *((volatile uint32_t*)(0x400FE000+0x604))
#define RCGCWTIMER                 *((volatile uint32_t*)(0x400FE000+0x65C))

#define GPTMCFG(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x000))
#define GPTMTAMR(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x004))
#define GPTMTBMR(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x008))
#define GPTMCTL(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x00C))
#define GPTMSYNC(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x010))
#define GPTMIMR(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x018))
#define GPTMRIS(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x01C))
#define GPTMMIS(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x020))
#define GPTMICR(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x024))
#define GPTMTAILR(x)               *((volatile uint32_t*)(GPT_OFFSET(x)+0x028))
#define GPTMTBILR(x)               *((volatile uint32_t*)(GPT_OFFSET(x)+0x02C))
#define GPTMTAMATCHR(x)            *((volatile uint32_t*)(GPT_OFFSET(x)+0x030))
#define GPTMTBMATCHR(x)            *((volatile uint32_t*)(GPT_OFFSET(x)+0x034))	
#define GPTMTAPR(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x038))
#define GPTMTBPR(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x03C))
#define GPTMTAPMR(x)               *((volatile uint32_t*)(GPT_OFFSET(x)+0x040))
#define GPTMTBPMR(x)               *((volatile uint32_t*)(GPT_OFFSET(x)+0x044))
#define GPTMTAR(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x048))
#define GPTMTBR(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x04C))
#define GPTMTAV(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x050))
#define GPTMTBV(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x054))
#define GPTMRTCPD(x)               *((volatile uint32_t*)(GPT_OFFSET(x)+0x058))	
#define GPTMTAPS(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x05C))
#define GPTMTBPS(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x060))
#define GPTMTAPV(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x064))
#define GPTMTBPV(x)                *((volatile uint32_t*)(GPT_OFFSET(x)+0x068))
#define GPTMPP(x)                  *((volatile uint32_t*)(GPT_OFFSET(x)+0xFC0))

/*Timer A Bits*/
#define TAEN                        0
#define TACDIR                      4
#define TAILD                       8
#define TAWOT                       6
#define TATOIM                      0
#define TATOCINT                    0
/*Timer B Bits*/
#define TBEN                        8
#define TBCDIR                      4
#define TBILD                       8
#define TBWOT                       6
#define TBTOIM                      8
#define TBTOCINT                    8


#define PRESCALER_MASK             0xF
                                                   

	

/**********************************************************************************************/

/**Pointer to Function***/
/*Timer_A**/
/*Basic Timer**/
static  void(*fptr_Timer0_A)(void);
static  void(*fptr_Timer1_A)(void);
static  void(*fptr_Timer2_A)(void);
static  void(*fptr_Timer3_A)(void);
static  void(*fptr_Timer4_A)(void);
static  void(*fptr_Timer5_A)(void);
/*Wild Timer**/
static  void(*fptr_WTimer0_A)(void);
static  void(*fptr_WTimer1_A)(void);
static  void(*fptr_WTimer2_A)(void);
static  void(*fptr_WTimer3_A)(void);
static  void(*fptr_WTimer4_A)(void);
static  void(*fptr_WTimer5_A)(void);
/*Timer_B**/
/*Basic Timer**/
static  void(*fptr_Timer0_B)(void);
static  void(*fptr_Timer1_B)(void);
static  void(*fptr_Timer2_B)(void);
static  void(*fptr_Timer3_B)(void);
static  void(*fptr_Timer4_B)(void);
static  void(*fptr_Timer5_B)(void);
/*Wild Timer**/
static  void(*fptr_WTimer0_B)(void);
static  void(*fptr_WTimer1_B)(void);
static  void(*fptr_WTimer2_B)(void);
static  void(*fptr_WTimer3_B)(void);
static  void(*fptr_WTimer4_B)(void);
static  void(*fptr_WTimer5_B)(void);

/******************************************************************************/
/**
 *  @brief 			   This function initializes the GPT.
 *  @param[in]		 pgpio pointer to input configuration structure.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t timer_init( Timer_cfg_st* timer_Cfg_st)
{
	uint8_t uint8_tstatus=SUCCESS;
	/*step #1*/
	/*Enable the clock for timer*/
	if (timer_Cfg_st->timer_num < WTIMER0_m)
	{
		SET_BIT(RCGCTIMER,timer_Cfg_st->timer_num);
	}
	else if (timer_Cfg_st->timer_num >= WTIMER0_m && timer_Cfg_st->timer_num <= WTIMER5_m )
	{
		SET_BIT(RCGCWTIMER,timer_Cfg_st->timer_num);
	}
	else
	{
		uint8_tstatus=ERROR;
		
	}
	/*step #2*/
	/*Disable The Timer*/
	CLEAR_BIT(GPTMCTL(timer_Cfg_st->timer_num),TAEN);
	CLEAR_BIT(GPTMCTL(timer_Cfg_st->timer_num),TBEN);
	
	/*step #3*/
	/*Set the timer Resoluation*/
	
	if (timer_Cfg_st->timer_use == INDIVADUAL)
	{
		
	if (timer_Cfg_st->timer_res==RES16BIT)
	{
		/*Check if the timer is basic or wild*/
		if (((timer_Cfg_st->timer_num) < (uint8_t)WTIMER0_m) )
		{
		  GPTMCFG(timer_Cfg_st->timer_num)=INDIVADUAL_VALUE;
		}
		else
		{
			uint8_tstatus=ERROR;
		}
		
	}
	else if (timer_Cfg_st->timer_res==RES32BIT)
	{
		/*Check if the timer is basic or wild*/
		if ((timer_Cfg_st->timer_num >= WTIMER0_m) && (timer_Cfg_st->timer_num <= WTIMER5_m))
		{
			GPTMCFG(timer_Cfg_st->timer_num)=INDIVADUAL_VALUE;
		}
		else
		{
			uint8_tstatus=ERROR;
		}
	}
}
	else if (timer_Cfg_st->timer_use == CONCATENATED)
	{
		/*Check if the timer is basic or wild*/
	 if (timer_Cfg_st->timer_res==RES32BIT)
	{
		if ((timer_Cfg_st->timer_num < WTIMER0_m))
		{
			
			GPTMCFG(timer_Cfg_st->timer_num)=CONCATENATED_VALUE;
		}
		else
		{
			uint8_tstatus=ERROR;
		}
		
	}
	else if (timer_Cfg_st->timer_res==RES64BIT)
	{
		/*Check if the timer is basic or wild*/
		if ((timer_Cfg_st->timer_num >= WTIMER0_m) && (timer_Cfg_st->timer_num <= WTIMER5_m))
		{
		GPTMCFG(timer_Cfg_st->timer_num)=CONCATENATED_VALUE;
		}
		else
		{
			uint8_tstatus=ERROR;
		}
	}
		
	}
	else
	{
		uint8_tstatus=ERROR;
	}
	
	/*step #4*/
	/*Set the timer configuration*/
	if (timer_Cfg_st->timer_use == INDIVADUAL)
	{
		if (timer_Cfg_st->timer_type==TIMER_A)
		{
			/*set the timer mode*/
			switch (timer_Cfg_st->timer_mode)
			{
				case ONESHOT_MODE:
					GPTMTAMR(timer_Cfg_st->timer_num)=ONESHOT_PATTERN;
				break;
				case PERIODIC_MODE:
				  GPTMTAMR(timer_Cfg_st->timer_num)=PERIODIC_MODE_PATTERN;
				break;
				case PWM_MODE:
					/*To do the configuration for this mode*/
				break;
				default:
				uint8_tstatus=ERROR;
			}	
			
			/*set the timer count directional*/
			if (timer_Cfg_st->count_dir == COUNT_DOWN)
				{
					CLEAR_BIT(GPTMTAMR(timer_Cfg_st->timer_num),TACDIR);
				}
				else if (timer_Cfg_st->count_dir == COUNT_UP)
				{
					SET_BIT(GPTMTAMR(timer_Cfg_st->timer_num),TACDIR);
				}
				else
				{
					uint8_tstatus=ERROR;	
				}
				
				/*set when the updated timer value will reload*/
				if (timer_Cfg_st->detect_change == AFTER_CYCLE)
				{
					CLEAR_BIT(GPTMTAMR(timer_Cfg_st->timer_num),TAILD);
				}
				else if (timer_Cfg_st->detect_change == AFTER_TIMEOUT)
				{
					SET_BIT(GPTMTAMR(timer_Cfg_st->timer_num),TAILD);
				}
				else
				{
					uint8_tstatus=ERROR;	
				}
				
				/*Set that the timer will start counting after enable or wait an event*/
				switch(timer_Cfg_st->enable_timer_type)
				{
					case JUST_ENABLE:
						CLEAR_BIT(GPTMTAMR(timer_Cfg_st->timer_num),TAWOT);
					break;
					case WAIT_TRIGGER:
						SET_BIT(GPTMTAMR(timer_Cfg_st->timer_num),TAWOT);
					break;
					default:
						uint8_tstatus=ERROR;
				}
				
				/*set the prescaler*/
				/*check the timer is wild or basic*/
				if ((timer_Cfg_st->timer_num < WTIMER0_m))
				{
				  //(timer_Cfg_st->timer_prescaler) &=PRESCALER_MASK;
          GPTMTAPR(timer_Cfg_st->timer_num)=timer_Cfg_st->timer_prescaler;				
				}
				else if ((timer_Cfg_st->timer_res==RES32BIT) && (timer_Cfg_st->timer_num >= WTIMER0_m) && (timer_Cfg_st->timer_num <= WTIMER5_m))
				{
					GPTMTAPR(timer_Cfg_st->timer_num)=timer_Cfg_st->timer_prescaler;
				}
				else
				{
					uint8_tstatus=ERROR;	
				}
				/*set The timer value*/
				/*check on the timer resoluation && if the timer is basic or wild*/
				if ((timer_Cfg_st->timer_res==RES16BIT) && (timer_Cfg_st->timer_num < WTIMER0_m))
				{
					GPTMTAILR(timer_Cfg_st->timer_num)=(uint16_t)timer_Cfg_st->timer_value;
				}
				else if ((timer_Cfg_st->timer_res==RES32BIT) && (timer_Cfg_st->timer_num >= WTIMER0_m) && (timer_Cfg_st->timer_num <= WTIMER5_m))
				{
					GPTMTAILR(timer_Cfg_st->timer_num)=(uint32_t)timer_Cfg_st->timer_value;
				}
				else
				{
					uint8_tstatus=ERROR;	
				}
			
		}
		else if (timer_Cfg_st->timer_type==TIMER_B)
		{
			/*set the timer mode*/
			switch (timer_Cfg_st->timer_mode)
			{
				case ONESHOT_MODE:
					GPTMTBMR(timer_Cfg_st->timer_num)=ONESHOT_PATTERN;
				break;
				case PERIODIC_MODE:
				  GPTMTBMR(timer_Cfg_st->timer_num)=PERIODIC_MODE_PATTERN;
				break;
				case PWM_MODE:
					/*To do the configuration for this mode*/
				break;
				default:
				uint8_tstatus=ERROR;				
			}	
			/*set the timer count directional*/
			if (timer_Cfg_st->count_dir == COUNT_DOWN)
				{
					CLEAR_BIT(GPTMTBMR(timer_Cfg_st->timer_num),TBCDIR);
				}
				else if (timer_Cfg_st->count_dir == COUNT_DOWN)
				{
					SET_BIT(GPTMTBMR(timer_Cfg_st->timer_num),TBCDIR);
				}
				else
				{
					uint8_tstatus=ERROR;	
				}
					/*set when the updated timer value will reload*/
				if (timer_Cfg_st->detect_change == AFTER_CYCLE)
				{
					CLEAR_BIT(GPTMTBMR(timer_Cfg_st->timer_num),TBILD);
				}
				else if (timer_Cfg_st->detect_change == AFTER_TIMEOUT)
				{
					SET_BIT(GPTMTBMR(timer_Cfg_st->timer_num),TBILD);
				}
				else
				{
					uint8_tstatus=ERROR;	
				}
				/*Set that the timer will start counting after enable or wait an event*/
				switch(timer_Cfg_st->enable_timer_type)
				{
					case JUST_ENABLE:
						CLEAR_BIT(GPTMTBMR(timer_Cfg_st->timer_num),TBWOT);
					break;
					case WAIT_TRIGGER:
						SET_BIT(GPTMTBMR(timer_Cfg_st->timer_num),TBWOT);
					break;
					default:
						uint8_tstatus=ERROR;
				}
				/*set The timer value*/
				/*check on the timer resoluation && if the timer is basic or wild*/
				if ((timer_Cfg_st->timer_res==RES16BIT) && (timer_Cfg_st->timer_num < WTIMER0_m))
				{
					GPTMTBILR(timer_Cfg_st->timer_num)=(uint16_t)timer_Cfg_st->timer_value;
				}
				else if ((timer_Cfg_st->timer_res==RES32BIT) && (timer_Cfg_st->timer_num >= WTIMER0_m) && (timer_Cfg_st->timer_num <= WTIMER5_m))
				{
					GPTMTBILR(timer_Cfg_st->timer_num)=(uint32_t)timer_Cfg_st->timer_value;
				}
				else
				{
					uint8_tstatus=ERROR;	
				}
				/*set the prescaler*/
				/*check the timer is wild or basic*/
				if ((timer_Cfg_st->timer_num < WTIMER0_m))
				{
					//timer_Cfg_st->timer_prescaler&=PRESCALER_MASK;
          GPTMTBPR(timer_Cfg_st->timer_num)=timer_Cfg_st->timer_prescaler;				
				}
				else if (((timer_Cfg_st->timer_res)==RES32BIT) && ((timer_Cfg_st->timer_num) >= WTIMER0_m) && ((timer_Cfg_st->timer_num) <= WTIMER5_m))
				{
					GPTMTBPR(timer_Cfg_st->timer_num)=timer_Cfg_st->timer_prescaler;
				}
			else
				{
					uint8_tstatus=ERROR;	
				}
			
		}
		else
		{
			uint8_tstatus=ERROR;
		}
	}
	else if (timer_Cfg_st->timer_use == CONCATENATED)
	{
		/*To do the configuration for this timer use*/
	}
	else
		{
			uint8_tstatus=ERROR;
		}
		return uint8_tstatus;
}

/**
 *  @brief 			   This function start the GPT.
 *  @param[in]		 pgpio pointer to input configuration structure.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t timer_start( Timer_cfg_st* timer_Cfg_st)
{
		uint8_t uint8_tstatus=SUCCESS;
	  if (timer_Cfg_st->timer_type==TIMER_A)
		{
			SET_BIT(GPTMCTL(timer_Cfg_st->timer_num),TAEN);
		}
	  else if (timer_Cfg_st->timer_type==TIMER_B)
		{
			SET_BIT(GPTMCTL(timer_Cfg_st->timer_num),TBEN);
		}
	  else
		{
			uint8_tstatus=ERROR;
		}
		return uint8_tstatus;
}

/**
 *  @brief 			   This function stop the GPT.
 *  @param[in]		 pgpio pointer to input configuration structure.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t timer_stop( Timer_cfg_st* timer_Cfg_st)
{
	uint8_t uint8_tstatus=SUCCESS;
	  if (timer_Cfg_st->timer_type==TIMER_A)
		{
			CLEAR_BIT(GPTMCTL(timer_Cfg_st->timer_num),TAEN);
		}
	  else if (timer_Cfg_st->timer_type==TIMER_B)
		{
			CLEAR_BIT(GPTMCTL(timer_Cfg_st->timer_num),TBEN);
		}
	  else
		{
			uint8_tstatus=ERROR;
		}
		return uint8_tstatus;
}

/**
 *  @brief 			   This function enable the interrupt the GPT.
 *  @param[in]		 pgpio pointer to input configuration structure.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t timer_interrupt_enable( Timer_cfg_st* timer_Cfg_st)
{
	uint8_t uint8_tstatus=SUCCESS;
	  if (timer_Cfg_st->timer_type==TIMER_A)
		{
			SET_BIT(GPTMIMR(timer_Cfg_st->timer_num),TATOIM);
			SET_BIT(GPTMICR(timer_Cfg_st->timer_num),TATOCINT);
			switch (timer_Cfg_st->timer_num)
			{
				case TIMER0_m:
					NVIC_EnableIRQ(TIMER0A_IRQn);
				break;
				case TIMER1_m:
					NVIC_EnableIRQ(TIMER1A_IRQn);
				break;
				case TIMER2_m:
					NVIC_EnableIRQ(TIMER2A_IRQn);
				break;
				case TIMER3_m:
					NVIC_EnableIRQ(TIMER3A_IRQn);
				break;
				case TIMER4_m:
					NVIC_EnableIRQ(TIMER4A_IRQn);
				break;
				case TIMER5_m:
					NVIC_EnableIRQ(TIMER5A_IRQn);
				break;
				case WTIMER0_m:
					NVIC_EnableIRQ(WTIMER0A_IRQn);
				break;
				case WTIMER1_m:
					NVIC_EnableIRQ(WTIMER1A_IRQn);
				break;
				case WTIMER2_m:
					NVIC_EnableIRQ(WTIMER2A_IRQn);
				break;
				case WTIMER3_m:
					NVIC_EnableIRQ(WTIMER3A_IRQn);
				break;
				case WTIMER4_m:
					NVIC_EnableIRQ(WTIMER4A_IRQn);
				break;
				case WTIMER5_m:
					NVIC_EnableIRQ(WTIMER5A_IRQn);
				break;
				default:
				uint8_tstatus=ERROR;
			}
		}
	  else if (timer_Cfg_st->timer_type==TIMER_B)
		{
			SET_BIT(GPTMICR(timer_Cfg_st->timer_num),TBTOCINT);
			SET_BIT(GPTMIMR(timer_Cfg_st->timer_num),TBTOIM);
			switch (timer_Cfg_st->timer_num)
			{
				case TIMER0_m:
					NVIC_EnableIRQ(TIMER0B_IRQn);
				break;
				case TIMER1_m:
					NVIC_EnableIRQ(TIMER1B_IRQn);
				break;
				case TIMER2_m:
					NVIC_EnableIRQ(TIMER2B_IRQn);
				break;
				case TIMER3_m:
					NVIC_EnableIRQ(TIMER3B_IRQn);
				break;
				case TIMER4_m:
					NVIC_EnableIRQ(TIMER4B_IRQn);
				break;
				case TIMER5_m:
					NVIC_EnableIRQ(TIMER5B_IRQn);
				break;
				case WTIMER0_m:
					NVIC_EnableIRQ(WTIMER0B_IRQn);
				break;
				case WTIMER1_m:
					NVIC_EnableIRQ(WTIMER1B_IRQn);
				break;
				case WTIMER2_m:
					NVIC_EnableIRQ(WTIMER2B_IRQn);
				break;
				case WTIMER3_m:
					NVIC_EnableIRQ(WTIMER3B_IRQn);
				break;
				case WTIMER4_m:
					NVIC_EnableIRQ(WTIMER4B_IRQn);
				break;
				case WTIMER5_m:
					NVIC_EnableIRQ(WTIMER5B_IRQn);
				break;
				default:
				uint8_tstatus=ERROR;
			}
		}
	  else
		{
			uint8_tstatus=ERROR;
		}
		__enable_irq();
		return uint8_tstatus;
}

/**
 *  @brief 			   This function disable the interrupt the GPT.
 *  @param[in]		 pgpio pointer to input configuration structure.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t timer_B_interrupt_disable( Timer_cfg_st* timer_Cfg_st)
{
	uint8_t uint8_tstatus=SUCCESS;
	  if (timer_Cfg_st->timer_type==TIMER_A)
		{
			CLEAR_BIT(GPTMIMR(timer_Cfg_st->timer_num),TATOIM);
		}
	  else if (timer_Cfg_st->timer_type==TIMER_B)
		{
			CLEAR_BIT(GPTMIMR(timer_Cfg_st->timer_num),TBTOIM);
		}
	  else
		{
			uint8_tstatus=ERROR;
		}
		return uint8_tstatus;
}

/**
 *  @brief 			   This function set callback function for interrupt.
 *  @param[in]		 Fptr (pointer to function), pgpio pointer to input configuration structure.
 *  @return        ::SUCCESS in case of success, otherwise, review error code
 */
uint8_t timer_interrupt_setcallback( Timer_cfg_st* timer_Cfg_st,void(*Fptr)(void))
{
	uint8_t uint8_tstatus=SUCCESS;
	  if (timer_Cfg_st->timer_type==TIMER_A)
		{
			if (Fptr!= NULLPTR)
			{
				switch (timer_Cfg_st->timer_num)
			{
				case TIMER0_m:
					fptr_Timer0_A=Fptr;
				break;
				case TIMER1_m:
					fptr_Timer1_A=Fptr;
				break;
				case TIMER2_m:
					fptr_Timer2_A=Fptr;
				break;
				case TIMER3_m:
					fptr_Timer3_A=Fptr;
				break;
				case TIMER4_m:
					fptr_Timer4_A=Fptr;
				break;
				case TIMER5_m:
					fptr_Timer5_A=Fptr;
				break;
				case WTIMER0_m:
					fptr_WTimer0_A=Fptr;
				break;
				case WTIMER1_m:
						fptr_WTimer1_A=Fptr;
				break;
				case WTIMER2_m:
					fptr_WTimer2_A=Fptr;
				break;
				case WTIMER3_m:
						fptr_WTimer3_A=Fptr;
				break;
				case WTIMER4_m:
						fptr_WTimer4_A=Fptr;
				break;
				case WTIMER5_m:
						fptr_WTimer5_A=Fptr;
				break;
				default:
				uint8_tstatus=ERROR;
			}
			}
			else
			{
				uint8_tstatus=ERROR;
			}
		}
	  else if (timer_Cfg_st->timer_type==TIMER_B)
		{
			if (Fptr!= NULLPTR)
			{
				switch (timer_Cfg_st->timer_num)
			{
				case TIMER0_m:
					fptr_Timer0_B=Fptr;
				break;
				case TIMER1_m:
					fptr_Timer1_B=Fptr;
				break;
				case TIMER2_m:
					fptr_Timer2_B=Fptr;
				break;
				case TIMER3_m:
					fptr_Timer3_B=Fptr;
				break;
				case TIMER4_m:
					fptr_Timer4_B=Fptr;
				break;
				case TIMER5_m:
					fptr_Timer5_B=Fptr;
				break;
				case WTIMER0_m:
					fptr_WTimer0_B=Fptr;
				break;
				case WTIMER1_m:
						fptr_WTimer1_B=Fptr;
				break;
				case WTIMER2_m:
					fptr_WTimer2_B=Fptr;
				break;
				case WTIMER3_m:
						fptr_WTimer3_B=Fptr;
				break;
				case WTIMER4_m:
						fptr_WTimer4_B=Fptr;
				break;
				case WTIMER5_m:
						fptr_WTimer5_B=Fptr;
				break;
				default:
				uint8_tstatus=ERROR;
			}
			}
			else
			{
				uint8_tstatus=ERROR;
			}
		}
	  else
		{
			uint8_tstatus=ERROR;
		}
		return uint8_tstatus;
}




/*******************************************Timer Handler*******************************************************/

/*Timer_A***/
/*Basic Timer**/
void TIMER0A_Handler(void)
{
	if (fptr_Timer0_A!=NULLPTR)
	{
		fptr_Timer0_A();
		SET_BIT(GPTMICR(TIMER0_m),TATOCINT);
	}
	else
	{
		//do nothing
	}
}
void TIMER1A_Handler(void)
{
	if (fptr_Timer1_A!=NULLPTR)
	{
		fptr_Timer1_A();
		SET_BIT(GPTMICR(TIMER1_m),TATOCINT);
	}
	else
	{
		//do nothing
	}
}
void TIMER2A_Handler(void)
{
	if (fptr_Timer2_A!=NULLPTR)
	{
		fptr_Timer2_A();
		SET_BIT(GPTMICR(TIMER2_m),TATOCINT);
	}
	else
	{
		//do nothing
	}
}
void TIMER3A_Handler(void)
{
	if (fptr_Timer3_A!=NULLPTR)
	{
		fptr_Timer3_A();
		SET_BIT(GPTMICR(TIMER3_m),TATOCINT);
	}
	else
	{
		//do nothing
	}
}
void TIMER4A_Handler(void)
{
	if (fptr_Timer4_A!=NULLPTR)
	{
		fptr_Timer4_A();
	}
	else
	{
		//do nothing
	}
}
void TIMER5A_Handler(void)
{
	if (fptr_Timer5_A!=NULLPTR)
	{
		fptr_Timer5_A();
	}
	else
	{
		//do nothing
	}
}
/*Wild Timer**/
void WTIMER0A_Handler(void)
{
	if (fptr_WTimer0_A!=NULLPTR)
	{
		fptr_WTimer0_A();
	}
	else
	{
		//do nothing
	}
}
void WTIMER1A_Handler(void)
{
	if (fptr_WTimer1_A!=NULLPTR)
	{
		fptr_WTimer1_A();
	}
	else
	{
		//do nothing
	}
}
void WTIMER2A_Handler(void)
{
	if (fptr_WTimer2_A!=NULLPTR)
	{
		fptr_WTimer2_A();
	}
	else
	{
		//do nothing
	}
}
void WTIMER3A_Handler(void)
{
	if (fptr_WTimer3_A!=NULLPTR)
	{
		fptr_WTimer3_A();
	}
	else
	{
		//do nothing
	}
}
void WTIMER4A_Handler(void)
{
	if (fptr_WTimer4_A!=NULLPTR)
	{
		fptr_WTimer4_A();
	}
	else
	{
		//do nothing
	}
}
void WTIMER5A_Handler(void)
{
	if (fptr_WTimer5_A!=NULLPTR)
	{
		fptr_WTimer5_A();
	}
	else
	{
		//do nothing
	}
}

/*Timer_B***/
/*Basic Timer**/

void TIMER0B_Handler(void)
{
	if (fptr_Timer0_B!=NULLPTR)
	{
		fptr_Timer0_B();
	}
	else
	{
		//do nothing
	}
}
void TIMER1B_Handler(void)
{
	if (fptr_Timer1_B!=NULLPTR)
	{
		fptr_Timer1_B();
		SET_BIT(GPTMICR(TIMER1_m),TBTOCINT);
	}
	else
	{
		//do nothing
	}
}
void TIMER2B_Handler(void)
{
	if (fptr_Timer2_B!=NULLPTR)
	{
		fptr_Timer2_B();
	}
	else
	{
		//do nothing
	}
}
void TIMER3B_Handler(void)
{
	if (fptr_Timer3_B!=NULLPTR)
	{
		fptr_Timer3_B();
	}
	else
	{
		//do nothing
	}
}
void TIMER4B_Handler(void)
{
	if (fptr_Timer4_B!=NULLPTR)
	{
		fptr_Timer4_B();
	}
	else
	{
		//do nothing
	}
}
void TIMER5B_Handler(void)
{
	if (fptr_Timer5_B!=NULLPTR)
	{
		fptr_Timer5_B();
	}
	else
	{
		//do nothing
	}
}
/*Wild Timer**/
void WTIMER0B_Handler(void)
{
	if (fptr_WTimer0_B!=NULLPTR)
	{
		fptr_WTimer0_B();
	}
	else
	{
		//do nothing
	}
}
void WTIMER1B_Handler(void)
{
	if (fptr_WTimer1_B!=NULLPTR)
	{
		fptr_WTimer1_B();
	}
	else
	{
		//do nothing
	}
}
void WTIMER2B_Handler(void)
{
	if (fptr_WTimer2_B!=NULLPTR)
	{
		fptr_WTimer2_B();
	}
	else
	{
		//do nothing
	}
}
void WTIMER3B_Handler(void)
{
	if (fptr_WTimer3_B!=NULLPTR)
	{
		fptr_WTimer3_B();
	}
	else
	{
		//do nothing
	}
}
void WTIMER4B_Handler(void)
{
	if (fptr_WTimer4_B!=NULLPTR)
	{
		fptr_WTimer4_B();
	}
	else
	{
		//do nothing
	}
}
void WTIMER5B_Handler(void)
{
	if (fptr_WTimer5_B!=NULLPTR)
	{
		fptr_WTimer5_B();
	}
	else
	{
		//do nothing
	}
}







