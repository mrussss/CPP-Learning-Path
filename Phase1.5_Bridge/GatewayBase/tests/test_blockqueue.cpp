#include <thread>
#include <vector>
#include "BlockQueue.hpp"
int main()
{
    BlockQueue<int> queue;
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; i++)
    {
        threads.emplace_back([&queue]()
                             {
                             for (int j = 0; j < 100000; j++)
                             {
                                queue.push(j);
                             } });
    }

    for (auto &t : threads)
    {
        t.join();
    }

    return 0;
}