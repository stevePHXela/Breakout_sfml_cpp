#include <iostream>
#include <ctime>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "Puddle.h"

static const int WIN_WIDTH = 900;
static const int WIN_HIGHT = 600;
static const float speed = 240.f;
bool gameOver = false;
const enum Directions {stop, top, topRight, topLeft, bottom, bottomLeft, bottomRight};

class Ball
{
public:
    Ball(int WIN_WIDTH, int WIN_HIGHT)
        : size(12.f)
    {
        position.x = (float)((WIN_WIDTH / 2) - 16);
        position.y = (float)(WIN_HIGHT - 100);
        ball.setRadius(size);
        direction = stop;
    }

public:
    void draw(sf::RenderWindow& window)
    {
        ball.setFillColor(sf::Color::Red);
        ball.setPosition(position.x, position.y);
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
            position.y--;
            break;
        case topRight:
            position.y--;
            position.x++;
            break;
        case topLeft:
            position.y--;
            position.x--;
            break;
        case bottom:
            position.y++;
            break;
        case bottomLeft:
            position.y++;
            position.x--;
            break;
        case bottomRight:
            position.y++;
            position.x++;
            break;
        }
    }

    void checkForCollision(int WIN_WIDTH, int WIN_HIGHT)
    {
        if (position.y == WIN_HIGHT)
        {
            gameOver = true;
        }

        if (position.x - size <= 0 || position.x + size >= WIN_WIDTH)
        {
            if (direction == topRight)
            {
                direction = topLeft;
            }
            if (direction == topLeft)
            {
                direction = topRight;
            }
            if (direction == bottomRight)
            {
                direction = bottomLeft;
            }
            if (direction == bottomLeft)
            {
                direction = bottomRight;
            }
            
        }

        if (position.y - size >= 0)
        {
            if (direction == top)
            {
                direction = bottom;
            }
            if (direction == topRight)
            {
                direction = topLeft;
            }
            if (direction == topLeft)
            {
                direction = topRight;
            }
            if (direction == bottomRight)
            {
                direction = bottomLeft;
            }
            if (direction == bottomLeft)
            {
                direction = bottomRight;
            }
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
    sf::Vector2f position;
    float size;
};

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HIGHT), "Breakout Game", sf::Style::Close);

    window.setFramerateLimit(360);
    sf::Clock clock;
    float deltaTime;

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
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                {
                    window.close();
                }
            }
        }

        deltaTime = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            puddle.move(-3.f * deltaTime * speed, WIN_WIDTH);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            puddle.move(3.f * deltaTime * speed, WIN_WIDTH);
        }


        window.clear();
        puddle.draw(window);

        ball.draw(window);
        ball.move();
        ball.checkForCollision(WIN_WIDTH, WIN_HIGHT);

        window.display();
    }
    
    return 0;
}