#include <iostream>

int main()
{
    std::cout << "Size of char: " << sizeof(char) << " bytes" << std::endl;
    std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "Size of long: " << sizeof(long) << " bytes" << std::endl; // 重点看这一行
    std::cout << "Size of long long: " << sizeof(long long) << " bytes" << std::endl;
    std::cout << "Size of pointer: " << sizeof(void *) << " bytes" << std::endl;

    return 0;
}
