#include <iostream>
#include <ctime>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "SimpleMath.h"
#include "Puddle.h"

using namespace DirectX::SimpleMath;

static const int WIN_WIDTH = 900;
static const int WIN_HIGHT = 600;
static const float speed = 240.f;
bool gameOver = false;

class Ball
{
public:
    Ball(int WIN_WIDTH, int WIN_HIGHT)
        : size(12.f), speed(280.f)
    {
        position = { (float)((WIN_WIDTH / 2) - 16), (float)(WIN_HIGHT - 100) };
        ball.setRadius(size);
        direction = {1.0, -1.0};
    }

public:
    void draw(sf::RenderWindow& window)
    {
        ball.setFillColor(sf::Color::Red);
        ball.setPosition(position.x, position.y);
        window.draw(ball);
    }

    void update(float dt)
    {
        position += direction * speed * dt;
    }

    void checkForCollision(Puddle& puddle, int WIN_WIDTH, int WIN_HIGHT)
    {
        float r = size;
        float w = (float)WIN_WIDTH;
        float h = (float)WIN_HIGHT;

        // Check for collision with left and right walls
        if (position.x - r <= 0.f || position.x + r >= w)
        {
            direction.x *= -1.f;
        }

        // Check for collision with top wall
        if (position.y - r <= 0.f)
        {
            direction.y *= -1.f;
        }

        // Check for collision with paddle
        if (position.x >= puddle.getXPosition() - 100.f && position.y >= puddle.getYPosition())
        {
            direction.y *= -1.f;
        }

        // Check for collision with bottom wall
        if (position.y + r >= h)
        {
            gameOver = true;
        }
    }

private:
    sf::CircleShape ball;
    Vector2 direction;
    Vector2 position;
    float speed;
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
        ball.update(deltaTime);
        ball.checkForCollision(puddle, WIN_WIDTH, WIN_HIGHT);

        window.display();
    }
    
    return 0;
}