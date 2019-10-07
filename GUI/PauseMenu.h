//
// Created by Paratthakorn Sribunyong on 6/10/2019 AD.
//
#include "../Button.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#ifndef GUJARUNSFML_PAUSEMENU_H
#define GUJARUNSFML_PAUSEMENU_H

class PauseMenu
{
public:
    PauseMenu(sf::RenderWindow& window, sf::Font& font);
    virtual ~PauseMenu();

public:
    const bool isButtonPressed(const std::string key);
    void update(const sf::Vector2f& mousePos);
    void render(sf::RenderTarget& target);
    void addButton(const std::string key, float y, const std::string text);

    //Accessor
    std::map<std::string, Button*>& getButtons();




private:
    sf::Font& font;
    sf::Text menuText;
    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, Button*> buttons;




};
#endif //GUJARUNSFML_PAUSEMENU_H
