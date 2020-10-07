#include "PulseS2.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main(void)
{

 PulseS2 pulse00 = PulseS2( );			//  use Timer Group 0  Timer 0
 PulseS2 pulse01 = PulseS2( 1 );		//  use Timer Group 0  Timer 1
																		// for now I recommend only 2 mas instances
																		// useful if you need to have 2 separate pulses

/************  This demo outputs consecutive pulses incrementing from .1 Sec to .6 Sec on gpio pin 34 using Timer 0 of Group 0
 * 																																  and .15 Sec to .9 Sec on gpio pin 33 using Timer 1 of Group 0
 * *********************************************/
 
while( 1 ) {
	for( int x = 1; x < 7; x++ )  {
	
		pulse00.Pulse( 34, x*100000 );
				vTaskDelay( x * 20 );
		pulse01.Pulse( 33, x*150000 );
				vTaskDelay( x * 20 );
			
				}
		}
}
