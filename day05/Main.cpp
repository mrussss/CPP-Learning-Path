#include <iostream>
class Player

{
private:
    int x = 0;
    int y = 0;
    int speed = 1;

public:
    void Move(int xa, int ya)
    {
        x += xa * speed;
        y += ya * speed;
    }
};
int main()
{
    Player p1;
    p1.Move(-1, -1);
    std::cout << "移动成功！" << std::endl;
    return 0;
}