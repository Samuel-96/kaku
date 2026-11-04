#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/stats.h"

void start_timer(struct stats *s)
{
    clock_gettime(CLOCK_MONOTONIC, &s->tic);
}

void end_timer(struct stats *s)
{
    clock_gettime(CLOCK_MONOTONIC, &s->toc);
}

void increase_correct(struct stats *s)
{
    if (s != NULL) s->correct++;
}

void increase_incorrect(struct stats *s)
{
    if (s != NULL) s->incorrect++;
}

void print_stats(const struct stats *s)
{
    double time = compute_time(s->tic, s->toc);
    double accuracy = compute_accuracy(s->correct, s->incorrect);

    printf("\n");
    printf("  \033[1;36m╭────────────── KAKU RESULTS ──────────────╮\033[0m\n");
    printf("  \033[1;36m\033[0m              \033[1;36m\033[0m\n");

    printf("  \033[1;36m\033[0m Time        \033[1m%8.2f sec\033[0m               \033[1;36m\033[0m\n", time);
    printf("  \033[1;36m\033[0m Words       \033[1m%8u\033[0m                     \033[1;36m\033[0m\n", s->words);
    printf("  \033[1;36m\033[0m Characters  \033[1m%8u\033[0m                     \033[1;36m\033[0m\n", s->chars);

    printf("  \033[1;36m\033[0m                                           \033[1;36m\033[0m\n");
    printf("  \033[1;36m\033[0m Correct     \033[1;32m%8u\033[0m                     \033[1;36m\033[0m\n", s->correct);
    printf("  \033[1;36m\033[0m Incorrect   \033[1;31m%8u\033[0m                     \033[1;36m\033[0m\n", s->incorrect);
    printf("  \033[1;36m\033[0m Accuracy    \033[1;33m%7.2f%%\033[0m                   \033[1;36m\033[0m\n", accuracy);

    printf("  \033[1;36m\033[0m                                          \033[1;36m\033[0m\n");
    printf("  \033[1;36m╰──────────────────────────────────────────╯\033[0m\n\n");
}

void count_text_stats(const char *sentence, struct stats *stats)
{
    size_t i, len;
    char lastC = 0;
    len = strlen(sentence);

    if(len > 0)
        lastC = sentence[0];

    for(i=0; i<=len; i++)
    {
        if ((isspace((unsigned char)sentence[i]) || sentence[i] == '\0') && !isspace((unsigned char)lastC) && lastC != '\0')
            stats->words++;

        if (!isspace((unsigned char)sentence[i]) && sentence[i] != '\0')
            stats->chars++;

        lastC = sentence[i];
    }
}

double compute_time(const struct timespec tic, const struct timespec toc)
{
	return (toc.tv_sec - tic.tv_sec) + (toc.tv_nsec - tic.tv_nsec) / 1e9;
}

double compute_accuracy(unsigned int correct, unsigned int incorrect)
{
    unsigned int total = correct + incorrect;

    if (total > 0)
        return (double)correct / total * 100.0;

    return 0;
}
