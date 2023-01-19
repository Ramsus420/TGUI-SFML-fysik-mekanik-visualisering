#pragma once
#include "Body.h"
#include<iostream>
#include <TGUI/TGUI.hpp>
class Kaströrelse
{
public:

    float Gravity; 
    int Y;
    int X;
    Body* grej;
    sf::RectangleShape Ground;
    bool moved = false;
    sf::CircleShape* kastshape;
    sf::Texture texture1;
    sf::Texture texture2;

    //constructor
    Kaströrelse(float vx, float vy, int x, int y, float g, sf::Color color)
    {
        Gravity = g;
        grej = new Body(x, y, vx, vy * -1, 1, 15, color);
        X = x;
        Y = y;
        Ground.setSize(sf::Vector2f(1280, 100));
        Ground.setPosition(0, 620);
        Ground.setFillColor(sf::Color::White);
        texture2.loadFromFile("mark.png");
        Ground.setTexture(&texture2);

        //hämtar och sätter texturen på objektet
        texture1.loadFromFile("ballz.png");
        kastshape = dynamic_cast<sf::CircleShape*>(grej->body);
        kastshape->setTexture(&texture1);
        kastshape->setOutlineThickness(1);
        kastshape->setOutlineColor(sf::Color::Red);
    };


    //applicerar gravitation på objektet
    void gravity()
    {
        kastshape = dynamic_cast<sf::CircleShape*>(grej->body);

       //kollar om objektet har flyttat från sin initiella position 
       if (kastshape->getPosition().y != Y or kastshape->getPosition().x != X)
        {
            moved = true;
        }
       
       // kollar om objektet nuddar marken och rört på sig
        if (kastshape->getGlobalBounds().intersects(Ground.getGlobalBounds()) and moved == true)
        {
            grej->velocity.y = 0;
            grej->velocity.x = 0;
        }

        else
        {
            grej->applyForce(sf::Vector2f(0, Gravity));
        }

        grej->update();
    };
};