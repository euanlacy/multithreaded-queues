#include <atomic>
#include <cstdint>
#include <deque>
#include <mutex>
#include <memory>

class CQueue {
private:
    std::mutex mut;
    std::deque<uint32_t> data;
public:
    void enqueue(uint32_t payload) {
        std::lock_guard<std::mutex> lockGuard(this->mut);
        this->data.push_back(payload);
    }

    uint32_t dequeue() {
        std::lock_guard<std::mutex> lockGuard(this->mut);

        if (!this->data.empty()) {
            std::shared_ptr<uint32_t> ret;
            auto front = this->data.front();
            this->data.pop_front();
            return front;
        } else {
            return 0;
        }
    }
};
