#include<iostream>
#include <TGUI/TGUI.hpp>
#include "Body.h"
#include "Kaströrelse.h"
#include "Omloppsbana.h"
#include "Stötar.h"

bool g;
bool tryckt = false;
bool RunGUI(tgui::GuiBase& gui);
sf::RenderWindow window{ {1280, 720}, "gg"};
tgui::GuiSFML gui{ window };
Omloppsbana* ob;
Kaströrelse* kr;
Stötar* st;

int simulation;

void simulate_omloppsbana()
{
    float m1 = tgui::String(gui.get<tgui::EditBox>("massa1")->getText()).toFloat();
    float m2 = tgui::String(gui.get<tgui::EditBox>("massa2")->getText()).toFloat();
    float r = tgui::String(gui.get<tgui::EditBox>("raide")->getText()).toFloat();
    float vx = tgui::String(gui.get<tgui::EditBox>("vx")->getText()).toFloat();
    float vy = tgui::String(gui.get<tgui::EditBox>("vy")->getText()).toFloat();
    delete ob;
    ob = new Omloppsbana(m1, m2, r, vx, vy);
    tryckt = true;
}

void simulate_kaströrelse() 
{
    float ypos = tgui::String(gui.get<tgui::EditBox>("ypos")->getText()).toFloat();
    float vx = tgui::String(gui.get<tgui::EditBox>("vx")->getText()).toFloat();
    float vy = tgui::String(gui.get<tgui::EditBox>("vy")->getText()).toFloat();
    delete kr;
    kr = new Kaströrelse(vx, vy, 0, ypos, 0.0075, sf::Color::White);
    tryckt = true;
}

void simulate_stötar()
{
    float m1 = tgui::String(gui.get<tgui::EditBox>("massa1")->getText()).toFloat();
    float m2 = tgui::String(gui.get<tgui::EditBox>("massa2")->getText()).toFloat();
    float vx1 = tgui::String(gui.get<tgui::EditBox>("vx1")->getText()).toFloat();
    float vy1 = tgui::String(gui.get<tgui::EditBox>("vy1")->getText()).toFloat();
    float vx2 = tgui::String(gui.get<tgui::EditBox>("vx2")->getText()).toFloat();
    float vy2 = tgui::String(gui.get<tgui::EditBox>("vy2")->getText()).toFloat();
    delete st;
    st = new Stötar(m1, m2, vx1, vy1, vx2, vy2);
    g = gui.get<tgui::CheckBox>("gtoggle")->isChecked();
    tryckt = true;
}

void guis(int gui_page)
{
    tryckt = false;
    simulation = gui_page;
    gui.removeAllWidgets();
    switch (gui_page) 
    {
    case 0:
        RunGUI(gui);
        break;

    case 1: {
        gui.loadWidgetsFromFile("omloppsbana.txt");
        auto back = gui.get<tgui::Button>("back");
        back->onPress(guis, 0);
        auto insert = gui.get<tgui::Button>("insert");
        insert->onPress(simulate_omloppsbana);
        break; };

    case 2: {
        gui.loadWidgetsFromFile("kastrorelse.txt");
        auto back = gui.get<tgui::Button>("back");
        back->onPress(guis, 0);
        auto insert = gui.get<tgui::Button>("insert");
        insert->onPress(simulate_kaströrelse);
        break; };

    case 3: {
        gui.loadWidgetsFromFile("kollision.txt");
        auto back = gui.get<tgui::Button>("back");
        back->onPress(guis, 0);
        auto insert = gui.get<tgui::Button>("insert");
        insert->onPress(simulate_stötar);
        break; };
    }
}

//For a easy debugging will show if a file counld not be opened in the console.
bool RunGUI(tgui::GuiBase& gui)
{
    try
    {
        gui.loadWidgetsFromFile("Huvudmeny.txt");
        auto omloppsbanastart = gui.get<tgui::Button>("omlopp");
        omloppsbanastart->onPress(guis, 1);
        auto kaströrelsestart = gui.get<tgui::Button>("kastrrelse");
        kaströrelsestart->onPress(guis, 2);
        auto stötarstart = gui.get<tgui::Button>("Sttar");
        stötarstart->onPress(guis, 3);
        return true;
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return false;
    }
}

//main entry
int main()
{
    window.setFramerateLimit(120);

    RunGUI(gui);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            gui.handleEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        
        if (tryckt == true) {
            switch (simulation)
            {
            case 1:
                ob->body1->draw(window);
                ob->body2->draw(window);
                ob->update();
                break;

            case 2:
                window.draw(kr->Ground);
                kr->grej->draw(window);
                kr->gravity();
                break;

            case 3:
                window.draw(st->Ground);
                st->ball1->draw(window);
                st->ball2->draw(window);
                st->update();
                if (g) { st->ball1->applyForce(sf::Vector2f(0, 0.25f*st->ball1->mass)); st->ball2->applyForce(sf::Vector2f(0, 0.25f*st->ball2->mass)); }
                break;
            }
        }
        gui.draw();
        window.display();
    }
}