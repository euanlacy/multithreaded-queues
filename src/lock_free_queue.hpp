#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H

#include <atomic>
#include <optional>
#include <iostream>

#include "queue.hpp"

template<typename T>
class LFQueue {
private:
    struct Node {
        T data;
        // Has to be atomic for same reasong FQueue::dequeue holds both locks
        std::atomic<Node*> next;
        Node(T _data): data(std::move(_data)), next(nullptr) {};
    };
    std::atomic<Node*> head;
    std::atomic<Node*> tail;
    Node* original_head;

public:
    LFQueue() {
        static_assert(Queue<LFQueue<T>, T>);
        if (!this->head.is_lock_free()) {
            std::cout << "Atomics not lock-free" << std::endl;
        }

        // Initialise the queue with a dummy node, so that there is
        // a linked list connecting head with tail.
        this->head = new Node(T {});
        this->tail = this->head.load();
        this->original_head = this->head;
    }

    ~LFQueue() {
        // If not every item has been dequeued, and Ts are heap allocated
        // then they will be lost here.
        while (this->original_head) {
            Node* old = this->original_head;
            this->original_head = old->next.load(std::memory_order_acquire);
            delete old;
        }
    }

    void enqueue(T payload) {
        Node* new_node = new Node(std::move(payload));

        // This node always exists, even if the queue is empty
        Node* old_tail = this->tail.load(std::memory_order_acquire);

        // Expect it to be the old_tail, we want it to be the new_node
        // if it is some other value, then old_tail will become that value,
        // and try again.
        // We don't have to worry about the ABA problem as memory is never reused and,
        // the pointer to each node is therefore unique.
        while (!this->tail.compare_exchange_weak(old_tail, new_node, std::memory_order_acq_rel));

        // Despite being enqueued and ready for more threads to enqueue,
        // the value can not be dequeued until this operation finishes. 
        old_tail->next.store(new_node, std::memory_order_release);
    }

    // https://en.cppreference.com/w/cpp/atomic/memory_order
    // Atomics ordering:
    // 1. Acquire the old head
    // 2. Acquire the next ptr from the old head
    // 3. compare_exchange head with old_head and next (acq_rel)
    // 3. If next exists, return the data in the node

    std::optional<T> dequeue() {
        // This node always exists, even if the queue is empty
        Node* old_head = head.load(std::memory_order_acquire);

        // While the queue is not empty, and the head is not the next node, try to make the
        // head the next node.
        // NOTE: The old head will never be free'd, hazard pointers or garbage collection,
        //       could be used to remedy, but GC is generally blocking which would somewhat
        //       ruin the point of a lock-free queue.
        // We don't have to worry about the ABA problem as memory is never reused and,
        // the pointer to each node is therefore unique.
        Node* next;
        while (
            (next = old_head->next.load(std::memory_order_acquire))
            && !this->head.compare_exchange_weak(old_head, next, std::memory_order_acq_rel)
        );

        // If the queue is not empty return the data from the "popped" node
        if (next) {
            T& data = next->data;
            return std::move(data);
        }

        // Else return None.
        return {};
    }
};

#endif
