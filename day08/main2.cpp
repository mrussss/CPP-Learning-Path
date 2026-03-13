#include <iostream>
#include <string>

// 1. 基准线：最普通的基类（2个 float）
class Entity
{
public:
    float X, Y;
    void Move(float xa, float ya)
    {
        X += xa;
        Y += ya;
    }
};

// 2. 对应第 27 集（继承）：只继承，没有虚函数
class Player : public Entity
{
public:
    const char *Name; // 额外加一个指针
    void PrintName() { std::cout << Name << std::endl; }
};

// 3. 对应第 28 集（虚函数）& 实验 C 核心：带虚函数的类
class VirtualEntity
{
public:
    float X, Y;
    virtual void Move(float xa, float ya)
    {
        X += xa;
        Y += ya;
    }
};

// 4. 对应第 29 集（接口）：纯虚函数
class IPrintable
{
public:
    virtual std::string GetClassName() = 0; // 纯虚函数
};

int main()
{
    std::cout << "=== 实验 C：多态与继承的物理代价 ===" << std::endl;

    std::cout << "1. 普通类 Entity 的大小: " << sizeof(Entity) << " 字节 (预期: 8 = 4+4)" << std::endl;

    std::cout << "2. 继承类 Player 的大小: " << sizeof(Player) << " 字节 (预期: 16 = Entity的8 + 指针的8)" << std::endl;

    std::cout << "3. 带虚函数 VirtualEntity 的大小: " << sizeof(VirtualEntity) << " 字节 (预期: 16 = 数据8 + vptr指针8)" << std::endl;

    std::cout << "4. 纯接口 IPrintable 的大小: " << sizeof(IPrintable) << " 字节 (预期: 8 = 仅有vptr指针)" << std::endl;

    return 0;
}