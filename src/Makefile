CCX = g++
CPPFLAGS = -std=c++20 -O3 -g -Wmissing-field-initializers -Wall -Wextra

SRCS := ${wildcard *.cpp}
OBJS := ${SRCS:%.cpp=%.o}

BUILD_PATH ?= .

vpath %.o ${BUILD_PATH}

all: ${OBJS}

%.o: %.cpp
	${CCX} ${CPPFLAGS} -c -o ${BUILD_PATH}/$@ $^

.PHONY: clean
clean:
	rm *.o

