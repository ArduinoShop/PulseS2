#include "driver/timer.h"
#include "driver/gpio.h"

class PulseS2 {
		public :
		
			PulseS2(  int timer = 0, int group = 0 );  //  Constructor - there are 4 timers - 2 groups of 2
		
			void Pulse( int pin, int duration, bool pol = true ) ;  //  specify the output gpio pin ( it will be set to OUTPUT )
																												   //  the duration of the pulse in microSeconds
																												   //  and the polarity of the pulse - true = low to high to low
			
			static gpio_num_t 	  pin;													  //  this should be private - to-do
			
		private :
			
			timer_group_t group = ( timer_group_t  ) 0;
			timer_idx_t 	  timer   = ( timer_idx_t )        0;

	 
							};
