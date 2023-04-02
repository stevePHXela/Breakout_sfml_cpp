#include <iostream>
#include <ctime>
#include <SFML\Graphics.hpp>
#include "Puddle.h"

static const int WIN_WIDTH = 900;
static const int WIN_HIGHT = 600;
const enum Directions {stop, top, topRight, topLeft, bottom, bottomLeft, bottomRight};

// Puddle can move right and left
    // - can't move out the width of the window.
    // - restart to the center after loses.
    // - A for left movement and D for right and Space to start.

// Ball
    // - In the start should go in random direction.
    // - Revers the obest diction when hit with Puddle or blocks
    // - When hit with a block, block remove and change direction.
    // - when the ball behind the Puddle game over.

// Blocks
    // three lines of blocks fill the width of the window.
    // when the ball in same position of a block, block remove.
    // when all blocks are removed, player win and game over.

class Ball
{
public:
    Ball(int WIN_WIDTH, int WIN_HIGHT)
        : size(16.f)
    {
        x_pos = (WIN_WIDTH / 2) - 16;
        y_pos = WIN_HIGHT - 100;
        ball.setRadius(size);
        direction = stop;
    }

public:
    void draw(sf::RenderWindow& window)
    {
        ball.setFillColor(sf::Color::Red);
        ball.setPosition(x_pos, y_pos);
        window.draw(ball);
    }

    void move()
    {
        switch (direction)
        {
        case stop:
            randomDirection();
            break;
        case top:
            y_pos--;
            break;
        case topRight:
            y_pos--;
            x_pos++;
            break;
        case topLeft:
            y_pos--;
            x_pos--;
            break;
        case bottom:
            y_pos++;
            break;
        case bottomLeft:
            y_pos++;
            x_pos--;
            break;
        case bottomRight:
            y_pos++;
            x_pos++;
            break;
        }
    }

private:
    void randomDirection()
    {
        direction = (Directions)(std::rand() & 7);
    }

private:
    sf::CircleShape ball;
    Directions direction;
    float size;
    float x_pos;
    float y_pos;
};

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HIGHT), "Breakout Game", sf::Style::Close);

    Puddle puddle(WIN_WIDTH, WIN_HIGHT);
    Ball ball(WIN_WIDTH, WIN_HIGHT);
        
    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            switch (e.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            puddle.move(-0.5f, WIN_WIDTH);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            puddle.move(0.5f, WIN_WIDTH);
        }


        window.clear();
        puddle.draw(window);
        ball.draw(window);
        ball.move();
        window.display();
    }
    
    return 0;
}