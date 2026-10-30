#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include "../include/args.h"

static struct arguments arguments; // defined in header file

/**
 * @brief Initializes struct arguments values.
 */
static void init_default()
{
    // arguments.text = "this is an automatic sample text because you didn't provide a value to -t argument";
    arguments.text = NULL;
    arguments.file = NULL;
    arguments.time = 30;
}

void print_usage()
{
    printf(
            "Usage: kaku [OPTIONS]\n"
            "\n"
            "A simple terminal typing test.\n"
            "\n"
            "Options:\n"
            "  -t, --text   TEXT       Use the provided text for the test.\n"
            "  -f, --file   FILE       Load the test text from a file.\n"
            "  -c, --chrono SECONDS    Set the test duration (default: 30).\n"
            "  -h, --help              Show this help message.\n"
            "\n"
            "Examples:\n"
            "  kaku -t \"Hello world, this is a typing test.\"\n"
            "  kaku --file texts/english.txt --chrono 60\n");
}

static bool check_args()
{
    // Didn't provide any of these arguments or provided BOTH arguments
    if (arguments.text == NULL && arguments.file == NULL) return false;
    if (arguments.text != NULL && arguments.file != NULL) return false;

    // The text provided is empty
    if (arguments.text != NULL && strlen(arguments.text) == 0) return false;

    // Time is not valid
    if (arguments.time <= 0) return false;

    return true;
}

/**
 * @brief Converts and validates a time argument.
 *
 * Parses a string as a base-10 integer and verifies
 * that the entire string represents a positive number.
 *
 * @param optarg String containing the time in seconds.
 * @return The parsed time on success, or -1 on failure.
 */
long check_time_argument(const char* optarg)
{
    char *endptr;
    errno = 0;
    long time = strtol(optarg, &endptr, 10);

    // Time converted from string to long don't match expected value
    if (endptr == optarg || *endptr != '\0' || errno == ERANGE || time <= 0) return -1;

    return time;
}

bool parse_arguments(int argc, char *argv[])
{
    int opt = 0, long_index = 0;

    init_default();

    static struct option long_options[] =
    {
        {"text",   required_argument,       0,  't' },
        {"file",   required_argument,       0,  'f' },
        {"chrono", required_argument,       0,  'c' },
    };

    while ((opt = getopt_long(argc, argv,"t:f:c:", long_options, &long_index )) != -1)
    {
        switch (opt) {
             case 't':
                arguments.text = optarg;
                break;
             case 'f':
                arguments.file  = optarg;
                break;
             case 'c':
                arguments.time = check_time_argument(optarg);
                break;
             default: print_usage();
                 exit(EXIT_FAILURE);
        }
    }

    // Check if there are more arguments that were not processed
    if (optind < argc) return false;

    return check_args();
}

const struct arguments *get_arguments(void)
{
    return &arguments;
}
