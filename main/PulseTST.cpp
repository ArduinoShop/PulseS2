#include "PulseS2.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main(void)
{

 PulseS2 pulse00 = PulseS2( );
 PulseS2 pulse01 = PulseS2( 1 );

while( 1 ) {
	for( int x = 1; x < 7; x++ )  {
	
		pulse00.Pulse( 34, x*100000 );
				vTaskDelay( x * 20 );
		pulse01.Pulse( 33, x*150000 );
				vTaskDelay( x * 20 );
			
				}
		}
}
