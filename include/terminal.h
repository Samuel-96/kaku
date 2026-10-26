#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

void terminal_init(void);
void terminal_restore(void);
void terminal_print_prompt(const char *text);
void set_cursor_to_start();

#endif