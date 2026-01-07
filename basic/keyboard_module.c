

/*****************************************************

keyboard_module.c

*****************************************************/

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "EventShareOS.h"
#include "controls.h"

static struct termios original_term_state;


// terminal_enable_raw_mode()
// Disable echo and set one character reads

void terminal_enable_raw_mode()
{
    struct termios raw_term;
    tcgetattr(STDIN_FILENO, &original_term_state);
    
    raw_term = original_term_state;
    raw_term.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw_term.c_cc[VMIN] = 0;
    raw_term.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_term);
}

// terminal_cleanup()
// Reset the terminal state back to original

void terminal_cleanup() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_term_state);
}


void keyboard_module_init()
{
    terminal_enable_raw_mode();
    printf("keyboard_module_init \n");
}

// keyboard_module_control()
// This a polling function to read the keyboard.
// This module does not get any inputs. 

void keyboard_module_control(controls C, unsigned int V)
{
    char key;

    read(STDIN_FILENO, &key, 1);
    if (key != 0) {
        publish_control(CONTROL_KEYBOARD, (unsigned int) key);
    }
}


void keyboard_module_cleanup()
{
    terminal_cleanup();
}
