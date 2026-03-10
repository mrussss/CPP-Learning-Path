#include <iostream>
#include <vector>

int main()
{
    std::cout << "Environment Check: START" << std::endl;

    std::vector<int> data = {10, 20, 30};

    // ⚠️ 故意制造的 Bug：循环次数写多了
    // data 只有 3 个元素 (下标 0, 1, 2)
    // 这里试图访问下标 3，这是未定义行为 (UB)
    for (int i = 0; i <= 3; ++i)
    {
        std::cout << "Index " << i << " = " << data.at(i) << std::endl;
    }

    std::cout << "Environment Check: END" << std::endl;
    return 0;
}
