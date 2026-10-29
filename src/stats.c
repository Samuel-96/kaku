#include <stdio.h>
#include "../include/stats.h"

void increase_correct(struct stats *s)
{
    s->correct++;
}

void increase_incorrect(struct stats *s)
{
    s->incorrect++;
}

void print_stats(struct stats *s)
{
    printf("Correct:   %u\n", s->correct);
    printf("Incorrect: %u\n", s->incorrect);
}
