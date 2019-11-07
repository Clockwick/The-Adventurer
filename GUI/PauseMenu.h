//
// Created by Paratthakorn Sribunyong on 6/10/2019 AD.
//
#include "../GUI.h"

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
    PauseMenu(sf::VideoMode& vm, sf::Font& font);
    virtual ~PauseMenu();

public:
    const bool isButtonPressed(const std::string key);
    void update(const sf::Vector2i& mousePosWindow);
    void render(sf::RenderTarget& target);
    void addButton(const std::string key, const float y,  const float width, const float height, const unsigned char_size, const std::string text);

    //Accessor
    std::map<std::string, gui::Button*>& getButtons();




private:
    sf::Font& font;
    sf::Text menuText;
    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, gui::Button*> buttons;




};
#endif //GUJARUNSFML_PAUSEMENU_H
