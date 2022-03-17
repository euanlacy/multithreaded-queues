#include <cstdint>
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE

#include <catch2/catch.hpp>

#include "../src/queue.hpp"

#define BENCHMARK(...)

TEST_CASE("Create") {
    CQueue<uint32_t> queue{};
    queue.enqueue(0);
    REQUIRE(queue.dequeue().get() == 0);
}

