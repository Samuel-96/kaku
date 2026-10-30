#include <stdio.h>
#include <string.h>

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
    printf("Correct:    %u\n", s->correct);
    printf("Incorrect:  %u\n", s->incorrect);
    printf("Characters: %u\n", s->chars);
}

void count_words(const char *sentence, struct stats *stats)
{
    size_t i, len;
    char lastC;
    len=strlen(sentence);

    if(len > 0)
        lastC = sentence[0];

    for(i=0; i<=len; i++)
    {
        if((sentence[i]==' ' || sentence[i]=='\0') && lastC != ' ')
        {
            stats->words++;
        }
        if (sentence[i] != ' ' && sentence[i] != '\0') stats->chars++;
        lastC = sentence[i];
    }
}
