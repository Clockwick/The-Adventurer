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
    PauseMenu(sf::RenderWindow& window);
    virtual ~PauseMenu();

public:
    void update();
    void render(sf::RenderTarget& target);



private:
    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, Button*> buttons;


};
#endif //GUJARUNSFML_PAUSEMENU_H
