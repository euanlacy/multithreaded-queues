#ifndef COARSE_QUEUE_H
#define COARSE_QUEUE_H

#include <deque>
#include <memory>
#include <mutex>
#include <condition_variable>

#include "queue.hpp"

template<typename T>
class CQueue {
private:
    std::mutex mut;
    std::deque<T> data;
    std::condition_variable cond_var;
public:
    CQueue() {
        static_assert(Queue<CQueue<T>, T>);
    }

    void enqueue(T payload) {
        std::lock_guard<std::mutex> lockGuard(this->mut);
        this->data.push_back(std::move(payload));
        cond_var.notify_one();
    }

    std::shared_ptr<T> dequeue() {
        std::unique_lock<std::mutex> mlock(this->mut);

        while (this->data.empty()) {
            this->cond_var.wait(mlock);
        }

        auto ret = std::make_shared<T>(this->data.front());
        this->data.pop_front();
        return ret;
    }
};

#endif
