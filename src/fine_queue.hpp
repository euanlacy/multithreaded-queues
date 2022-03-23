#ifndef FINE_QUEUE_H
#define FINE_QUEUE_H

#include <deque>
#include <memory>
#include <mutex>
#include <optional>

#include "queue.hpp"

template<typename T>
class FQueue {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node(T _data): data(std::move(_data)) {};
    };
    std::unique_ptr<Node> head;
    Node* tail;
    std::mutex head_mutex;
    std::mutex tail_mutex;
public:
    FQueue() {
        static_assert(Queue<FQueue<T>, T>);
        this->head = std::make_unique<Node>(T {});
        this->tail = this->head.get();
    }

    void enqueue(T payload) {
        auto dummy_node = std::make_unique<Node>(T {});
        auto new_tail = dummy_node.get();

        std::lock_guard<std::mutex> tail_lock(this->tail_mutex);

        this->tail->next = std::move(dummy_node);
        this->tail->data = std::move(payload);
        this->tail = new_tail;
    }

    std::optional<T> dequeue() {
        std::lock_guard<std::mutex> head_lock(this->head_mutex);

        if (!this->head->next) { return {}; }

        auto value = std::move(this->head->data);
        this->head = std::move(this->head->next);

        return value;
    }
};

#endif
