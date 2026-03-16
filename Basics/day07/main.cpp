#include <iostream>
#include <string>
#include <stdexcept>

class Entity
{
private:
    std::string m_Name;

public:
    Entity(const std::string &name) : m_Name(name)
    {
        std::cout << "  -> 堆内存: Entity [" << m_Name << "] 被 new 出来了！" << std::endl;
    }
    ~Entity()
    {
        std::cout << "  -> 堆内存: Entity [" << m_Name << "] 被 delete 销毁了！" << std::endl;
    }
    const std::string &GetName() const { return m_Name; }
};

class ScopedEntity
{
private:
    Entity *m_Ptr;

public:
    ScopedEntity(Entity *ptr) : m_Ptr(ptr)
    {
        std::cout << "[管家] ScopedEntity 已接管指针！" << std::endl;
    }

    ~ScopedEntity()
    {
        std::cout << "[管家] 马上要出大括号了，管家临死前帮你全自动 delete！" << std::endl;
        delete m_Ptr;
    }

    Entity *Get() { return m_Ptr; }
};

int main()
{
    std::cout << "--- 极限施压实验开始 ---" << std::endl;

    try
    {
        // 在局部作用域（try块）里创建管家和堆内存
        ScopedEntity e(new Entity("Cherno"));

        std::cout << "业务逻辑正在运行，访问名字：" << e.Get()->GetName() << std::endl;

        // 💥 模拟突发灾难：网络断开、读取失败等，强制抛出异常打断程序！
        std::cout << "🔥 突然发生严重错误！准备抛出异常打断程序..." << std::endl;
        throw std::runtime_error("致命错误：网络连接突然断开！");

        // 注意：因为上面抛出了异常，程序直接“跳车”了，下面这行代码永远不可能被执行到！
        std::cout << "❌ 如果你看到这一行，说明 C++ 坏掉了" << std::endl;

    } // <--- 见证奇迹的时刻：虽然程序被打断了，但离开这个大括号时，C++ 的“栈展开”机制依然会强行触发 e 的析构函数！
    catch (const std::exception &ex)
    {
        // 捕获到了异常，程序没有直接死掉
        std::cout << "🚨 外层捕获到异常: " << ex.what() << std::endl;
    }

    std::cout << "--- 程序从异常中存活，安全结束 ---" << std::endl;
    return 0;
}