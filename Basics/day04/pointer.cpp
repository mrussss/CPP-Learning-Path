#include <iostream>
using namespace std;

__attribute__((noinline)) int *getAddrOfLocal()
{
    int x = 123;
    cout << "x address = " << (void *)&x << ", x value = " << x << endl;
    return &x; // ❌ UB：返回局部变量地址
}

int main()
{
    int *p = getAddrOfLocal();
    cout << "p = " << (void *)p << endl;

    // 故意读它，让 sanitizer 抓
    cout << "*p = " << *p << endl;

    return 0;
}
