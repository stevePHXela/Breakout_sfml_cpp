#include "Puddle.h"

Puddle::Puddle(int WIN_WIDTH, int WIN_HIGHT)
    : size({100.f, 30.f})
{
    position = { (float)(WIN_WIDTH / 2), (float)(WIN_HIGHT - 50) };
    puddle.setSize(size);
    //puddle.setOrigin(size / 2.f);
}

void Puddle::draw(sf::RenderWindow& window)
{
    puddle.setFillColor(sf::Color::Green);
    puddle.setPosition(position.x, position.y);
    window.draw(puddle);
}

void Puddle::move(float dx, int WIN_WIDTH)
{
    position.x += dx;
    if (position.x < 0)
        position.x = 0 + 16;
    else if (position.x + size.x > WIN_WIDTH)
        position.x = WIN_WIDTH - (size.x + 16);
}

void Puddle::resetPostion(int WIN_WIDTH, int WIN_HIGHT)
{
    position.x = (float)((WIN_WIDTH / 2) - 50);
    position.y = (float)(WIN_HIGHT - 64);
}

sf::FloatRect Puddle::getBoundingBox()
{
    return sf::FloatRect(getXPosition(), getYPosition(), getWidth(), getHeight());
}

float Puddle::getXPosition() { return puddle.getPosition().x; }

float Puddle::getYPosition() { return puddle.getPosition().y; }

float Puddle::getWidth() { return puddle.getSize().x; }

float Puddle::getHeight() { return puddle.getSize().y; }