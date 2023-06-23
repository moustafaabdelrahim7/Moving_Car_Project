/**
 ** @file                   WDT_Tester.c
 ** @brief                  This file implements watchdog timer Module tester
 ** @author                 Mohamed Sayed
 ** @date                   Jan 23, 2023
 ** @version                0.1
 */

/*- INCLUDES
----------------------------------------------*/
#include "app.h"
#include "led.h"
#include "button.h"
#include "common.h"

/*-------------------------------*/
/*- APIs IMPLEMENTATION
-----------------------------------*/


int main (void)
	{

		APP_init();
		//for moustafa
		while (1)
		{
			APP_start();
		}
	}


	
	
	
	
	
	
	
	
	
	
	
	
	
	
//#define GPTMTAMR_TIMER0  *((volatile uint32_t*)(0x40030000+0x004))
//#define  TACDIR   4
//#define   TAEN    0

//#define  GPTMCTL_TIMER0        *((volatile uint32_t*)(0x40030000+0x00C))

//#define  GPTMCFG_TIMER0        *((volatile uint32_t*)(0x40030000)) //CHECK THIS ADDRESS
//	
//#define  GPTMTAILR_TIMER0        *((volatile uint32_t*)(0x40030000+0x028)) 
//	
//#define  GPTMRIS_TIMER0         *((volatile uint32_t*)(0x40030000+0x01C)) 
//	
//#define   RCGCTIMER        *((volatile uint32_t*)(0x400FE000+0x604)) 



///* notes from gpt
//    // Enable Timer 0
//    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0;

//*/



//void gpt_init (void)
//{
//	//Bits in this register should only be changed when the TAEN bit in the GPTMCTL register is cleared.
//	
//	// ENABLE TIMER CLOCK
//	SET_BIT(RCGCTIMER ,0);
//		
//	/* step 1: Timer0 A  is disabled*/
//	CLEAR_BIT (GPTMCTL_TIMER0 ,TAEN);
//	
//	/* STEP 2: Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.*/
//	GPTMCFG_TIMER0 = 0x00000000;
//	
//	/* STEP 3: Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR)*/
//	// GPTM Timer A Mode SET AS ONE_SHOT MODE---> PUT 0X1 IN TAMR BITS (0,1)
//	SET_BIT( GPTMTAMR_TIMER0,0);
//	CLEAR_BIT (GPTMTAMR_TIMER0,1);
//	
//	// configure the timer to count down
//	CLEAR_BIT (GPTMTAMR_TIMER0,4);
//	
//	/* STEP 4: Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).*/
//	GPTMTAILR_TIMER0 = 8000000;

//}

//void timer0_delay_ms (uint32_t ms)
//{
//	   
//  	// ENABLE TIMER CLOCK
//	SET_BIT(RCGCTIMER ,0);
//		
//	/* step 1: Timer0 A  is disabled*/
//	CLEAR_BIT (GPTMCTL_TIMER0 ,TAEN);
//	
//	/* STEP 2: Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.*/
//	GPTMCFG_TIMER0 = 0x00000000;
//	
//	/* STEP 3: Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR)*/
//	// GPTM Timer A Mode SET AS ONE_SHOT MODE---> PUT 0X1 IN TAMR BITS (0,1)
//	SET_BIT( GPTMTAMR_TIMER0,0);
//	CLEAR_BIT (GPTMTAMR_TIMER0,1);

//	// Set the delay time in milliseconds
//    uint32_t delay_ticks = (ms * SystemCoreClock) / 1000;
//	
//	/* STEP 4: Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).*/
//	GPTMTAILR_TIMER0 = delay_ticks;
//	
//	//Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
//	SET_BIT (GPTMCTL_TIMER0 ,TAEN);
//	
//	//Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled
//	while (READ_BIT(GPTMRIS_TIMER0,0) == 0) ;
//	
//		/* step 1: Timer0 A  is disabled*/
//	CLEAR_BIT (GPTMCTL_TIMER0 ,TAEN);
//	
//}

//void stop_timer0 (void)
//{
//		/* step 1: Timer0 A  is disabled*/
//	CLEAR_BIT (GPTMCTL_TIMER0 ,TAEN);
//	
//}
// // 0X40000000, 0X400FFFFF

//int main(void)
//{
//	APP_init();
//	
//	gpt_init ();
//	
//	
//	while(1)
//	{
//	//APP_start();
//		timer0_delay_ms(5000);
//	}
//}

///**
// ** @file                   WDT_Tester.c
// ** @brief                  This file implements watchdog timer Module tester
// ** @author                 Mohamed Sayed
// ** @date                   Jan 23, 2023
// ** @version                0.1
// */

///*- INCLUDES
//----------------------------------------------*/


//#define STCTRL                   *((volatile uint32_t*)((0xE000E000)+0x010))
//	#define COUNT                               16



//#define GPT_OFFSET(x)              (x<8?((0x40030000)+((x)*0x1000)):((0x4004C000)+((x-8)*0x1000)))

//#define GPTMRIS(x)                 *((volatile uint32_t*)(GPT_OFFSET(x)+0x01C))


///*- LOCAL MACROS
//------------------------------------------*/

///*- GLOBAL STATIC VARIABLES
//-------------------------------*/
////wdt_cfg_t wdt_cfg;


///*- GLOBAL EXTERN VARIABLES
//-------------------------------*/
///*- APIs IMPLEMENTATION
//-----------------------------------*/
//volatile uint8_t Press_count=0;



//uint8_t count=0;
//void f (void)
//{
//static uint8_t flag=0;
//	flag++;
//	if (flag==50)
//	{
//		LED_ON(&ledblue);
//  }
//	else if (flag==100)
//	{
//		flag=0;
//		LED_OFF(&ledblue);
//	}
//}

///****************************/
//#define STRELOAD                 *((volatile uint32_t*)((0xE000E000)+0x014))
//#define STCURRENT                *((volatile uint32_t*)((0xE000E000)+0x018))

// 


//int main(void)
//{
//	LED_Init(&ledred);
//	LED_Init(&ledblue);
//	LED_Init(&ledgreen);
//	
//	//count= (200*60000)/(SystemCoreClock*3000000);
//	
//	Timer_cfg_st TIMER;
//	TIMER.timer_mode=PERIODIC_MODE;
//	TIMER.timer_num=TIMER0_m;
//	TIMER.timer_res=RES16BIT;
//	TIMER.timer_use=INDIVADUAL;
//	TIMER.timer_type=TIMER_A;
//	TIMER.count_dir=COUNT_DOWN;
//	TIMER.detect_change=AFTER_CYCLE;
//	TIMER.enable_timer_type=JUST_ENABLE;
//	TIMER.timer_value=59999;
//	TIMER.timer_prescaler=200;
//	
//	timer_init(&TIMER);
//	
//timer_interrupt_setcallback(&TIMER,f);
//	
//timer_A_interrupt_enable(&TIMER);
//	
//	timer_start(&TIMER);
//	
//while(1)
//{
//		
//}
//}
