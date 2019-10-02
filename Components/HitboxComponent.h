//
// Created by Paratthakorn Sribunyong on 2/10/2019 AD.
//
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#ifndef GUJARUNSFML_HITBOXCOMPONENT_H
#define GUJARUNSFML_HITBOXCOMPONENT_H
class HitboxComponents
{
public:
    HitboxComponents(sf::Sprite& sprite,float offset_x, float offset_y, float width, float height);
    virtual ~HitboxComponents();
    //Functions
    bool checkIntersect(const sf::FloatRect& frect);
    void update();
    void render(sf::RenderTarget& target);


private:
    sf::Sprite& sprite;
    sf::RectangleShape hitbox;
    float offsetX;
    float offsetY;

};
#endif //GUJARUNSFML_HITBOXCOMPONENT_H
