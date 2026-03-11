#include <iostream>
#include <string>

class Entity
{
private:
    std::string m_Name;

public:
    Entity() : m_Name("Unknow") {}
    Entity(const std::string &name) : m_Name(name) {}
    const std::string &GetName() const { return m_Name; }
};

int main()
{
    Entity *e;
    {
        Entity entity("Chetno");
        e = &entity;
        std::cout << "大括号内部访问" << entity.GetName() << std::endl;
    }

    std::cout << "大括号外部访问（野指针）" << e->GetName() << std::endl;
    return 0;
}