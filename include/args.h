#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>

struct arguments {
    char *text;
    char *file;
    long time;
};

void print_usage(void);
bool parse_arguments(int argc, char *argv[]);
const struct arguments *get_arguments(void);

#endif
