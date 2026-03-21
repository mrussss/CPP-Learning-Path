#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

int main()
{
    std::mutex mtx;
    {
        mtx.lock();
        mtx.lock();
        std::cout << "成功执行了！" << std::endl;
        mtx.unlock();
    }
    std::cout << "函数正常！" << std::endl;
}