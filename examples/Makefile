BUILD_PATH ?= .
BIN_PATH ?= .

vpath %.o ${BUILD_PATH}
vpath % ${BIN_PATH}

all: concept_example generic_example

generic_example: generic_example.cpp
	${CXX} ${CXXFLAGS} -o ${BIN_PATH}/$@ $^
concept_example: concept_example.cpp
	${CXX} ${CXXFLAGS} -o ${BIN_PATH}/$@ $^

