/**
 ** @file                   main.c
 ** @brief                  This file contains the app running state
 ** @author                 Mohamed Sayed
 ** @date                   Jan 23, 2023
 ** @version                0.1
 */

/*- INCLUDES
----------------------------------------------*/
#include "app.h"



int main (void)
	{

		APP_init();
		while (1)
		{
			APP_start();
		}
	}


	
	
