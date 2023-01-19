#pragma once
#include<iostream>
#include<string>
#include <TGUI/TGUI.hpp>
#include "Body.h"

class Omloppsbana
{
public:
    //variabler
    const float pi = 3.14159265358979323846; //pi
    const float G = 6.673e-11; //gravitationskonstanten
    const int WIDTH = 1280; //bredd f�nster
    const int HEIGHT = 720; //h�jd f�nster
    float r; //avst�ndet mellan objekten
    float vx; //hastigheten i x-led p� det kretsande objektet
    float vy; //hastigheten i y-led p� det kretsande objektet
    Body* body1; 
    Body* body2;
    sf::CircleShape* shape1; 
    sf::CircleShape* shape2;
    sf::Texture texture1;
    sf::Texture texture2;

    //constructor
    Omloppsbana(float m1, float m2, float R, float Vx, float Vy)
    {
        r = R;
        vx = Vx;
        vy = Vy;
        body1 = new Body((WIDTH / 2) - r, HEIGHT / 2, vx, vy, m1, 5, sf::Color::White);
        body2 = new Body(WIDTH / 2, HEIGHT / 2, 0, 0, m2, 50, sf::Color::White);

        //h�mtar och s�tter texturer p� objekten
        texture1.loadFromFile("Satelite-removebg-preview.png");
        shape1 = dynamic_cast<sf::CircleShape*>(body1->body);
        shape1->setTexture(&texture1);
        texture2.loadFromFile("Earth-removebg-preview.png");
        shape2 = dynamic_cast<sf::CircleShape*>(body2->body);
        shape2->setTexture(&texture2);
    }

    //uppdaterar och r�knar ut positioner och variabler
    void update()
    {
        shape1 = dynamic_cast<sf::CircleShape*>(body1->body);
        shape2 = dynamic_cast<sf::CircleShape*>(body2->body);
        r = std::hypot(shape1->getPosition().x - shape2->getPosition().x, shape1->getPosition().y - shape2->getPosition().y); //ber�knar avst�nd mellan objekt
        const float F = (G * body1->mass * body2->mass) / (r * r); //ber�knar kraften
        const float theta = std::atan2(shape2->getPosition().y - shape1->getPosition().y, shape2->getPosition().x - shape1->getPosition().x); //ber�knar kraftens riktning/vinkel
        body1->applyForce(sf::Vector2f(std::cos(theta) * F, std::sin(theta) * F));//applicerar kraften p� det kretsande objektet
        body1->update();
    }
};