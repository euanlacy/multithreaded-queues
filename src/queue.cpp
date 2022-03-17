#include <atomic>
#include <deque>
#include <mutex>
#include <memory>

template <typename T>
class CQueue {
private:
    std::mutex mut;
    std::deque<T> data;
public:
    CQueue();
    ~CQueue();
    void enqueue(T payload) {
        std::lock_guard<std::mutex> lockGuard(this->mut);
        this->data.push(payload);
    }

    std::shared_ptr<T> dequeue() {
        std::lock_guard<std::mutex> lockGuard(this->mut);

        if (!this->data.empty()) {
            std::shared_ptr<T> ret = this->data.front();
            this->data.pop_front();
            return ret;
        } else {
            return std::shared_ptr<T>();
        }
    }
};
