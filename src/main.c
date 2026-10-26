#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/terminal.h"
#include "../include/typing_test.h"

int main(int argc, char *argv[])
{
	terminal_init();

	terminal_print_prompt(argv[1]);
	set_cursor_to_start();
	typing_test_run(argv[1]);

	terminal_restore();
	
	return 0;
}