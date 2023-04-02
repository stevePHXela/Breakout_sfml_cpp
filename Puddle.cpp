#include <SFML\Graphics.hpp>
#include "Puddle.h"

Puddle::Puddle(int WIN_WIDTH, int WIN_HIGHT)
    : width(100.0f), hight(30.0f)
{
    x_pos = (WIN_WIDTH / 2) - 50.f;
    y_pos = WIN_HIGHT / 1.1f;
    puddle.setSize(sf::Vector2f(width, hight));
}

void Puddle::draw(sf::RenderWindow& window)
{
    puddle.setFillColor(sf::Color::Green);
    puddle.setPosition(x_pos, y_pos);
    window.draw(puddle);
}

void Puddle::move(float dx, int WIN_WIDTH)
{
    x_pos += dx;
    if (x_pos < 0)
        x_pos = 0 + 16;
    else if (x_pos + width > WIN_WIDTH)
        x_pos = WIN_WIDTH - (width + 16);
}

void Puddle::resetPostion(int WIN_WIDTH, int WIN_HIGHT)
{
    x_pos = (WIN_WIDTH / 2) - 50.f;
    y_pos = WIN_HIGHT / 1.1f;
}