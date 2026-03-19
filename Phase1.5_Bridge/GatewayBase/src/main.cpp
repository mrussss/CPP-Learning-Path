#include "BlockQueue.hpp"
#include <iostream>

int main()
{
    BlockQueue<int> bq;
    bq.push(100);
    std::cout << "BloclQueue 骨架编译通过。push成功！" << std::endl;
    return 0;
}