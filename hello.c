/*
 * Hello world example
 */
#include <rtems.h>
#include <stdlib.h>
#include <stdio.h>
#include <bsp.h>
#include <bsp/microblaze-timer.h>
#include <time.h>
#include <math.h>
#include <unistd.h> /* Sleep */

rtems_id   task_id;
rtems_name task_name;

static volatile int counter=0;
void timer1_callback(void * none){
  counter++;
}



rtems_task Init(
  rtems_task_argument ignored
)
{
  volatile Microblaze_Timer *timer = _Microblaze_Timer;
  int count_rate = 4000;
  microblaze_user_clock_handler_install(timer1_callback);


  /* Set load register to 0 */
  timer->tlr1 = 0;

  /* Set a reset value for the timer counter */
  timer->tlr1 = BSP_MICROBLAZE_FPGA_TIMER_FREQUENCY / count_rate ;

  /* Reset the timer and interrupt */
  timer->tcsr1 = MICROBLAZE_TIMER_TCSR0_T0INT | MICROBLAZE_TIMER_TCSR0_LOAD0;

  // /* Release the reset */
  timer->tcsr1 = 0;
  /*
   * Enable interrupt, auto reload mode, external interrupt signal,
   * and down counter
   */
  timer->tcsr1 =  MICROBLAZE_TIMER_TCSR0_ARHT0 | 
                  MICROBLAZE_TIMER_TCSR0_GENT0 | 
                  MICROBLAZE_TIMER_TCSR0_UDT0 |
                  MICROBLAZE_TIMER_TCSR0_ENT0 |
                  MICROBLAZE_TIMER_TCSR0_ENIT0 |
                  MICROBLAZE_TIMER_TCSR0_T0INT; /* Clear interrupt */

  printf("timer task started\n");
  volatile int count_0 = counter;
  volatile int counter_end;
  int ind;
  int return_result = 0;
  int error;
  for (ind=0;ind < 4;ind++)
  {
    counter_end = counter;
    int observed_rate = counter_end - count_0;
    printf("Sleeping %d %d\n",observed_rate,ind);
    count_0 = counter;
    sleep(1);
    error = fabs(observed_rate - count_rate);
    if( (ind > 0) && (error > 60)){
      return_result = -1;
      printf("Fail error=%d\n",error);
    }
  }
  printf("Done Error is %d\n", error);
  // delete init task after starting the three working tasks
  (void) rtems_task_delete( RTEMS_SELF );
}


/*
 * Simple RTEMS configuration
 */

#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_UNLIMITED_OBJECTS
#define CONFIGURE_UNIFIED_WORK_AREAS
#define CONFIGURE_MAXIMUM_TASKS             4

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>

