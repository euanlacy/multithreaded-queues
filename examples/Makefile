CC = gcc
CFLAGS = -pg -O3 -Wmissing-field-initializers -Wall -Werror

BUILD_PATH ?= .
BIN_PATH ?= .

vpath %.o ${BUILD_PATH}
vpath % ${BIN_PATH}

all: long short

long: long.c knuth_bendix.o intlist.o lists.o brute_force.o
	$(CC) -o ../bin/$@ $^

short: short.c knuth_bendix.o intlist.o lists.o brute_force.o
	$(CC) -o ../bin/$@ $^
