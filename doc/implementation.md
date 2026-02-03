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

``` C
    void subscribe(uint32_t module, int num, ...);
```
is a variable list using the module name, the number of events, and a list of each event. 

##### Soft Timers
A soft timer is a software generated event based on reaching a specific time. Soft timers fall into two types: recurring and one shot. Recurring timers are events that repeat with a fixed time interval.  One shot timers are events that are started and the event is sent when the timer is completed.  Timers can be turned on or off. To set a timer, assign an event name, the time, the type and if the timer is turned on or off. 

``` C
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

``` C
    if (module_list & MODULE_01_MASK) {
        // call module 01 here
        xxx_module_control(event, value);
    }
```
The module_list is the grouping of modules that are sharing the event. Each function is hard coded to the module listing enumeration. If a module is listed as two then in the needs to be associated with MODULE_02_MASK.  Assign the highest priority tasks to the lower numbers.  


### custom_loop_quit
Inside this function is the cleanup coded needed by each module. When the system is sent the quit signal 

```C
    void signal_quit();
```

the custom_loop_quit function is called.  Any events in the queue are discarded and the system will shutdown. 

## Usage

Event Driven Systems are passive.  That means nothing will happen unless an event is sent, queued, and dispatched to the module.  Event Driven Systems are great for embedded devices as inputs can be expressed as an event. Also events can be handled as a state machine. 

For example:  Take the simple device of one switch and a motor. Pressing the switch once will turn on the motor. Pressing the switch again with the motor running will turn off the motor. Holding the switch will increase the speed of the motor. Holding the switch too long will shut off the motor.  

This design can be broken into two modules: switch_module_control and motor_module_control. The motor module can receive three events ON, OFF, SPEED.  The switch module handles the one switch. There are two approaches to switch handling interrupt or polling. 

### Interrupt Design
Most embedded programmers like interrupts. With an interrupt design, when the interrupt set to be called when the switch is pressed or when the switch is released. 

EVENT_SWITCH_ON
EVENT_SWITCH_OFF

To send an event use publish_event function. 

```C
    void publish_event(uint32_t E, uint32_t V);
```
For example the send the event when the switch is pressed:

```C
    publish_event(EVENT_SWITCH_ON, 0);
```
The event is placed on the queue in sequential order. As events are dequeued they are sent to custom_loop_scheduler. The switch_module_control receives the event and depending on the current state of the internal state machine does the correction action. 

If the  motor was off:  

```C
    SWITCH_STATE_MOTOR_OFF:
        publish_event(EVENT_MOTOR_ON, 0);
        start_timer(EVENT_TIMER_SWITCH_ON);
        break;
```       
If the motor was already on and received EVENT_SWITCH_OFF:

```C
    SWITCH_STATE_MOTOR_ON:
        publish_event(EVENT_MOTOR_OFF, 0);
        cancel_timer(EVENT_TIMER_SWITCH_ON);
        break;
```    

### POLLING Design
In a polling design, three modules will be needed: switch_module_control, app_motor_control, and motor_module_control. To read the switch a repeating timer is needed.

Timer Setup
```C
   add_timer_event(EVENT_TIMER_SWITCH_POLLING, 20, TIMER_REPEAT, TIMER_ENABLED);
```
The switch module would look like this:

```C
    static bool switch_state = false;
    void switch_module_control(event E, uint32_t V) {
        bool switch = false;
        if (E == EVENT_TIMER_SWITCH_POLLING) {
            switch = read_switch();
            If ((switch_state) && (!switch) {
                publish_event(EVENT_SWITCH_STATE_OFF, 0);
                switch_state = false
            }
            elseif (switch) {
                publish_event(EVENT_SWITCH_STATE_ON, 0);
                switch_state = true
            }
        }
    }
```
Every 20 miliseconds the state of the switch is read. Depending on the prior state, the on or off event is sent.

[Back to Readme](../README.adoc)

> **Copyright** <p> EventShareOS is Copyright (c) by Brian L Carver 2026 under a MIT license. See the file: EventShareOS_License.txt for more details. 

[License](../EventShareOS_License.txt)