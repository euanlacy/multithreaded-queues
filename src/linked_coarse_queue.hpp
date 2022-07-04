#ifndef LINKED_COARSE_QUEUE_H
#define LINKED_COARSE_QUEUE_H

#include <list>
#include <mutex>
#include <optional>

#include "queue.hpp"

template<typename T>
class LCQueue {
private:
    std::mutex mut;
    std::list<T> data;
public:
    LCQueue() {
        static_assert(Queue<LCQueue<T>, T>);
    }

    void enqueue(T payload) {
        std::lock_guard<std::mutex> lockGuard(this->mut);
        this->data.push_back(std::move(payload));
    }

    std::optional<T> dequeue() {
        std::lock_guard<std::mutex> lockGuard(this->mut);

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
