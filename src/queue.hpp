#ifndef QUEUE_H
#define QUEUE_H

#include <optional>
#include <concepts>

template<class Q, typename P>
concept Queue = requires(Q queue, P payload) {
    queue.enqueue(std::move(payload));
    { queue.dequeue() } -> std::same_as<std::optional<P>>;
    { Q() } -> std::same_as<Q>;
};

#endif
