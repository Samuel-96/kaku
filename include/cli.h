#ifndef CLI_H
#define CLI_H

void init_parser(void);
void parse_args(int argc, char *argv[]);
char *get_text(void);
void free_parser(void);

#endif
