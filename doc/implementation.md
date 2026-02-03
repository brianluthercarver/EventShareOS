# Implementing EventShareOS
Advice and best practices implementing EventShareOS on an embedded processor or a single threaded POSIX application.  There are common fundamentals between implementing EventShareOS between a POSIX application and an embedded device.  This guid will go over those steps.

## First Steps
While implementation can be easy with EventShareOS, using an Event Driven system can be confusing at first.  Read the [Background](./background.md) of EventShareOS to understand how event driven systems work. 

### Modules and Events
There are two H files needed for a custom application: modules.h and events.h.  Inside these two files, there should be an enumeration to represent the module list and event list. 

For an example see [module.h](../basic/modules.h) and [event.h](../basic/events.h) 

In both files the Zero value is off limits. EventShareOS assumes that zero is range limit. The name XXXX_EOL (End of List) is the upper end value.  That must be set in the initialization function.

#### Modules 
Modules is a grouping of associated functions inside a custom application much like a thread or process. 

#### Events
Events are sent as a pair of unsigned 32 bit numbers, uint32_t.  The first number is the *Event* and the second is the *Value* associated with the event (E,V).

### Custom Functions
The interface with EventShareOS handled with three custom functions:

1) custom_loop_init
2) custom_loop_scheduler
3) custom_loop_quit

These function are defined in [custom_event_loop.h](../EventShareOS/custom_event_loop.h). 

Each function can be defined in it's own file or placed all three in one file.  The basic example provided has all three functions in the same file. [basic_eventloop.c](../basic/basic_eventloop.c)

#### custom_loop_init
Inside initialization function there are three parts that have to be completed: subscriptions, soft timers, and modules.   For an example see [basic_eventloop.c](../basic/basic_eventloop.c).

##### Subscriptions 

Modules that process events will need to subscribe to those events. The subscription function

```
    void subscribe(uint32_t module, int num, ...);
```
is a variable list using the module name, the number of events, and a list of each event. 

##### Soft Timers
A soft timer is a software generated event based on reaching a specific time. Soft timers fall into two types: recurring and one shot. Recurring timers are events that repeat with a fixed time interval.  One shot timers are events that are started and the event is sent when the timer is completed.  Timers can be turned on or off. To set a timer, assign an event name, the time, the type and if the timer is turned on or off. 

```
    #define TIMER_ENABLED    true
    #define TIMER_DISABLED   false
    #define TIMER_REPEAT     true
    #define TIMER_ONE_SHOT   false

    void add_timer_event(uint32_t E, uint16_t milliseconds, bool timer_type, bool on_off);
```
##### Modules
Each module must provide three functions: Init, The Handler, and Cleanup.  Typically the naming of the three functions follow:

xxx_module_init
xxx_module_control
xxx_module_cleanup

Place the init functions at the end of the custom_loop_init.

### custom_loop_scheduler
This is the heart of EventShareOS for a custom application.  Inside EventShareOS, as events are pulled off the queue, they are sent to this function. Inside this function the Event Value pair (E,V) is given to each module as subscribed.

```
    if (module_list & MODULE_01_MASK) {
        // call module 01 here
        xxx_module_control(event, value);
    }
```




[Back to Readme](../README.adoc)

> **Copyright** <p> EventShareOS is Copyright (c) by Brian L Carver 2026 under a MIT license. See the file: EventShareOS_License.txt for more details. 

[License](../EventShareOS_License.txt)