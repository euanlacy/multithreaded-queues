#include <memory>

template <typename T>
class CQueue {
public:
    void enqueue(T payload);
    std::shared_ptr<T> dequeue();
};

