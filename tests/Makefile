CXX = g++
CPPFLAGS = --std=c++17 -Wall -Wextra
BUILD_PATH ?= .
BIN_PATH ?= .

SRCS := ${wildcard *.cpp}
vpath %.o ${BUILD_PATH}
vpath % ${BIN_PATH}

all: test_queue

test_queue: test_queue.cpp queue.o
	${CXX} ${CPPFLAGS} -o ${BIN_PATH}/$@ $^

