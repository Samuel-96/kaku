#include <termios.h>
#include <stdio.h>
#include <unistd.h>

static struct termios original_terminal;

void terminal_init(void)
{
    struct termios raw;
    
    tcgetattr(STDIN_FILENO, &original_terminal);          // Obtains current terminal configuration

    raw = original_terminal;

    raw.c_lflag     &= ~(ICANON | ECHO);
    raw.c_cc[VMIN]  = 1;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &raw); // Sets new terminal configuration
}

void terminal_restore(void)
{
    // ANSI: \033[?25h Shows cursor terminal.
    printf("\033[?25h\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal);
}

void terminal_print_prompt(const char *text)
{
	printf("\033[38;5;248m%s \033[0m", text);
	fflush(stdout);
}

void set_cursor_to_start()
{
	printf("\r");
    fflush(stdout);
}