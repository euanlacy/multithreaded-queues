#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <iostream>
#include <future>
#include <concepts>
#include <catch2/catch.hpp>

#include "../src/single_thread_queue.hpp"
#include "../src/coarse_queue.hpp"
#include "../src/linked_coarse_queue.hpp"
#include "../src/lock_free_queue.hpp"
#include "../src/fine_queue.hpp"
#include "../src/queue.hpp"
#include "../src/util.hpp"

const int BIG_ITERATIONS = 10'000'000;

template <class Q>
requires Queue<Q, int>
void bench_enqueue() {
    Q queue = Q();

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < BIG_ITERATIONS; i++) {
        queue.enqueue(5);
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed = end - start; 
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
    std::cout << "took " << elapsed_us << " with an avg of " << elapsed / BIG_ITERATIONS << std::endl;
}

template <class Q>
requires Queue<Q, int>
void bench_dequeue() {
    Q queue = Q();

    for (int i = 0; i < BIG_ITERATIONS; i++) {
        queue.enqueue(5);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < BIG_ITERATIONS; i++) {
        queue.dequeue();
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed = end - start; 
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
    std::cout << "took " << elapsed_us << " with an avg of " << elapsed / BIG_ITERATIONS << std::endl;
}

TEST_CASE("Single Threaded Tests", "[int]") {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Benchmark Enqueue" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    std::cout << "SFQueue" << std::endl;
    bench_enqueue<SFQueue<int>>();

    std::cout << std::endl << "LCQueue" << std::endl;
    bench_enqueue<LCQueue<int>>();

    std::cout << std::endl << "CQueue" << std::endl;
    bench_enqueue<CQueue<int>>();

    std::cout << std::endl << "FQueue" << std::endl;
    bench_enqueue<FQueue<int>>();

    std::cout << std::endl << "LFQueue" << std::endl;
    bench_enqueue<LFQueue<int>>();

    std::cout << std::endl;

    std::cout << "--------------------------------" << std::endl;
    std::cout << "Benchmark Dequeue" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    std::cout << "SFQueue" << std::endl;
    bench_dequeue<SFQueue<int>>();

    std::cout << std::endl << "LCQueue" << std::endl;
    bench_dequeue<LCQueue<int>>();

    std::cout << std::endl << "CQueue" << std::endl;
    bench_dequeue<CQueue<int>>();

    std::cout << std::endl << "FQueue" << std::endl;
    bench_dequeue<FQueue<int>>();

    std::cout << std::endl << "LFQueue" << std::endl;
    bench_dequeue<LFQueue<int>>();

    std::cout << std::endl;
}

template <class Q>
requires Queue<Q, int>
void bench_one_one() {
    Q queue = Q();
    auto start = std::chrono::high_resolution_clock::now();

    auto consumer  = std::thread([&queue] { dequeue_n(queue, 10'000'000); });
    auto producer  = std::thread([&queue] { enqueue_n(queue, 10'000'000); });

    consumer.join();
    producer.join();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
    std::cout << "took " << elapsed_ms << std::endl;
}

template <class Q>
requires Queue<Q, int>
void bench_five_one() {
    Q queue = Q();
    auto start = std::chrono::high_resolution_clock::now();

    auto consumer   = std::thread([&queue] { dequeue_n(queue, 5'000'000); });
    auto producer1  = std::thread([&queue] { enqueue_n(queue, 1'000'000); });
    auto producer2  = std::thread([&queue] { enqueue_n(queue, 1'000'000); });
    auto producer3  = std::thread([&queue] { enqueue_n(queue, 1'000'000); });
    auto producer4  = std::thread([&queue] { enqueue_n(queue, 1'000'000); });
    auto producer5  = std::thread([&queue] { enqueue_n(queue, 1'000'000); });

    consumer.join();
    producer1.join();
    producer2.join();
    producer3.join();
    producer4.join();
    producer5.join();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
    std::cout << "took " << elapsed_ms << std::endl;
}

template <class Q>
requires Queue<Q, int>
void bench_three_three() {
    Q queue = Q();
    auto start = std::chrono::high_resolution_clock::now();

    auto consumer1 = std::thread([&queue] { dequeue_n(queue, 2'000'000); });
    auto consumer2 = std::thread([&queue] { dequeue_n(queue, 2'000'000); });
    auto consumer3 = std::thread([&queue] { dequeue_n(queue, 2'000'000); });

    auto producer1 = std::thread([&queue] { enqueue_n(queue, 2'000'000); });
    auto producer2 = std::thread([&queue] { enqueue_n(queue, 2'000'000); });
    auto producer3 = std::thread([&queue] { enqueue_n(queue, 2'000'000); });

    consumer1.join();
    consumer2.join();
    consumer3.join();

    producer1.join();
    producer2.join();
    producer3.join();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
    std::cout << "took " << elapsed_ms << std::endl;
}

TEST_CASE("Many Threads") {
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Benchmark One Producer, One consumer" << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    std::cout << "CQueue" << std::endl;
    bench_one_one<CQueue<int>>();

    std::cout << std::endl << "LCQueue" << std::endl;
    bench_one_one<LCQueue<int>>();

    std::cout << std::endl << "FQueue" << std::endl;
    bench_one_one<FQueue<int>>();

    std::cout << std::endl << "LFQueue" << std::endl;
    bench_one_one<LFQueue<int>>();

    std::cout << std::endl;

    std::cout << "--------------------------------" << std::endl;
    std::cout << "Benchmark 5 Producers, One Consumer" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    std::cout << "CQueue" << std::endl;
    bench_five_one<CQueue<int>>();

    std::cout << std::endl << "LCQueue" << std::endl;
    bench_five_one<LCQueue<int>>();

    std::cout << std::endl << "FQueue" << std::endl;
    bench_five_one<FQueue<int>>();

    std::cout << std::endl << "LFQueue" << std::endl;
    bench_five_one<LFQueue<int>>();

    std::cout << std::endl;

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Benchmark three Producers, three Consumer" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    std::cout << "CQueue" << std::endl;
    bench_three_three<CQueue<int>>();

    std::cout << std::endl << "LCQueue" << std::endl;
    bench_three_three<LCQueue<int>>();

    std::cout << std::endl << "FQueue" << std::endl;
    bench_three_three<FQueue<int>>();

    std::cout << std::endl << "LFQueue" << std::endl;
    bench_three_three<LFQueue<int>>();

    std::cout << std::endl;
}

