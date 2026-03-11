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

        e = new Entity("Chetno");
        std::cout << "大括号内部访问" << e->GetName() << std::endl;
    }

    std::cout << "大括号外部访问（依旧存活）" << e->GetName() << std::endl;
    delete e;
    return 0;
}