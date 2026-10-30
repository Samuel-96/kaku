#ifndef STATS_H
#define STATS_H

struct stats
{
    unsigned int correct;
    unsigned int incorrect;
    unsigned int words;
    unsigned int chars;
};

void increase_correct(struct stats *s);
void increase_incorrect(struct stats *s);
void print_stats(struct stats *s);
void count_words(const char *sentence, struct stats *stats);

#endif
