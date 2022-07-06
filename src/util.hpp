#ifndef UTIL_HPP
#define UTIL_HPP

#include <concepts>

#include "queue.hpp"

template <class Q>
requires Queue<Q, int>
void enqueue_n(Q& queue, int n) {
    for (int i = 0; i < n; i++) {
        queue.enqueue(i);
    }
}

template <class Q>
requires Queue<Q, int>
void dequeue_n(Q& queue, int n) {
    int n_dequeued = 0;
    while (n_dequeued < n) {
        if (queue.dequeue()) {
            n_dequeued++;
        }
    }
}

#endif
