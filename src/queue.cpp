#include <atomic>
#include <deque>
#include <mutex>
#include <memory>
#include <cstdint>

template <typename T>
class CQueue {
private:
    std::mutex mut;
    std::deque<T> data;
public:
    void enqueue(T payload) {
        std::lock_guard<std::mutex> lockGuard(this->mut);
        this->data.push_back(payload);
    }

    std::shared_ptr<T> dequeue() {
        std::lock_guard<std::mutex> lockGuard(this->mut);

        if (!this->data.empty()) {
            auto ret = std::make_shared<T>(this->data.front());
            this->data.pop_front();
            return ret;
        } else {
            return std::shared_ptr<T>();
        }
    }
};

template class CQueue<uint32_t>;
