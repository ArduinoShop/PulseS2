/**********   revision 0.1  -  Oct. 7 202   ***********************//

#include "PulseS2.h"

/*
 *  some private variables for th class
 */
 
 timer_idx_t                timer;
 timer_group_t         group;
 gpio_num_t	PulseS2::pin;		//  public for now

 void IRAM_ATTR timer_group0_isr( void *p ) { 
    timer_spinlock_take(  group ); 
    
    	gpio_set_level( ( gpio_num_t ) PulseS2::pin, (uint32_t) 0 );
    	
		timer_group_clr_intr_status_in_isr( group, timer );

    /* After the alarm has been triggered we need to enable it again, so it will re-triggered again */
    timer_group_enable_alarm_in_isr( group, timer ); 

    timer_spinlock_give(  group );

}

void timer_init( uint64_t dur )  { 
	
	printf("timer init at 10 MHz - prescale = 8 G %d, T %d, duration %lld\n", group, timer, dur );
	    /* Select and initialize basic parameters of the timer */
    timer_config_t config;
        config.divider = 8;  //  Set for a 10MHz Clock = 100nSec resolution
        config.counter_dir = TIMER_COUNT_UP;
        config.counter_en = TIMER_PAUSE;
        config.alarm_en = TIMER_ALARM_DIS;  //  TIMER_ALARM_DIS;  //  TIMER_ALARM_EN;
        config.auto_reload = ( timer_autoreload_t )1;
  // default clock source is APB
		ESP_ERROR_CHECK( timer_init( group, timer, &config ) );
//  Set Reload Value to 0000000000000
		timer_set_counter_value( group, timer, 0x00000000ULL );
		
		timer_set_alarm_value( group, timer, dur * 10 ); 
		timer_enable_intr( group, timer );
		timer_set_alarm( group, timer,  TIMER_ALARM_EN ); 			

	   timer_isr_register( group, timer, timer_group0_isr,  &PulseS2::pin, ESP_INTR_FLAG_IRAM, NULL );
	
	  timer_start( group, timer );
	
						}

 PulseS2::PulseS2( int t, int g ) {	printf("PulseS2 Construtor Group %d, Timer %d\n", g, t );
		group = (  timer_group_t ) g;
		timer = ( timer_idx_t ) t;
				}
				
void PulseS2::Pulse( int p, int duration, bool pol )  {	
	
	if( duration ) {
			PulseS2::pin = ( gpio_num_t ) p;
			gpio_set_direction( ( gpio_num_t )pin, GPIO_MODE_OUTPUT );
			gpio_set_level( ( gpio_num_t )pin, 0 ); 

		    printf("%d uSec Pulse Requested on %d for Group %d, Timer %d\n", duration, p, group, timer );   //  DEBUG statement - comment out for production
		    
		    timer_init( duration ); 
		    
		    if( pol ) { gpio_set_level( ( gpio_num_t )pin, 1 ); }  	   // default is low to high to low pulse
//		    else       { gpio_set_level( ( gpio_num_t )pin, 0 ); }    //  on th to-do list
		    
		} 
		 else { printf("Zero length Pule Request IGNORED\n"); }		//  more DEBUG stuff
	
	  }
