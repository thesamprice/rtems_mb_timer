/*
 * Hello world example
 */
#include <rtems.h>
#include <stdlib.h>
#include <stdio.h>
#include <bsp.h>
#include <bsp/timer.h>
#include <time.h>


static volatile int counter=0;
void timer1_callback(void *){
  counter++;

}

rtems_task Init(
  rtems_task_argument ignored
)
{
  volatile Microblaze_Timer *timer = _Microblaze_Timer;

  printf( "\nHello World\n" );
  microblaze_user_clock_handler_install(timer1_callback);


  /* Set load register to 0 */
  timer->tlr1 = 0;
  /* Reset the timer and interrupt */
  timer->tcsr1 = MICROBLAZE_TIMER_TCSR0_T0INT | MICROBLAZE_TIMER_TCSR0_LOAD0;
  /* Release the reset */
  timer->tcsr1 = 0;
  /*
   * Enable interrupt, auto reload mode, external interrupt signal,
   * and down counter
   */
  timer->tcsr1 =  MICROBLAZE_TIMER_TCSR0_ARHT0 | MICROBLAZE_TIMER_TCSR0_ENIT0 |
                  MICROBLAZE_TIMER_TCSR0_GENT0 | MICROBLAZE_TIMER_TCSR0_UDT0;

  /* Set a reset value for the timer counter */
  timer->tlr1 = BSP_MICROBLAZE_FPGA_TIMER_FREQUENCY / 4000;
  uint32_t control_status_reg = timer->tcsr1;
  /* Load the reset value into the counter register */
  timer->tcsr1 = MICROBLAZE_TIMER_TCSR0_LOAD0;
  /* Enable the timer */
  timer->tcsr1 = control_status_reg | MICROBLAZE_TIMER_TCSR0_ENT0;

  int count_0 = counter;
  itn counter_end;
  for(int ind = 0;ind< 10;ind++){
    sleep(1);
    counter_end = counter;
    printf("%d\n", counter_end - count_0);
    count_0 = counter;
  }
  exit( 0 );
}
