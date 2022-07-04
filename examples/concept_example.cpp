#include <cstdint>
#include <iostream>

#include "../src/queue.hpp"
#include "../src/coarse_queue.hpp"
#include "../src/fine_queue.hpp"
#include "../src/lock_free_queue.hpp"

typedef uint32_t u32;
typedef int32_t  i32;

struct Point {
    i32 x;
    i32 y;
};

template <class Q>
requires Queue<Q, u32>
void test() {
    auto queue = Q();

    queue.enqueue(5);
    queue.enqueue(3);

    std::cout << *queue.dequeue() << std::endl;
    std::cout << *queue.dequeue() << std::endl;
}

int main() {
    test<CQueue<u32>>();
    test<FQueue<u32>>();
    /* test<LFQueue<u32>>(); */
}
