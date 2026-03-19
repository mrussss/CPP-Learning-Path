#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

// 模板类T代表我要装入队列的数据类型。
template <typename T>
class BlockQueue
{
private:
    std::queue<T> queue_;
    std::mutex mtx_;
    std::condition_variable cv_;

    // bool is_stopped_ = false;
public:
    BlockQueue() = default;
    ~BlockQueue() = default;

    // TODO:实现push
    void push(const T &item)
    {
        std::lock_guard<std::mutex> lock(mtx_);

        queue_.push(item);

        cv_.notify_one();
    }
    // TODO:实现pop
    // TODO:实现stop
};