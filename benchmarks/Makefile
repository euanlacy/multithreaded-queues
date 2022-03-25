CXX = g++
CPPFLAGS = --std=c++20 -O3 -Wall -Wextra
BUILD_PATH ?= .
BIN_PATH ?= .

SRCS := ${wildcard *.cpp}
vpath %.o ${BUILD_PATH}
vpath % ${BIN_PATH}

all: bench_queues

bench_queues: bench_queues.cpp
	${CXX} ${CPPFLAGS} -o ${BIN_PATH}/$@ $^

