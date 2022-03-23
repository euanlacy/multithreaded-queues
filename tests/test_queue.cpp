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

    SECTION("Dequeue while empty") {
        auto test = queue.dequeue();

        REQUIRE(!test.has_value());
    }

    SECTION("Enqueue Dequeue") {
        queue.enqueue(3);
        auto test = queue.dequeue();

        REQUIRE(*test == 3);
    }

    SECTION("Enqueue Dequeue Dequeue") {
        queue.enqueue(14);

        auto fourteen = queue.dequeue();
        REQUIRE(*fourteen == 14);

        auto empty = queue.dequeue();
        REQUIRE(!empty.has_value());
    }

    SECTION("Dequeue Enqueue Dequeue") {
        auto empty = queue.dequeue();
        REQUIRE(!empty.has_value());

        queue.enqueue(152);

        auto one_five_two = queue.dequeue();
        REQUIRE(*one_five_two == 152);
    }

    // Enqueues 100 random numbers in [1, 500), then checks they dequeue in the correct order.
    SECTION("FIFO Ordering") {
        auto numbers = GENERATE(take(100, random(1, 500)));

        queue.enqueue(numbers);
        auto values = queue.dequeue();

        REQUIRE(*values == numbers);
    }
}

TEST_CASE("Many Threads") {
    CQueue<uint32_t> queue {};

    auto fut  = std::async([&queue]{ queue.enqueue(3); });
    auto fut1 = std::async([&queue]{ queue.enqueue(20); });
    auto fut2 = std::async([&queue]{ queue.enqueue(12); });

    auto fut3 = std::async([&queue]{ return *queue.dequeue(); });
    auto fut4 = std::async([&queue]{ return *queue.dequeue(); });
    auto fut5 = std::async([&queue]{ return *queue.dequeue(); });

    fut.get(), fut1.get(), fut2.get();

    std::cout << fut3.get() << std::endl;
    std::cout << fut4.get() << std::endl;
    std::cout << fut5.get() << std::endl;
}

