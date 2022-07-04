#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H

#include <deque>
#include <memory>
#include <mutex>
#include <atomic>
#include <optional>

#include "queue.hpp"

template<typename T>
class LFQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T _data): data(std::move(_data), next(nullptr)) {};
    };
    std::atomic<Node*> head;
    std::atomic<Node*> tail;

public:
    LFQueue() {
        static_assert(Queue<LFQueue<T>, T>);
        this->head = nullptr;
        this->tail = nullptr;
    }

    void enqueue(T payload) {
        auto new_node = new Node(std::move(payload));
        new_node->data = std::move(payload);
        new_node->next = head;

        // Weak in while, strong if not in while
        while (!this->head.compare_exchange_strong(new_node->next, new_node));
    }

    std::optional<T> dequeue() {
        Node* old_head = head.load();

        while (old_head != nullptr && !head.compare_exchange_strong(old_head, old_head->next)) {
            if (old_head == nullptr) return {};
        }

        return std::move(old_head->data);
    }
};

#endif
