

/*****************************************************************
*
* eventloop.c
*
* Public code file for the event loop.
* 
* Within each of these functions there is a call to an implementation
* specific version of initialization and the scheduler.  This allows
* shared code to used across different implementations and test 
* frameworks.  
*  
*******************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

#include "event_loop.h"
#include "custom_event_loop.h"

#define MAX_SUBSCRIPTION_SIZE 100
#define MAX_QUEUE_SIZE 20

static uint32_t subscriptions[MAX_SUBSCRIPTION_SIZE];
static control_value event_queue[MAX_QUEUE_SIZE];
static uint32_t head = 0;
static uint32_t tail = 0;
static bool queue_available = true;
static bool running_status = true;

static uint32_t controls_min = 0;
static uint32_t controls_max = 0;
static uint32_t modules_min = 0;
static uint32_t modules_max = 0;

void event_loop_set_controls_range(uint32_t max) {
    controls_min = 0;
    controls_max = max;
}
void event_loop_set_modules_range(uint32_t max) {
    modules_min = 0;
    modules_max = max;
}

uint32_t get_max_controls() {
    return(controls_max);
}
uint32_t get_max_modules() {
    return(modules_max);
}

void event_loop_init(void)
{
    memset(subscriptions, 0, sizeof(subscriptions));
    memset(event_queue, 0, sizeof(event_queue));
    head = 0;
    tail = 0;
    custom_loop_init();
}

void event_loop_scheduler(void)
{
    // get the first item off the queue
    uint32_t C = event_queue[head].control;
    uint32_t V = event_queue[head].value;
    uint32_t module_mask = subscriptions[C];

    // pass the C & V onto the custom scheduler with the subscription
    if (( C > controls_min ) && ( C < controls_max))
    {
    	custom_loop_scheduler(module_mask, C, V);
        // clear the item out of the queue
    	event_queue[head].control = controls_min;
    	event_queue[head].value = 0;

        // move the head pointer
        ++head;
        if (head == MAX_QUEUE_SIZE)
        {
            head = 0;
        }
        if (queue_available == false)
        {
           queue_available = true;
        }
    }
}

void subscribe(uint32_t module, int num, ...)
{
    if (( module > modules_min) && (module < modules_max))
    {
        va_list arg_list;
        va_start(arg_list, num);
        for (int index = 0; index < num; index++)
        {  
            unsigned int control = va_arg(arg_list, unsigned int);

            if ((control > controls_min) && (control < controls_max ))
            {
                unsigned int sub = subscriptions[control];
                unsigned int new = 1 << (module-1);  // modules are bit specific
                sub = sub | new;
                subscriptions[control] = sub;
            }  
        }
        va_end(arg_list);
    }
}
        
void publish_control(uint32_t C, unsigned int V)
{
    // insert C  V onto the queue 
    // printf("control %d, value %i \n", C, V);
    if (queue_available)
    {
        event_queue[tail].control = C;
        event_queue[tail].value = V;

        // move the tail
        ++tail;
        if (tail == MAX_QUEUE_SIZE)
        {
            tail = 0;
            if (tail == head)
            {
                queue_available = false;  // full queue
            }
        }
        else if ( tail == head )
        {
            queue_available = false; // full queue
        }
    }
}


void signal_quit()
{
    running_status = false;
    // all the private cleanup  signals are handle here
    custom_loop_quit();
}

bool event_loop_running()
{
    return (running_status);
}



