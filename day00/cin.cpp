#include <iostream>
#include <vector>

int main()
{
    std::cout << "--- Environment Check: START ---" << std::endl;

    std::vector<int> data = {10, 20, 30};
    int index;

    std::cout << "请输入你想查询的下标 (0, 1, 2): ";

    // 1. 获取用户输入
    std::cin >> index;

    // 2. 增加一个简单的安全检查（防止越界导致 UB）
    if (index >= 0 && index < data.size())
    {
        std::cout << "Index " << index << " 的值是: " << data[index] << std::endl;
    }
    else
    {
        std::cerr << "错误：输入的下标越界了！" << std::endl;
    }

    std::cout << "--- Environment Check: END ---" << std::endl;
    return 0;
}