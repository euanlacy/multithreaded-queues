#ifndef FINE_QUEUE_H
#define FINE_QUEUE_H

#include <deque>
#include <memory>
#include <mutex>
#include <optional>
#include <iostream>

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
        // Create dummy node
        this->head = std::make_unique<Node>(T {});
        this->tail = this->head.get();
    }

    ~FQueue() {
        // Unique ptr destructor stack overflows for big lists
        // https://gcc.gcc.gnu.narkive.com/z4arPhYO/segmentation-fault-with-unique-ptr
        while (this->dequeue());
    }

    void enqueue(T payload) {
        // We can create the node, before holding the lock and modifying
        // the queue
        auto new_node = std::make_unique<Node>(std::move(payload));
        auto new_tail = new_node.get();

        std::lock_guard<std::mutex> tail_lock(this->tail_mutex);

        // The new node is appended to the tail
        // SAFETY: if the queue was empty, then this is the dummy node
        //         and is the same as the head, this does not matter as
        //         the head returns if it is the dummy node.
        this->tail->next = std::move(new_node);
        // The new tail is a ptr to the new node
        this->tail = new_tail;
    }

    std::optional<T> dequeue() {
        std::lock_guard<std::mutex> head_lock(this->head_mutex);

        // Head always exists as it is the dummy node, the first
        // node with data is the next one, if that does not exist
        // then the queue is empty, and return None.
        {
            // Mutex required as enqueue could be writing to the
            // dummy node's next pointer if the queue is empty
            // If it is empty we return, if it is not, then enqueue
            // can not be writing to the node, so it is safe to read
            // the data from it.
            std::lock_guard<std::mutex> tail_lock(this->tail_mutex);
            if (!this->head->next) { return {}; }
        }

        // Get the data from the node
        auto value = std::move(this->head->next->data);
        // The next node becomes the head, and the old head is
        // automatically free'd as it is held by a unique ptr.
        this->head = std::move(this->head->next);

        return value;
    }
};

#endif
