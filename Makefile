# ----------- #
#  Variables  #
# ----------- #

CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -g

TARGET = build/kaku
SOURCE = src/main.c src/terminal.c src/typing_test.c src/cli.c lib/argparse/argparse.c

# ---------------- #
#  Phony Targets   #
# ---------------- #

# Declare targets that do not represent actual files.
.PHONY: all clean

# Default target: build the executable.
all: $(TARGET)


# ------------------- #
#  Build Instructions #
# ------------------- #

# Compile the executable from the source file.
# Ensure the build directory exists before compilation.
$(TARGET): $(SOURCE) include/terminal.h include/typing_test.h include/cli.h lib/argparse/argparse.h | build
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

# Create the build directory if it does not exist.
build:
	mkdir -p build


# ---------------- #
#  Clean Target    #
# ---------------- #

# Remove generated build artifacts.
clean:
	rm -rf build
