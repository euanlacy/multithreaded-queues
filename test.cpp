#include <cstdint>
#include <iostream>

#include "src/queue.hpp"

typedef struct {
    uint32_t x;
    uint32_t y;
} Point;

int main() {
    auto p1 = Point { .x = 10, .y = 32 };
    auto p2 = Point { .x = 2, .y = 5 };
    auto p3 = Point { .x = 1, .y = 9 };

    CQueue<uint32_t> queue{};

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    std::cout << *queue.dequeue() << std::endl;
    std::cout << *queue.dequeue() << std::endl;
    std::cout << *queue.dequeue() << std::endl;
}
