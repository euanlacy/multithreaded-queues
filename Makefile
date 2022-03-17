BUILD_DIR := ./build/.
BIN_DIR := ./bin/.
SRCS := $(shell find ./src -name '*.c')
OBJS := $(SRCS:%=$(BULID_DIR)/%.o)
CC := gcc
CXX := g++
CFLAGS := -pg -O3
CPPFLAGS := --std=c++17 -O3

vpath %.o ${BUILD_DIR}

all: compile

compile: export BUILD_PATH = ../${BUILD_DIR}
compile: export BIN_PATH = ../${BIN_DIR}
compile:
	cd src && ${MAKE}

test: export BUILD_PATH = ../${BUILD_DIR}
test: export BIN_PATH = ../${BIN_DIR}
test: compile
	cd tests && ${MAKE}

# bench: export BUILD_PATH = ../${BUILD_DIR}
# bench: export BIN_PATH = ../${BIN_DIR}
# bench: compile
# 	cd benchmarks && ${MAKE}

examples: export BUILD_PATH = ../${BUILD_DIR}
examples: export BIN_PATH = ../${BIN_DIR}
examples: compile
	cd examples && ${MAKE}

.PHONY: all test clean compile

clean:
	rm -r ${BUILD_DIR} ${BIN_DIR}