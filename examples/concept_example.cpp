#include <cstdint>
#include <iostream>

#include "../src/queue.hpp"
#include "../src/coarse_queue.hpp"

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
    /* auto p1 = Point { .x = 10, .y = 32 }; */
    /* auto p2 = Point { .x = 2,  .y = 5 }; */
    /* auto p3 = Point { .x = 1,  .y = 9 }; */

    test<CQueue<u32>>();

    /* queue.enqueue(p1); */
    /* queue.enqueue(p2); */
    /* queue.enqueue(p3); */

    /* std::cout << queue.dequeue()->x << std::endl; */
    /* std::cout << queue.dequeue()->y << std::endl; */
    /* std::cout << queue.dequeue()->y << std::endl; */
}
