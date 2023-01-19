#pragma once
#include <math.h>
#include "Body.h"
class Stötar
{
public:
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;
    Body* ball1;
    Body* ball2;
    sf::CircleShape* shape1;
    sf::CircleShape* shape2;
    sf::RectangleShape Ground;
    sf::RectangleShape roof;

    Stötar(float m1, float m2, float vx1, float vy1, float vx2, float vy2)
    {
        ball1 = new Body(100, 360, vx1, vy1, m1, 20, sf::Color::White);
        ball2 = new Body(1180, 360, vx2, vy2, m2, 20, sf::Color::White);
        texture1.loadFromFile("ballz.png");
        shape1 = dynamic_cast<sf::CircleShape*>(ball1->body);
        shape1->setTexture(&texture1);
        texture2.loadFromFile("ballz.png");
        shape2 = dynamic_cast<sf::CircleShape*>(ball2->body);
        shape2->setTexture(&texture2);
        shape1->setOutlineThickness(2);
        shape2->setOutlineThickness(2);
        shape1->setOutlineColor(sf::Color::Red);        
        shape2->setOutlineColor(sf::Color::Blue);
        Ground.setSize(sf::Vector2f(1280, 100));
        Ground.setPosition(0, 620);
        Ground.setFillColor(sf::Color::White);
        texture3.loadFromFile("mark.png");
        Ground.setTexture(&texture3);
        roof.setSize(sf::Vector2f(1280, 100));
        roof.setPosition(0, -100);
    }

    void update()
    {
        shape1 = dynamic_cast<sf::CircleShape*>(ball1->body);
        shape2 = dynamic_cast<sf::CircleShape*>(ball2->body);
        // Update the balls' positions and velocities
        ball1->update();
        ball2->update();

        // Check if the balls have collided
        if (shape1->getGlobalBounds().intersects(shape2->getGlobalBounds()))
        {
            sf::Vector2f v1_after, v2_after;
            // Calculate the new velocities of the balls after the collision
            v1_after = (ball1->velocity * (ball1->mass - ball2->mass) + (2 * ball2->mass * ball2->velocity)) / (ball1->mass + ball2->mass);
            v2_after = (ball2->velocity * (ball2->mass - ball1->mass) + (2 * ball1->mass * ball1->velocity)) / (ball1->mass + ball2->mass);
            ball1->velocity = v1_after;
            ball2->velocity = v2_after;
        }

        // Check if the balls have hit the ground or cieling
        if (shape1->getGlobalBounds().intersects(Ground.getGlobalBounds()) or shape1->getGlobalBounds().intersects(roof.getGlobalBounds()))
        {
            // Reverse the ball's y-velocity to make it bounce
            ball1->velocity.y = -ball1->velocity.y;
        }

        if (shape2->getGlobalBounds().intersects(Ground.getGlobalBounds()) or shape2->getPosition().y + ball2->RADIUS <= 0)
        {
            // Reverse the ball's y-velocity to make it bounce
            ball2->velocity.y = -ball2->velocity.y;
        }

        // Check if the balls have hit the wall
        if (shape1->getPosition().x + ball1->RADIUS >= 1280 or shape1->getPosition().x + ball1->RADIUS <= 0)
        {
            // Reverse the ball's x-velocity to make it bounce
            ball1->velocity.x = -ball1->velocity.x;
        }

        if (shape2->getPosition().x + ball2->RADIUS >= 1280 or shape2->getPosition().x + ball2->RADIUS <= 0)
        {
            // Reverse the ball's x-velocity to make it bounce
            ball2->velocity.x = -ball2->velocity.x;
        }
    }
};