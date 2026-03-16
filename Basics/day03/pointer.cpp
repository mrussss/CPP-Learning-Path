#include <iostream>

int main()
{
    int var = 8;
    std::cout << "var的值:" << var << std::endl;
    std::cout << "var的地址:" << &var << std::endl;
    void *ptr = nullptr;
    ptr = &var;
    int *p = &var;
    *p = 10;
    std::cout << "修改后var的值:" << var << std::endl;
    std::cin.get();
}