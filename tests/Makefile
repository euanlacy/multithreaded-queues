BUILD_PATH ?= .
BIN_PATH ?= .

SRCS := ${wildcard *.cpp}
vpath %.o ${BUILD_PATH}
vpath % ${BIN_PATH}

all: test_queues

test_queues: test_queue.cpp catch.o
	${CXX} ${CXXFLAGS} -o ${BIN_PATH}/$@ $^

