#pragma once
#include<iostream>
#include<string>
#include <TGUI/TGUI.hpp>
class Body
{
public:
    sf::Vector2f velocity; //hastighet
    sf::Vector2f acceleration; //acceleration
    float mass; //masssa
    int RADIUS; //storleken på objektet
    sf::Color Color;
    sf::CircleShape shape;
    sf::CircleShape* body;

    //constructor
    Body(float x, float y, float vx, float vy, float m, int radius, sf::Color color) {
        velocity = sf::Vector2f(vx, vy);
        Color = color;
        mass = m;
        RADIUS = radius;
        shape = sf::CircleShape(RADIUS);
        shape.setPosition(x, y);
        body = &shape;
    }

    //beräknar accelerationen utifrån kraften och massan på objektet
    void applyForce(sf::Vector2f force) {
        acceleration += force / mass;
    }

    //beräknar hastigheten
    void update() {
        velocity += acceleration;
        acceleration = sf::Vector2f(0, 0);
        body = &shape;
    }

    //applicerar hastigheten och ritar på objektet
    void draw(sf::RenderWindow& window) {
        shape.setFillColor(Color);
        shape.setOrigin(RADIUS / 2, RADIUS / 2);
        shape.move(velocity);
        window.draw(*body);
    }
};