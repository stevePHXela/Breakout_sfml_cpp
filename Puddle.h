#pragma once

#include <SFML\Graphics.hpp>


class Puddle
{
public:
    Puddle(int WIN_WIDTH, int WIN_HIGHT);

    void draw(sf::RenderWindow& window);

    void move(float dx, int WIN_WIDTH);

    void resetPostion(int WIN_WIDTH, int WIN_HIGHT);

    sf::FloatRect getBoundingBox();

    float getXPosition();

    float getYPosition();

    float getWidth();

    float getHeight();


private:
    sf::RectangleShape puddle;
    sf::Vector2f size;
    sf::Vector2f position;
};
