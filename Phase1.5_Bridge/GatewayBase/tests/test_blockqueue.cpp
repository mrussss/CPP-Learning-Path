#include <thread>
#include <iostream>
#include <chrono>
#include "BlockQueue.hpp"

BlockQueue<int> queue;

void Producer()
{
    for (int i = 0; i < 10; i++)
    {
        queue.push(i);
        std::cout << "Producer生产成功!" << std ::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Consumer()
{
    while (true)
    {
        int item;
        bool state = queue.pop(item);
        if (!state)
        {
            std::cout << "Consumer 收到退出信号，安全结束" << std ::endl;
            break;
        }
        std::cout << item << std ::endl;
    }
}
int main()
{
    std::thread T1(Producer);
    std::thread T2(Consumer);
    T1.join();
    // queue.stop();
    T2.join();
}