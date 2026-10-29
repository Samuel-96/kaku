#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>

#include "../include/typing_test.h"
#include "../include/stats.h"

void typing_test_run(const char *text, struct stats *stats)
{
	int col = 1;
	size_t cont = 0;
	size_t end = strlen(text);

	char c;

	while (read(STDIN_FILENO, &c, 1) == 1)
	{
		if (c == text[cont])
		{
		  // ANSI: \033[%dG moves cursor to the indicated column.
		  // \033[32m enable green color; %c prints user input.
		  // \033[0m restores color.
		  printf("\033[%dG\033[32m%c\033[0m", col, c);
		  increase_correct(stats);
		}
		else
		{
		  // Incorrect char it's showed in red.
		  printf("\033[%dG\033[31m%c\033[0m", col, text[cont]);
		  increase_incorrect(stats);
		}

		// Increment column, refresh screen after type and increment char counter.
		col++;
		fflush(stdout);
		cont++;

		if (cont == end)
		  break;
	}

	//clock_gettime(CLOCK_MONOTONIC, &toc);

	fflush(stdout);
}
