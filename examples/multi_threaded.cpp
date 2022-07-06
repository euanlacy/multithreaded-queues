#include <cstdint>
#include <iostream>
#include <thread>

#include "../src/queue.hpp"
#include "../src/coarse_queue.hpp"
#include "../src/fine_queue.hpp"
#include "../src/lock_free_queue.hpp"
#include "../src/linked_coarse_queue.hpp"
#include "../src/util.hpp"

struct Point {
    int x;
    int y;
};

template <class Q>
requires Queue<Q, int>
void test() {
    Q queue = Q();

    auto producer1 = std::thread([&queue] {enqueue_n(queue, 1000);});
    auto producer2 = std::thread([&queue] {enqueue_n(queue, 1000);});

    auto consumer1 = std::thread([&queue] {dequeue_n(queue, 1000);});
    auto consumer2 = std::thread([&queue] {dequeue_n(queue, 1000);});

    producer1.join();
    producer2.join();

    consumer1.join();
    consumer2.join();
}

// This program is useful to test and inspect thread safety using tools
// like -fsanitize=thread, valgrind --tool=drd, and valgrind --tool=hellgrind
// note: these tools are neither absolute guarantees of thread-saftey or the
// lack of thread-safety.
int main() {
    test<CQueue<int>>();
    test<LCQueue<int>>();
    test<FQueue<int>>();
    test<LFQueue<int>>();
}
