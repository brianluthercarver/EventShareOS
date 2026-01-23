/************************************************************
EventShareOS is Copyright (c) by Brian L Carver 2026
under a MIT license. See the file: EventShareOS_License.txt
for more details. 

basic is an example program using EventShareOS in a POSIX 
Linux system. 
************************************************************/

/*****************************************************

quote_module.c

Generate Random Quotes
*****************************************************/

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>


#include "EventShareOS.h"
#include "events.h"
#include "quote_module.h"

char * quotes[] = {
    "1 Don't comment bad code - rewrite it. - Brian Kernighan",
    "2 In God we trust. All others must bring data.- W. Edwards Demming",
    "3 Nine people can't make a baby in a month. - Fred Brooks",
    "4 First, solve the problem. Then, write the code. - John Johnson",
    "5 Talk is cheap. Show me the code.- Linus Torvalds",
    "6 When in doubt, use brute force. - Ken Thompson ",
    "7 Rules of Optimization: 1. Don't. 2. (For experts only) Don't yet. - Michael A. Jackson",
    "8 Code is read much more often than it is written. - Guido van Rossum",
    "9 C++ is an octopus made by nailing extra legs onto a dog. - Steve Taylor ",
    "10 Programmer: A machine that turns coffee into code. – Anonymous"
};

char * goodbye[] = {
    "Parting is all we know of heaven, And all we need of hell. - Emily Dickinson",
    "There are no goodbyes for us. Wherever you are, you will always be in my heart. - Mahatma Gandhi",
    "Remember me and smile, for it’s better to forget than to remember me and cry. - Dr. Seuss",
    "Every new beginning comes from some other beginning’s end. - Seneca",
    "What we have once enjoyed we can never lose. All that we love deeply becomes a part of us. - Helen Keller"
};


void quote_module_init() {
    // setup for a random number generator
    srand(time(NULL));
}

void quote_module_control(events E, unsigned int V) {
    uint32_t id = 0;
    uint32_t size = 0;
    if (E == EVENT_TIMER_APP_DEMO) {
        id = (rand() % 10);
        size = strlen(quotes[id]);
        enqueue_data_chunk(EVENT_NEW_QUOTE, quotes[id], size);
    }
}

void quote_module_cleanup() {
    // print an ending quote
    uint32_t id = rand() % 5;
    printf("Goodbye \n %s\n", goodbye[id]);
}