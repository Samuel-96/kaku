#include "../lib/argparse/argparse.h" // argsparse library
#include "../include/cli.h"           // own cli.h header file

static ArgParser* parser;

void init_parser(void)
{
    parser = ap_new_parser();

    ap_set_helptext(parser, "Usage: kaku...");
    ap_set_version(parser, "1.0");
    ap_add_str_opt(parser, "text t", "");
}

void parse_args(int argc, char *argv[])
{
    ap_parse(parser, argc, argv);
}

char *get_text(void)
{
    return ap_get_str_value(parser, "text");
}

void free_parser(void)
{
    ap_free(parser);
}
