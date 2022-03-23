#include <cstdint>
#include <iostream>

#include "../src/queue.hpp"
#include "../src/coarse_queue.hpp"

typedef uint32_t u32;
typedef int32_t  i32;

struct Point {
    i32 x;
    i32 y;

    void print_point() {
        std::cout << "Point { x: " << this->x << ", y: " << this->y << " }" << std::endl;
    }
};

int main() {
    auto p1 = Point { .x = 10, .y = 32 };
    auto p2 = Point { .x = 2,  .y = 5  };
    auto p3 = Point { .x = 1,  .y = 9  };

    auto queue = CQueue<Point>();

    queue.enqueue(p1);
    queue.enqueue(p2);
    queue.enqueue(p3);

    queue.dequeue()->print_point();
    queue.dequeue()->print_point();
    queue.dequeue()->print_point();
}
