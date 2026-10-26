CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -g

TARGET = build/kaku
SOURCE = src/main.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCE) | build
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

build:
	mkdir -p build

clean:
	rm -rf build
