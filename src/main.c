#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "../include/terminal.h"
#include "../include/typing_test.h"
#include "../include/args.h"
#include "../include/stats.h"

void typing_test_file(const char *file_path, struct stats *stats);
void typing_test_text(const char *text, struct stats *stats);
double compute_time(struct timespec tic, struct timespec toc);

struct timespec tic, toc;

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
	// const long time = args->time;

	struct stats stats;
	stats.correct   = 0;
	stats.incorrect = 0;
	stats.words     = 0;
	stats.chars     = 0;

	if (text != NULL)
		typing_test_text(text, &stats);

	if(file_path != NULL)
		typing_test_file(file_path, &stats);


	printf("Time spent: %.2f sec.\n", compute_time(tic, toc));
	printf("Words:      %d\n", stats.words);
	print_stats(&stats);

	return 0;
}

void typing_test_text(const char *text, struct stats *stats)
{
	// Initialize terminal with new configuration and start timer
	terminal_init();
	clock_gettime(CLOCK_MONOTONIC, &tic);
	count_words(text, stats);

	// Start the typing test
	terminal_print_prompt(text);
	set_cursor_to_start();
	typing_test_run(text, stats);

	// End timer and restore terminal configuration
	clock_gettime(CLOCK_MONOTONIC, &toc);
	terminal_restore();
}

void typing_test_file(const char *file_path, struct stats *stats)
{
	FILE *f = fopen(file_path, "r");

	if (f == NULL)
	{
		perror("Error opening file");
		return;
	}

	terminal_init();
	clock_gettime(CLOCK_MONOTONIC, &tic);

	char buffer[2048]; // buffer that stores each line of provided txt file

	while (fgets(buffer, sizeof(buffer), f) != NULL)
	{
		size_t line_length = strlen(buffer);

		// When reading files, change newline char to end of string char. Update the new line_length
		if (line_length > 0 && buffer[line_length - 1] == '\n')
		{
			buffer[line_length - 1] = '\0';
			line_length -= 1;
		}

		// Remove carriage return from Windows line endings, no need no update line_length since it's not used until next iteration.
		if (line_length > 0 && buffer[line_length - 1] == '\r')
			buffer[line_length - 1] = '\0';

		// If there is a newline, ignore it and continue to the next.
		if (buffer[0] == '\0') continue;

		count_words(buffer, stats);
		terminal_print_prompt(buffer);
		// move_cursor_up(1); No need to move the cursor since we now ignore the new lines in files.
		set_cursor_to_start();
		typing_test_run(buffer, stats);

		printf("\n"); // End of line, move to the next.
    }

	fclose(f);

	clock_gettime(CLOCK_MONOTONIC, &toc);
	terminal_restore();
}

double compute_time(struct timespec tic, struct timespec toc)
{
	return (toc.tv_sec - tic.tv_sec) + (toc.tv_nsec - tic.tv_nsec) / 1e9;
}
