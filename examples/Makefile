CCX = g++
CPPFLAGS = --std=c++20 -O3 -g -Wmissing-field-initializers -Wall -Wextra

BUILD_PATH ?= .
BIN_PATH ?= .

vpath %.o ${BUILD_PATH}
vpath % ${BIN_PATH}

all: concept_example

concept_example: concept_example.cpp
	${CCX} ${CPPFLAGS} -o ${BIN_PATH}/$@ $^

