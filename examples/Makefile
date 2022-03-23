CCX = g++
CPPFLAGS = -std=c++20 -O3 -g -Wmissing-field-initializers -Wall -Wextra

BUILD_PATH ?= .
BIN_PATH ?= .

vpath %.o ${BUILD_PATH}
vpath % ${BIN_PATH}

all: long short

long: long.c knuth_bendix.o intlist.o lists.o brute_force.o
	${CC} -o ../bin/$@ $^

short: short.c knuth_bendix.o intlist.o lists.o brute_force.o
	${CC} -o ../bin/$@ $^
