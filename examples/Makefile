BUILD_PATH ?= .
BIN_PATH ?= .

vpath %.o ${BUILD_PATH}
vpath % ${BIN_PATH}

all: concept_example generic_example unique_ptr multi_threaded

generic_example: generic_example.cpp
	${CXX} ${CXXFLAGS} -o ${BIN_PATH}/$@ $^

concept_example: concept_example.cpp
	${CXX} ${CXXFLAGS} -o ${BIN_PATH}/$@ $^

unique_ptr: unique_ptr.cpp
	${CXX} ${CXXFLAGS} -o ${BIN_PATH}/$@ $^

multi_threaded: multi_threaded.cpp
	${CXX} ${CXXFLAGS} -o ${BIN_PATH}/$@ $^
