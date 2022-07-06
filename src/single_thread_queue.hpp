#ifndef SINGLE_THREAD_QUEUE_H
#define SINGLE_THREAD_QUEUE_H

#include <deque>
#include <mutex>
#include <optional>
#include <concepts>

#include "queue.hpp"

template<typename T>
class STQueue {
private:
    std::deque<T> data;
public:
    STQueue() {
        static_assert(Queue<STQueue<T>, T>);
    }

    void enqueue(T payload) {
        this->data.push_back(std::move(payload));
    }

    std::optional<T> dequeue() {
        if (!this->data.empty()) {
            auto ret = std::move(this->data.front());
            this->data.pop_front();
            return ret;
        } else {
            return {};
        }
    }
};

#endif
