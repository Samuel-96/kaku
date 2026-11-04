#ifndef STATS_H
#define STATS_H

#include <time.h>

struct stats
{
    unsigned int correct;
    unsigned int incorrect;
    unsigned int words;
    unsigned int chars;
    double accuracy;
    struct timespec tic;
    struct timespec toc;
};

void start_timer(struct stats *s);
void end_timer(struct stats *s);
void increase_correct(struct stats *s);
void increase_incorrect(struct stats *s);
void print_stats(const struct stats *s);
void count_text_stats(const char *sentence, struct stats *stats);
double compute_time(struct timespec tic, struct timespec toc);
double compute_accuracy(unsigned int correct, unsigned int incorrect);

#endif
