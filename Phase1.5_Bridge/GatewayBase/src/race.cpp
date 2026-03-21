#include <iostream>
#include <thread>
#include <vector>

int cout_num = 0;
void add()
{
    for (int i = 0; i < 10000; i++)
    {
        cout_num++;
    }
}
int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++)
    {
        threads.emplace_back(add);
    }

    for (auto &T : threads)
    {
        T.join();
    }
    std::cout << cout_num << std::endl;
}