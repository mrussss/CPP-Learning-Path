#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockQueue
{
private:
    std::queue<T> data_queue;
    std::mutex mtx;
    std::condition_variable cv_;

public:
    void push(const T &item)
    {
        std::lock_guard<std::mutex> lock(mtx);

        data_queue.push(item);
        cv_.notify_one();
    }
};
