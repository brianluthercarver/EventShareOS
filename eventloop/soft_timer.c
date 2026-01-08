


#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "EventShareOS.h"
#include "event_loop.h"
#include "soft_timer.h"


static uint32_t main_time = 0;
static uint32_t max_events = 0;
static timer_event timer_events[MAX_TIME_EVENTS];

static uint32_t timer_events_min = 0;
static uint32_t timer_events_max = 0;
static uint32_t timer_modules_min = 0;
static uint32_t timer_modules_max = 0;

void timer_init()
{
    memset(timer_events, 0, sizeof(timer_events));
    main_time = 0;
    timer_events_max = get_max_events();
    timer_modules_max = get_max_modules();
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
                    publish_event(timer_events[i].control, 0);
                    timer_events[i].count_down = timer_events[i].time;                   
                }
                else  // TIMER_ONE_SHOT
                {
                    publish_event(timer_events[i].control, 0);
                    timer_events[i].enabled = TIMER_DISABLED;
                }
            }
        }
    }

}



void update_timer_event(int i, uint32_t C, uint16_t milliseconds, bool timer_type, bool on_off)
{
    if ((C > timer_events_min) && (C < timer_events_max)) {
        timer_events[i].control = C;
        timer_events[i].time = milliseconds;
        timer_events[i].count_down = milliseconds;
        timer_events[i].type = timer_type;
        timer_events[i].enabled = on_off;
    }
}

void add_timer_event(uint32_t E, uint16_t milliseconds, bool timer_type, bool on_off)
{
    int i = 0;
    bool not_done = true;

    // check for first time add
    if ((E > timer_events_min) && (E < timer_events_max) && (max_events == 0))
    {
        update_timer_event(max_events, E, milliseconds, timer_type, on_off);
        ++max_events;
    }
    else
    {
        while (not_done)
        {
            // overwrite the existing timer 
            if ( timer_events[i].control == E)
            {
                update_timer_event(i, E, milliseconds, timer_type, on_off);
                not_done = false;
            }
            
            // add a new timer
            if ( timer_events[i].control == timer_events_min )
            {
                if ((E < timer_events_max) && (max_events < MAX_TIME_EVENTS))
                {
                    update_timer_event(i, E, milliseconds, timer_type, on_off);
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
void start_timer(uint32_t E)
{
    if ((E > timer_events_min) && (E < timer_events_max)) {
        for (int i = 0; i < max_events; i++)
        {
            if (timer_events[i].control == E )
            {
                if (timer_events[i].type == TIMER_ONE_SHOT)
                {
                    timer_events[i].enabled = TIMER_ENABLED;
                    timer_events[i].count_down = timer_events[i].time;
                }
            }
        }
    }
}

void cancel_timer(uint32_t E)
{
    if ((E > timer_events_min) && (E < timer_events_max)) {
        for (int i = 0; i < max_events; i++)
        {
            if (timer_events[i].control == E )
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
}


void enable_timer(uint32_t E, bool on_off)
{
    if ((E > timer_events_min) && (E < timer_events_max)) {
        for (int i = 0; i < max_events; i++)
        {
            if (timer_events[i].control == E )
            {
                timer_events[i].enabled = on_off;
            }
        }
    }
}

