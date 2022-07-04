#ifndef HAZARD_POINTER_H
#define HAZARD_POINTER_H

#include <list>

// Single-writer, multi-reader shared pointer
template<typename T>
class HazardPointer {
private:
    std::list<T> list;
    T* node;

public:
};

#endif
