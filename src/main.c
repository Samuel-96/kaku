#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/terminal.h"
#include "../include/typing_test.h"
#include "../include/cli.h"

int main(int argc, char *argv[])
{
	init_parser();

	parse_args(argc, argv);

	char *text = get_text();

	terminal_init();

	terminal_print_prompt(text);
	set_cursor_to_start();
	typing_test_run(text);

	terminal_restore();
	free_parser();

	return 0;
}
