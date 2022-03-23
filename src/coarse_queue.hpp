#ifndef COARSE_QUEUE_H
#define COARSE_QUEUE_H

#include <deque>
#include <mutex>
#include <optional>

#include "queue.hpp"

template<typename T>
class CQueue {
private:
    std::mutex mut;
    std::deque<T> data;
public:
    CQueue() {
        static_assert(Queue<CQueue<T>, T>);
    }

    void enqueue(T payload) {
        std::lock_guard<std::mutex> lockGuard(this->mut);
        this->data.push_back(std::move(payload));
    }

    std::optional<T> dequeue() {
        std::lock_guard<std::mutex> lockGuard(this->mut);

        if (!this->data.empty()) {
            auto ret = this->data.front();
            this->data.pop_front();
            return ret;
        } else {
            return {};
        }
    }
};

#endif
