#include <cstdint>
#include <iostream>

#include "test_class.cpp"

int main() {
    CQueue queue{};

    queue.enqueue(30);
    queue.enqueue(10);
    queue.enqueue(23);

    std::cout << queue.dequeue() << std::endl;
    std::cout << queue.dequeue() << std::endl;
    std::cout << queue.dequeue() << std::endl;
    std::cout << queue.dequeue() << std::endl;
}
