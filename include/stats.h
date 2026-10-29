#ifndef STATS_H
#define STATS_H

struct stats
{
    unsigned int correct;
    unsigned int incorrect;
};

void increase_correct(struct stats *s);
void increase_incorrect(struct stats *s);
void print_stats(struct stats *s);

#endif
