


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./eventloop.h"
#include "./soft_timer.h"

#include "../basic/controls.h"
#include "../basic/modules.h"

static unsigned int main_time = 0;
static unsigned int max_events = 0;
static timer_event timer_events[MAX_TIME_EVENTS];



void timer_init()
{
    memset(timer_events, 0, sizeof(timer_events));
    main_time = 0;
}


void time_keeper()
{
    ++main_time; // update the millisecond timer
    // decrement all the countdown timers
    // and check for an event
    for (int i = 0; i < max_events; i++)
    {
        if ( timer_events[i].enabled == TIMER_ENABLED )
        {
            --timer_events[i].count_down;
            if ( timer_events[i].count_down == 0 )
            {
                if ( timer_events[i].type == TIMER_REPEAT )
                {
                    publish_control(timer_events[i].control, 0);
                    timer_events[i].count_down = timer_events[i].time;                   
                }
                else  // TIMER_ONE_SHOT
                {
                    publish_control(timer_events[i].control, 0);
                    timer_events[i].enabled = TIMER_DISABLED;
                }
            }
        }
    }

}



void update_timer_event(int i, controls C, uint16_t milliseconds, bool timer_type, bool on_off)
{
    timer_events[i].control = C;
    timer_events[i].time = milliseconds;
    timer_events[i].count_down = milliseconds;
    timer_events[i].type = timer_type;
    timer_events[i].enabled = on_off;
}

void add_timer_event(controls C, uint16_t milliseconds, bool timer_type, bool on_off)
{
    int i = 0;
    bool not_done = true;

    // check for first time add
    if ((C < CONTROL_EOL) && (max_events == 0))
    {
        update_timer_event(max_events, C, milliseconds, timer_type, on_off);
        ++max_events;
    }
    else
    {
        while (not_done)
        {
            // overwrite the existing timer 
            if ( timer_events[i].control == C)
            {
                update_timer_event(i, C, milliseconds, timer_type, on_off);
                not_done = false;
            }
            
            // add a new timer
            if ( timer_events[i].control == CONTROL_UNDEFINED )
            {
                if ((C < CONTROL_EOL) && (max_events < MAX_TIME_EVENTS))
                {
                    update_timer_event(i, C, milliseconds, timer_type, on_off);
                    ++max_events;
                    not_done = false;
                }
            }

            // check for a end condition
            ++i;
            if ((not_done == true) && ( i == max_events+1))
            {
                not_done = false;
            }
        }
    }

}
void start_timer(controls C)
{
    for (int i = 0; i < max_events; i++)
    {
        if (timer_events[i].control == C )
        {
            if (timer_events[i].type == TIMER_ONE_SHOT)
            {
                timer_events[i].enabled = TIMER_ENABLED;
                timer_events[i].count_down = timer_events[i].time;
            }
        }
    }
}

void cancel_timer(controls C)
{
    for (int i = 0; i < max_events; i++)
    {
        if (timer_events[i].control == C )
        {
            if (timer_events[i].type == TIMER_ONE_SHOT)
            {
            	if (timer_events[i].enabled == TIMER_ENABLED)
            	{
					timer_events[i].enabled = TIMER_DISABLED;
					timer_events[i].count_down = 0;
            	}
            }
        }
    }
}


void enable_timer(controls C, bool on_off)
{
    for (int i = 0; i < max_events; i++)
    {
        if (timer_events[i].control == C )
        {
            timer_events[i].enabled = on_off;
        }
    }
}

