#include <tuple>
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE

#include <cstdint>
#include <iostream>
#include <future>
#include <catch2/catch.hpp>

#include "../src/coarse_queue.hpp"
#include "../src/queue.hpp"

template<typename T>
using QueueTypes = std::tuple<CQueue<T>>;

TEMPLATE_TEST_CASE("Single Threaded Tests", "[ints]", CQueue<int>) {
    static_assert(Queue<TestType, int>);
    auto queue = TestType();

    queue.enqueue(3);
    auto test = queue.dequeue();

    REQUIRE(*test == 3);
}

TEST_CASE("2 Threads") {
    CQueue<uint32_t> queue {};

    auto fut  = std::async([&queue]{ queue.enqueue(3); });

    auto fut3 = std::async([&queue]{ return *queue.dequeue(); });
    auto fut4 = std::async([&queue]{ return *queue.dequeue(); });
    auto fut5 = std::async([&queue]{ return *queue.dequeue(); });

    auto fut1 = std::async([&queue]{ queue.enqueue(20); });
    auto fut2 = std::async([&queue]{ queue.enqueue(12); });

    fut.get(), fut1.get(), fut2.get();

    std::cout << fut3.get() << std::endl;
    std::cout << fut4.get() << std::endl;
    std::cout << fut5.get() << std::endl;
}

