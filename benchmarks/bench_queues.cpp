#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <cstdint>
#include <iostream>
#include <future>
#include <catch2/catch.hpp>

#include "../src/coarse_queue.hpp"
#include "../src/fine_queue.hpp"
#include "../src/queue.hpp"

TEMPLATE_TEST_CASE("Single Threaded Tests", "[int]", CQueue<int>, FQueue<int>) {
    static_assert(Queue<TestType, int>);
    auto queue = TestType();

    BENCHMARK("Enqueue") {
        queue.enqueue(1);
    };

    queue.enqueue(1);

    BENCHMARK("Dequeue") {
        return queue.dequeue();
    };
}

TEMPLATE_TEST_CASE("Many Threads", "[int]", CQueue<int>, FQueue<int>) {
    static_assert(Queue<TestType, int>);
    auto queue = TestType();

    BENCHMARK("One Producer - One Consumer") {
        auto producer = std::async([&queue]{
            for (int i = 1; i <= 100; i++) {
                queue.enqueue(i);
            }
        });

        auto consumer = std::async([&queue]{
            int num_dequeued = 0; 
            while (num_dequeued != 100) {
                auto value = queue.dequeue();
                if (value) {
                    num_dequeued += 1;
                }
            }
        });

        producer.get();
        consumer.get();
    };

    BENCHMARK("5 Producers - One Consumer") {
        auto p1 = std::async([&queue]{
            for (int i = 1; i <= 20; i++) {
                queue.enqueue(i);
            }
        });

        auto p2 = std::async([&queue]{
            for (int i = 1; i <= 20; i++) {
                queue.enqueue(i);
            }
        });

        auto p3 = std::async([&queue]{
            for (int i = 1; i <= 20; i++) {
                queue.enqueue(i);
            }
        });

        auto p4 = std::async([&queue]{
            for (int i = 1; i <= 20; i++) {
                queue.enqueue(i);
            }
        });

        auto p5 = std::async([&queue]{
            for (int i = 1; i <= 20; i++) {
                queue.enqueue(i);
            }
        });

        auto consumer = std::async([&queue]{
            int num_dequeued = 0; 
            while (num_dequeued != 100) {
                auto value = queue.dequeue();
                if (value) {
                    num_dequeued += 1;
                }
            }
        });

        p1.get();
        p2.get();
        p3.get();
        p4.get();
        p5.get();
        consumer.get();
    };
}

