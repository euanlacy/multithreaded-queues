#include <memory>

template <typename T>
class CQueue {
public:
    CQueue();
    ~CQueue();
    void enqueue(T payload);
    std::shared_ptr<T> dequeue();
};

