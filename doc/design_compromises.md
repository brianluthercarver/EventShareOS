# Design Compromises

> Every design is already compromised. It's just some designs are more efficient than others. - Brian L. Carver

Years ago while a more junior engineer I remember being shutdown for design suggestions.  I knew my own design choices were better and I was shutdown because of a senior engineer's ego.  Then later as I grew more senior I had to discourage other suggestions and I wondered if my own ego was getting in the way. 

I then adopted a new  approach welcoming other's suggestions. Then that's when I came up with the above quote. No mater how well a design is though out, it's already compromised. What compromises are right for the application, usage, and efficiency.  I still listen to new suggestions, not all suggestions are going to make it into the final design.

## EventShareOS Compromises
When I design EventShareOS I had to make compromises for the design for the sake of usage, simplicity, and efficiency. I will go over the design choices and explain the advantages and disadvantages 

## Event Driven Design
I have used event driven designs in the past with GUI tools that I have written. By using the VMC (View Model Control) software design for the GUI. I used events to control the flow of information between the GUI output (the view), the controller (main code), and the model (current state).  I settled on my event name called E and V pair. E stands for Event and V stands for value, much K and V for key value pairs used for dictionaries or hash style structures. 


I love event driven designs as they lend well to case statements. Or using state machines as each new event can drives a new state. 

Here is an example from the basic application 

```C
switch(E) {
        case EVENT_KEYBOARD:
            char c = (char) V;
            printf("App Control %c \n", c);

            if ((c == 'q') || (c == 'Q')) {
                printf("Program signal quit, shutting down\n");
                signal_quit();
            }
            break;

        case EVENT_TIMER_APP_DEMO:
            timer_count++;
            printf("10 Second repeat timer %i\n", timer_count);
            break;

        case EVENT_NEW_QUOTE:
            memset(quote, 0, sizeof(quote));
            bool pass = get_data_chunk(V, (uint8_t *) quote, sizeof(quote));
            if (pass) {
                quote_count++;
                printf("New Quote %i:\n %s\n", quote_count, quote);     
            }
            break;

        case EVENT_TIMER_ONE_SHOT_DEMO:
            printf("5 second one shot timer\n");
            break;

        default:
            break;
    }
```

The second reason why I like them is that debugging and searching through the code is relatively easy with a modern IDE.  By searching on the event name you can quickly see where that event is being used in the code base. 

### Event Driven Design Disadvantages
I abhor spaghetti code.  Personally, I can’t remember every bit of code and connection to properly debug it.  The one disadvantage of an event driven design is that the misuse can quickly turn into spaghetti code.  There are two cases of the misuse: poorly named events and too many functions associated with an event. Both downsides are interrelated but worthwhile to explain separately. 

#### Poorly Named Events
For example if you have an event called LED_CONTROL and use the associated value to drive a behavior. This is forcing the programmer to examine the value to figure out what is happening and searching on LED_CONTROL can result in too many hits. It’s better to have a more specific event name. Instead of LED_CONTROL  it would be better to have LED_RED_FRONT_PANEL_CONTROL or LED_BLUE_BACK_PANEL_CONTROL. This will reduce the search to at least two specific areas of the code: the even initiating code and the LED driver code.  

#### Too Many Associated Functions
If you have ever used the QT framework then you would know about SLOT and SIGNALS.  A slot is an associated function call with a signal (event).  I once worked with a QT implemented system that had 10 plus associated slots with one signal.  Debugging became a nightmare as I did not know which function call was executed first, and secondly, I could not keep in my head all the behavior changes associated with the signal. 

### Superloop vs. RTOS
Superloops are just one endless loop running all the functions. Real Time

Superloop and Interrupts
EventShareOS is a superloop design. That means there is one process thread that controls all program flow and execution. EventShareOS was designed for embedded devices. Most embedded devices depend on interrupts for outside interaction. Hardware interrupts integrate nicely with EventShareOS. It’s important to use interrupts correctly to handle time critical events. 


[Back to Readme](../README.adoc)

> **Copyright** <p> EventShareOS is Copyright (c) by Brian L Carver 2026 under a MIT license. See the file: EventShareOS_License.txt for more details. 

[License](../EventShareOS_License.txt)