#ifndef QUEUE_H
#define QUEUE_H

#include <memory>
#include <concepts>

template<class Q, typename P>
concept Queue = requires(Q queue, P payload) {
    queue.enqueue(payload);
    { queue.dequeue() } -> std::convertible_to<std::shared_ptr<P>>;
    { Q() } -> std::same_as<Q>;
};

#endif
