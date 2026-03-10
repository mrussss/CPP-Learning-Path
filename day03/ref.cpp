#include <iostream>
template <typename T>
void LOG(T arg)
{
    std::cout << arg << std::endl;
}
template <typename T, typename... Args>
void LOG(T first, Args... args)
{
    std::cout << first << " "; // 打印第一个，加个空格
    LOG(args...);              // 剩下的递归处理
}
// 指针传递
void IncrementPtr(int *value)
{
    (*value)++;
}

// 引用传递
void IncrementRef(int &value)
{
    value++;
}

int main()
{
    int a = 5;
    int &ref = a;
    LOG("a的地址是:", &a);
    LOG("ref的地址是:", ref);
    IncrementPtr(&a);
    LOG("a的值是", a);
    IncrementRef(a);
    LOG("a的值是", a);
}