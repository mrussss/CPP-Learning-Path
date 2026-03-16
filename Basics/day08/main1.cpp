#include <iostream>
class EmptyClass
{
};

class NormalClass
{

public:
    void DoSomething() {}
};
class NormalClass1
{
private:
    int num;

public:
    void DoSomething() {}
};

class VirtualClass
{

public:
    virtual void DoSomething() {}
};
class VirtualClass1
{
private:
    int num;

public:
    virtual void DoSomething() {}
};
int main()
{
    std::cout << "=== C++ 虚函数内存代价实验 ===" << std::endl;
    std::cout << "Size of EmptyClass:   " << sizeof(EmptyClass) << " bytes\n";
    std::cout << "Size of NormalClass:  " << sizeof(NormalClass) << " bytes\n";
    std::cout << "Size of NormalClass1:  " << sizeof(NormalClass1) << " bytes\n";
    std::cout << "Size of VirtualClass: " << sizeof(VirtualClass) << " bytes\n";
    std::cout << "Size of VirtualClass1: " << sizeof(VirtualClass1) << " bytes\n";
    return 0;
}
