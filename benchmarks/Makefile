BUILD_PATH ?= .
BIN_PATH ?= .

SRCS := ${wildcard *.cpp}
vpath %.o ${BUILD_PATH}
vpath % ${BIN_PATH}

all: bench_queues

bench_queues: bench_queues.cpp catch.o
	${CXX} ${CXXFLAGS} -o ${BIN_PATH}/$@ $^

