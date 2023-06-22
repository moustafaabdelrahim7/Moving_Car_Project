/**
 ** @file                   gpio.c
 ** @brief                  This is header file for GPIO for TM4C123GH6PM
 ** @author                 Mohamed Sayed
 ** @date                   Jan 23, 2023
 ** @version                0.1
 */

#include "gpio.h"

/*used for simulator --> Map range to be added 0x40000000, 0x400fffff*/

/***********Pointer to function*********************/
static  void(*fptr_A)(void);
static  void(*fptr_B)(void);
static  void(*fptr_C)(void);
static  void(*fptr_D)(void);
static  void(*fptr_E)(void);
static  void(*fptr_F)(void);
/**************************************************/

/****************Glopal Pins for interrupt*********/
static volatile uint8_t portA_pin=PIN_TOTAL;
static volatile uint8_t portB_pin=PIN_TOTAL;
static volatile uint8_t portC_pin=PIN_TOTAL;
static volatile uint8_t portD_pin=PIN_TOTAL;
static volatile uint8_t portE_pin=PIN_TOTAL;
static volatile uint8_t portF_pin=PIN_TOTAL;

/*GPIO Registers****************/
/********************************/
#define GPIO_APB
#ifdef GPIO_APB
#define GPIO_OFFSET(x)              (x<4?((0x40004000)+((x)*0x1000)):((0x40024000)+((x-4)*0x1000)))

#define GPIO_LOCK_PATTERN           (0x4C4F434B)
#define GPIO_UNLOCK_PATTERN         (2)
//#define GPIO_PORE_A_OFFSET        (0x40004000)
//#define GPIO_PORE_B_OFFSET        (0x40005000)
//#define GPIO_PORE_C_OFFSET        (0x40006000)
//#define GPIO_PORE_D_OFFSET        (0x40007000)
//#define GPIO_PORE_E_OFFSET        (0x40024000)
//#define GPIO_PORE_F_OFFSET        (0x40025000)
#elif GPIO_AHB
#error "Not Supported Yet"
#else
#error "Please choose a bus for GPIOs"
#endif



/*******Registers MAP**********/
#define RCGCGPIO                   *((volatile uint32_t*)((0x400FE000)+0x608))

#define GPIODATA(x)                *((volatile uint32_t*)(GPIO_OFFSET(x)+0x3FC))
#define GPIODIR(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x400))
#define GPIOIS(x)                  *((volatile uint32_t*)(GPIO_OFFSET(x)+0x404))
#define GPIOIBE(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x408))
#define GPIOIEV(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x40C))
#define GPIOIM(x)                  *((volatile uint32_t*)(GPIO_OFFSET(x)+0x410))
#define GPIORIS(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x414))
#define GPIOMIS(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x418))
#define GPIOICR(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x41C))
#define GPIOAFSEL(x)               *((volatile uint32_t*)(GPIO_OFFSET(x)+0x420))
#define GPIODR2R(x)                *((volatile uint32_t*)(GPIO_OFFSET(x)+0x500))
#define GPIODR4R(x)                *((volatile uint32_t*)(GPIO_OFFSET(x)+0x504))
#define GPIODR8R(x)                *((volatile uint32_t*)(GPIO_OFFSET(x)+0x508))	
#define GPIOODR(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x50C))
#define GPIOPUR(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x510))
#define GPIOPDR(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x514))
#define GPIOSLR(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x518))
#define GPIODEN(x)                 *((volatile uint32_t*)(GPIO_OFFSET(x)+0x51C))
#define GPIOLOCK(x)                *((volatile uint32_t*)(GPIO_OFFSET(x)+0x520))
#define GPIOCR(x)                  *((volatile uint32_t*)(GPIO_OFFSET(x)+0x524))
#define GPIOAMSEL(x)               *((volatile uint32_t*)(GPIO_OFFSET(x)+0x528))
#define GPIOPCTL(x)                *((volatile uint32_t*)(GPIO_OFFSET(x)+0x52C))	
#define GPIOADCCTL(x)              *((volatile uint32_t*)(GPIO_OFFSET(x)+0x530))
#define GPIODMACTL(x)              *((volatile uint32_t*)(GPIO_OFFSET(x)+0x534))
#define GPIOPeriphID4(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFD0))
#define GPIOPeriphID5(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFD4))
#define GPIOPeriphID6(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFD8))
#define GPIOPeriphID7(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFDC))
#define GPIOPeriphID0(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFE0))
#define GPIOPeriphID1(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFE4))
#define GPIOPeriphID2(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFE8))
#define GPIOPeriphID3(x)           *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFEC))
#define GPIOPCellID0(x)            *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFF0))
#define GPIOPCellID1(x)            *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFF4))
#define GPIOPCellID2(x)            *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFF8))
#define GPIOPCellID3(x)            *((volatile uint32_t*)(GPIO_OFFSET(x)+0xFFC))
	

/**********************************************************************************************/


uint8_t pin_init(gpio_init_st* gpio)
{
	uint8_t uint8_tstatus=SUCCESS;
	if (gpio!=NULLPTR)
	{
     /*step #1*/
		/*Enable the clock*/
		if (gpio->port_num < PORT_TOTAL)
		{
			SET_BIT(RCGCGPIO,gpio->port_num);
			/*step #2*/
			/*set the direction*/
			if ((gpio->pin_num) < PIN_TOTAL)
			{
				switch(gpio->pin_dir)
				{
					case OUTPUT:
						SET_BIT( GPIODIR(gpio->port_num) , gpio->pin_num );
					break;
					case INPUT:
						CLEAR_BIT(GPIODIR(gpio->port_num),gpio->pin_num);
					break;
					default:
					uint8_tstatus=ERROR;	
				}
				/*step #3*/
				/*set the pin type as gpio  or alternate pin*/
				switch (gpio->pin_type)
				{
					case GPIO:
						CLEAR_BIT(GPIOAFSEL(gpio->port_num),gpio->pin_num);
					break;
					case ALTERNATE:
						SET_BIT(GPIOAFSEL(gpio->port_num),gpio->pin_num);
					  //To do the remaining the setting of alternate features
					break;
					default:
					uint8_tstatus=ERROR;	
				}
				/*step #4*/
			/*set the output current*/
				switch(gpio->pin_current)
				{
					case PORT_CURRENT_2mA:
					SET_BIT(GPIODR2R(gpio->port_num),gpio->pin_num);
					break;
					case PORT_CURRENT_4mA:
          SET_BIT(GPIODR4R(gpio->port_num),gpio->pin_num);
					break;						
					case PORT_CURRENT_8mA:
          SET_BIT(GPIODR8R(gpio->port_num),gpio->pin_num);
					break;
          default:
					uint8_tstatus=ERROR;					
				}
			/*step #5*/
			/*set the pin connection*/	
				/*To do the remaining setting of pin connection */
				switch(gpio->pin_con)
				{
					case PULL_UP:
					CLEAR_BIT(GPIOODR(gpio->port_num),gpio->pin_num);
					CLEAR_BIT(GPIOPDR(gpio->port_num),gpio->pin_num);
					SET_BIT(GPIOPUR(gpio->port_num),gpio->pin_num);
					break;
					case PULL_DOWN:
					CLEAR_BIT(GPIOODR(gpio->port_num),gpio->pin_num);
					CLEAR_BIT(GPIOPUR(gpio->port_num),gpio->pin_num);
          SET_BIT(GPIOPDR(gpio->port_num),gpio->pin_num);
					break;	
          case OPEN_DRAIN:
          CLEAR_BIT(GPIOPDR(gpio->port_num),gpio->pin_num);
					CLEAR_BIT(GPIOPUR(gpio->port_num),gpio->pin_num);
					SET_BIT(GPIOODR(gpio->port_num),gpio->pin_num);						
          default:
					uint8_tstatus=ERROR;					
				}
				/*step #6*/
			/*set the pin if digital or analog*/	
				switch(gpio->pin_stat)
				{
					case PORT_DIGITAL:
					CLEAR_BIT(GPIOAMSEL(gpio->port_num),gpio->pin_num);
					SET_BIT(GPIODEN(gpio->port_num),gpio->pin_num);
					break;
					case PORT_ANALOG:
					CLEAR_BIT(GPIODEN(gpio->port_num),gpio->pin_num);
          SET_BIT(GPIOAMSEL(gpio->port_num),gpio->pin_num);
					break;						
          default:
					uint8_tstatus=ERROR;					
				}
				/*step #7*/
			/*Gpio Lock*/
			/*To do the remaining setting of Pins lock */
				switch(gpio->pin_lock)
				{
					case LOCK:
					GPIOLOCK(gpio->port_num)=GPIO_LOCK_PATTERN;
					break;
					case UNLOCK:
					GPIOLOCK(gpio->port_num)=GPIO_UNLOCK_PATTERN;
					break;
					default:
					uint8_tstatus=ERROR;	
				}
				/*step #8*/
				/*set the data of pin*/
				switch (gpio->pin_data)
				{
					case HIGH:
					SET_BIT(GPIODATA(gpio->port_num),gpio->pin_num);
					break;
					case LOW:
					CLEAR_BIT(GPIODATA(gpio->port_num),gpio->pin_num);
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
	}
  else
  {
   uint8_tstatus=ERROR;
  }	
	
	return uint8_tstatus;
}

uint8_t port_interrupt_enable(port_edge_en edge,uint8_t port,uint8_t pin)
{
	    uint8_t uint8_tstatus=SUCCESS;
	      switch(edge)
				{
						case LEVEL:
						SET_BIT(GPIOIS(port),pin);	
						break;
						case RISING_EDGE:
						CLEAR_BIT(GPIOIS(port),pin);	
						CLEAR_BIT(GPIOIBE(port),pin);	
						SET_BIT(GPIOIEV(port),pin);
						SET_BIT(GPIOICR(port),pin);
						break;
						case FALLING_EDGE:
						CLEAR_BIT(GPIOIS(port),pin);	
						CLEAR_BIT(GPIOIBE(port),pin);	
						CLEAR_BIT(GPIOIEV(port),pin);
						SET_BIT(GPIOICR(port),pin);
						break;
						case BOTH_RISNG_FALLNG:
						CLEAR_BIT(GPIOIS(port),pin);	
						SET_BIT(GPIOIBE(port),pin);	
						SET_BIT(GPIOICR(port),pin);
						break;
						default:
						uint8_tstatus=ERROR;	
					}
					SET_BIT(GPIOIM(port),pin);
					switch (port)
					{
						case PORTA:
						NVIC_EnableIRQ(GPIOA_IRQn);
            __enable_irq();
						break;
						case PORTB:
						NVIC_EnableIRQ(GPIOB_IRQn);
            __enable_irq();
						break;
						case PORTC:
						NVIC_EnableIRQ(GPIOC_IRQn);
            __enable_irq();
						break;
						case PORTD:
						NVIC_EnableIRQ(GPIOD_IRQn);
            __enable_irq();
						break;
						case PORTE:
						NVIC_EnableIRQ(GPIOE_IRQn);
            __enable_irq();
						break;
						case PORTF:
						NVIC_EnableIRQ(GPIOF_IRQn);
            __enable_irq();
						break;
						default:
					uint8_tstatus=ERROR;
					}
	return uint8_tstatus;
}

void port_interrupt_disable(uint8_t port,uint8_t pin)
{
	        CLEAR_BIT(GPIOIM(port),pin);
					CLEAR_BIT(GPIOIS(port),pin);	
					CLEAR_BIT(GPIOIBE(port),pin);	
					CLEAR_BIT(GPIOIEV(port),pin);
}

uint8_t port_interrupt_setcallback(void (*Fptr)(void),uint8_t port,uint8_t pin)
{
	uint8_t uint8_tstatus=SUCCESS;
	if (Fptr!=NULLPTR)
	{
	switch (port)
					{
						case PORTA:
						fptr_A=Fptr;
						portA_pin=pin;
						break;
						case PORTB:
						fptr_B=Fptr;
						portB_pin=pin;
						break;
						case PORTC:
						fptr_C=Fptr;
						portC_pin=pin;
						break;
						case PORTD:
						fptr_D=Fptr;
						portD_pin=pin;
						break;
						case PORTE:
						fptr_E=Fptr;
						portE_pin=pin;
						break;
						case PORTF:
						fptr_F=Fptr;
						portF_pin=pin;
						break;
						default:
					uint8_tstatus=ERROR;
					}
	 }
	else
	{
		uint8_tstatus=ERROR;
	}
	return uint8_tstatus;
}
uint8_t pin_write(PORT_PIN_DATA data,uint8_t port,uint8_t pin)
{
	uint8_t uint8_tstatus=SUCCESS;
	switch (data)
				{
					case HIGH:
					SET_BIT(GPIODATA(port),pin);
					break;
					case LOW:
					CLEAR_BIT(GPIODATA(port),pin);
					break;
					default:
					uint8_tstatus=ERROR;
				}
	return uint8_tstatus;
}

uint8_t pin_read(uint8_t* data,uint8_t port,uint8_t pin)
{
	uint8_t uint8_tstatus=SUCCESS;
	if (port < PORT_TOTAL && pin < PIN_TOTAL)
	{
		*data=READ_BIT(GPIODATA(port),pin);
	}
	else
	{
		uint8_tstatus=ERROR;
	}
	return uint8_tstatus;
}


/***************************************GPIO Interrupt Handler******************************************************************************/
/*PortA*/
void GPIOA_Handler(void) 
{
   if (fptr_A!=NULLPTR)
	 {
		 fptr_A();
		 SET_BIT(GPIOICR(PORTA),portA_pin);
	 }
	 else
	 {
		 //do nothing
	 }
}

/*PortB*/
void GPIOB_Handler(void) 
{
    if (fptr_B!=NULLPTR)
	 {
		 fptr_B();
		 SET_BIT(GPIOICR(PORTB),portB_pin);
	 }
	 else
	 {
		 //do nothing
	 }
}

/*PortC*/
void GPIOC_Handler(void)
{
    if (fptr_C!=NULLPTR)
	 {
		 fptr_C();
		 SET_BIT(GPIOICR(PORTC),portC_pin);
	 }
	 else
	 {
		 //do nothing
	 }
}

/*PortD*/
void GPIOD_Handler(void) 
{
    if (fptr_D!=NULLPTR)
	 {
		 fptr_D();
		 SET_BIT(GPIOICR(PORTD),portD_pin);
	 }
	 else
	 {
		 //do nothing
	 }
}

/*PortE*/
void GPIOE_Handler(void)
{
    if (fptr_E!=NULLPTR)
	 {
		 fptr_E();
		 SET_BIT(GPIOICR(PORTE),portE_pin);
	 }
	 else
	 {
		 //do nothing
	 }
}

/*PortE*/
void GPIOF_Handler(void) 
{
    if (fptr_F!=NULLPTR)
	 {
		 fptr_F();
		 SET_BIT(GPIOICR(PORTF),portF_pin);
	 }
	 else
	 {
		 //do nothing
	 }
}



