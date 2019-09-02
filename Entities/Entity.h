//
// Created by Paratthakorn Sribunyong on 2/9/2019 AD.
//
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
#ifndef GUJARUNSFML_ENTITY_H
#define GUJARUNSFML_ENTITY_H


class Entity
{
public:
    Entity();
    virtual ~Entity();

    //Functions
 virtual void render(sf::RenderTarget* target);
 virtual void update(const float &dt);
 virtual void move(const float& dt, const float x, const float y);

protected:
    sf::RectangleShape shape;
    float movementSpeed;


private:

};

#endif //GUJARUNSFML_ENTITY_H
