 #include "contiki.h"
 #include <stdio.h> 




 PROCESS(send_process,"Send_Process");
PROCESS(print_process,"Print_Process");
AUTOSTART_PROCESSES(&send_process,&print_process);
  static int count;

 PROCESS_THREAD(send_process, ev, data)
 {
         static struct etimer timer;
         

         PROCESS_BEGIN();
        
         etimer_set(&timer, CLOCK_SECOND * 4 + random_rand() % (CLOCK_SECOND * 4));

         count = 0;

        // printf("Initial value of count: %d\n", count);
        
         while (1) {
                 PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
           count++;
				//printf("trigger process runs.............\n");
                 printf("Count value in SEND PROCESS: %d\n", count);
                //PROCESS_PAUSE();
				 process_poll(&print_process);
                 etimer_reset(&timer);
         }

         PROCESS_END();
 }


static void
pollhandler(void)
{
  printf("Count value in PRINT PROCESS: %d\n", count);

}

//on going process

 PROCESS_THREAD(print_process, ev, data)
 {
		static struct etimer et;
		
		PROCESS_POLLHANDLER(pollhandler());
 	   
         PROCESS_BEGIN();
		//printf("Start Continuous Process\n");
		etimer_set(&et, CLOCK_CONF_SECOND);
		
         while (1) {
				
				PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
				
				printf("Hello World\n");
				etimer_reset(&et);
				
			
                 
         }
		
         PROCESS_END();
 }
