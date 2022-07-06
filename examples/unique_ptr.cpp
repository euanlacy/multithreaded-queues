#include <cstdint>
#include <iostream>
#include <memory>

#include "../src/queue.hpp"
#include "../src/coarse_queue.hpp"
#include "../src/fine_queue.hpp"
#include "../src/lock_free_queue.hpp"

struct Point {
    int32_t x;
    int32_t y;

    void print_point() {
        std::cout << "Point { x: " << this->x << ", y: " << this->y << " }" << std::endl;
    }
};

using Type = std::unique_ptr<Point>;

template <class Q>
requires Queue<Q, Type>
void test() {
    Q queue = Q();

    queue.enqueue(std::make_unique<Point>(5, 4));
    queue.enqueue(std::make_unique<Point>(3, 2));

    (*queue.dequeue())->print_point();
    (*queue.dequeue())->print_point();
}

int main() {
    test<CQueue<Type>>();
    test<FQueue<Type>>();
    test<LFQueue<Type>>();
}
