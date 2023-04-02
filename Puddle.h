#pragma

#include <SFML\Graphics.hpp>

class Puddle
{
public:
    Puddle(int WIN_WIDTH, int WIN_HIGHT);

    void draw(sf::RenderWindow& window);

    void move(float dx, int WIN_WIDTH);

    void resetPostion(int WIN_WIDTH, int WIN_HIGHT);

private:
    sf::RectangleShape puddle;
    float width;
    float hight;
    float x_pos;
    float y_pos;
};