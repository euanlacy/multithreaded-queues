SRCS := ${wildcard *.cpp}
OBJS := ${SRCS:%.cpp=%.o}

BUILD_PATH ?= .

vpath %.o ${BUILD_PATH}

all: ${OBJS}

%.o: %.cpp
	${CXX} ${CXXFLAGS} -c -o ${BUILD_PATH}/$@ $^

.PHONY: clean
clean:
	rm *.o

