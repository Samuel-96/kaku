#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "../include/terminal.h"
#include "../include/typing_test.h"
#include "../include/args.h"

void typing_test_file(const char *file_path);
void typing_test_text(const char *text);

int main(int argc, char *argv[])
{
	if (!parse_arguments(argc, argv))
	{
		print_usage();
		return EXIT_FAILURE;
	}

	const struct arguments *args = get_arguments();

	const char *text = args->text;
	const char *file_path = args->file;
	const long time = args->time;

	if (text != NULL)
		typing_test_text(text);

	if(file_path != NULL)
		typing_test_file(file_path);

	return 0;
}

void typing_test_text(const char *text)
{
	terminal_init();

	terminal_print_prompt(text);
	set_cursor_to_start();
	typing_test_run(text);

	terminal_restore();
}

void typing_test_file(const char *file_path)
{
	FILE *f = fopen(file_path, "r");

	if (f == NULL)
	{
		perror("Error opening file");
		return;
	}

	terminal_init();

	char buffer[2048];

	while (fgets(buffer, sizeof(buffer), f) != NULL)
	{
		terminal_print_prompt(buffer);
		move_cursor_up(1);
		set_cursor_to_start();
		typing_test_run(buffer);
    }

	fclose(f);

	terminal_restore();
}
