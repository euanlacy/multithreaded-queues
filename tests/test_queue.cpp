#define CATCH_CONFIG_FAST_COMPILE

#include <tuple>
#include <cstdint>
#include <iostream>
#include <future>
#include <catch2/catch.hpp>

#include "../src/linked_coarse_queue.hpp"
#include "../src/coarse_queue.hpp"
#include "../src/fine_queue.hpp"
#include "../src/lock_free_queue.hpp"
#include "../src/single_thread_queue.hpp"
#include "../src/queue.hpp"
#include "../src/util.hpp"

template<typename T>
using QueueTypes = std::tuple<CQueue<T>>;

TEMPLATE_TEST_CASE("Single Threaded Tests", "[ints]",
                   CQueue<int>, LCQueue<int>, FQueue<int>, SFQueue<int>) {
    static_assert(Queue<TestType, int>);
    auto queue = TestType();

    SECTION("Dequeue while empty") {
        auto test = queue.dequeue();

        REQUIRE(!test.has_value());
    }

    SECTION("Enqueue Dequeue") {
        queue.enqueue(3);
        auto test = queue.dequeue();

        REQUIRE(test.has_value());
        REQUIRE(*test == 3);
    }

    SECTION("Enqueue Dequeue Dequeue") {
        queue.enqueue(14);

        auto fourteen = queue.dequeue();
        REQUIRE(fourteen.has_value());
        REQUIRE(*fourteen == 14);

        auto empty = queue.dequeue();
        REQUIRE(!empty.has_value());
    }

    SECTION("Enqueue Enqueue Dequeue Dequeue Dequeue") {
        queue.enqueue(14);
        queue.enqueue(25);

        auto fourteen = queue.dequeue();
        REQUIRE(fourteen.has_value());
        REQUIRE(*fourteen == 14);

        auto twenty_five = queue.dequeue();
        REQUIRE(twenty_five.has_value());
        REQUIRE(*twenty_five == 25);

        auto empty = queue.dequeue();
        REQUIRE(!empty.has_value());
    }

    SECTION("Dequeue Enqueue Dequeue") {
        auto empty = queue.dequeue();
        REQUIRE(!empty.has_value());

        queue.enqueue(152);

        auto one_five_two = queue.dequeue();
        REQUIRE(one_five_two.has_value());
        REQUIRE(*one_five_two == 152);
    }

    SECTION("Destructor works") {
        auto q = TestType();
        for (int i = 0; i < 1'000'000; i++) {
            q.enqueue(i);
        }
    }

    SECTION("FIFO Ordering") {
        enqueue_n(queue, 500);

        for (int i = 0; i < 500; i++) {
            auto value = queue.dequeue();
            REQUIRE(value.has_value());
            REQUIRE(*value == i);
        }

        auto empty = queue.dequeue();
        REQUIRE(!empty.has_value());
    }
}

// Both of the multithreaded tests fail in unpredictable ways with the single-threaded queue.

TEMPLATE_TEST_CASE("One Producer, One Consumer", "[yeet]", CQueue<int>, LCQueue<int>, FQueue<int>/*, SFQueue<int>*/) {
    auto queue = TestType();

    // This test has one producer thread which enqueues every int from 0..1'000'000 in order,
    // then it requires that the consumer recieves them in order
    auto producer = std::thread([&queue] {enqueue_n(queue, 1'000'000);});

    std::promise<bool> p; 
    std::future<bool> succeed = p.get_future(); 

    auto consumer = std::thread([&queue, &p]{
        int num_dequeued = 0; 
        while (num_dequeued != 1'000'000) {
            auto value = queue.dequeue();
            if (value) {
                if (*value != num_dequeued++) {
                    p.set_value(false);
                    return;
                }
            }
        }

        // There are no more elements in the queue
        p.set_value(!queue.dequeue());
    });

    consumer.join();
    producer.join();

    CHECK(succeed.get());
}

TEMPLATE_TEST_CASE("Two Producers, One Consumer", "[argh]", CQueue<int>, LCQueue<int>, FQueue<int>/*, SFQueue<int>*/) {
    auto queue = TestType();

    // This test creates two threads that both enqueue every int from 0..1'000'000, in order
    // It then requires that the consumer recieves two of every int.
    const int N = 1'000'000;
    auto consumer = std::thread([&queue] {
        int values[N] = {0};
        int total = 0;
        while (total < N * 2) {
            auto value = queue.dequeue();
            if (value) {
                values[*value]++;
                REQUIRE(values[*value] <= 2);
                total++;
            }
        }

        REQUIRE(total == N * 2);
        for (auto num : values) {
            REQUIRE(num == 2);
        }
    });

    auto thread1  = std::thread([&queue] { enqueue_n(queue, N); });
    auto thread2  = std::thread([&queue] { enqueue_n(queue, N); });

    consumer.join(), thread1.join(), thread2.join();
}


template <class Q>
requires Queue<Q, int>
std::vector<int> dequeue_test(Q& queue, int n) {
    std::vector<int> dequeued;
    int n_dequeued = 0;

    while (n_dequeued < n) {
        auto value = queue.dequeue();
        if (value) {
            n_dequeued++;
            dequeued.push_back(*value);
        }
    }

    return dequeued;
}


TEMPLATE_TEST_CASE("Two Producers, Two Consumers", "[argh]", CQueue<int>, LCQueue<int>, FQueue<int>/*, SFQueue<int>*/) {
    auto queue = TestType();

    // This test creates two threads that both enqueue every int from 0..1'000'000, in order
    // It then creates two consumers which return the values they dequeded, then checking
    // that all the ints have been deqeueued.
    const int N = 1'000'000;

    std::promise<std::vector<int>> first_half; 
    std::promise<std::vector<int>> second_half; 

    std::future<std::vector<int>> first_fut = first_half.get_future(); 
    std::future<std::vector<int>> second_fut = second_half.get_future(); 

    auto consumer1 = std::thread([&queue, &first_half] {
        auto values = dequeue_test(queue, N);
        first_half.set_value(values);
    });

    auto consumer2 = std::thread([&queue, &second_half] {
        auto values = dequeue_test(queue, N);
        second_half.set_value(values);
    });

    auto thread1  = std::thread([&queue] { enqueue_n(queue, N); });
    auto thread2  = std::thread([&queue] { enqueue_n(queue, N); });

    consumer1.join(), consumer2.join(), thread1.join(), thread2.join();

    auto values = first_fut.get();
    auto second = second_fut.get();
    values.insert(values.end(), second.begin(), second.end());

    int counts[N] = {0};
    for (auto value : values) {
        counts[value]++;
    }

    int i = 0;
    for (auto count : counts) {
        REQUIRE(count == 2);
        i++;
    }
}

