#include <iostream>
#include "Logger.hpp"
#include <thread>
#include <vector>
#include <mutex>

int shared_counter = 0;
std::mutex mtx;
void bad_worker()
{
    LOG_INFO("I begin to make trouble!");
    for (int i = 0; i < 10000; ++i)
    {
        mtx.lock();
        mtx.lock(); // 致命红线：对同一把普通的互斥锁连续锁两次！
        shared_counter++;
        mtx.unlock();
    }
}
int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++)
    {
        threads.emplace_back(bad_worker);
    }
    for (auto &t : threads)
    {
        t.join();
    }
    LOG_INFO("最终的 counter 结果是: %d (预期是 100000)", shared_counter);
    return 0;
}