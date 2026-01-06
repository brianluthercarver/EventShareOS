#ifndef POSIX_TIMER_H
#define POSIX_TIMER_H

//#include "soft_timer.h"

/************************************************************

File: posix_timer.h
In linux, time is retrieved by the clock_gettime() function. 
This function offers the higher nanosecond resolution for
precision. In this case we will be using the microsecond time
to generate millisecond events.

For polling linux systems use poll_time_keeper().

************************************************************/

void init_poll_time_keeper();
void poll_time_keeper();

#endif // POSIX_TIMER_H