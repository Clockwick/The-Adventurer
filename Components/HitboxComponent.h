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
    bool intersects(const sf::FloatRect& frect);
    void update();
    void render(sf::RenderTarget& target);
    //Accessors
    const sf::Vector2f& getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);


    //Modifiers
    void setPosition(sf::Vector2f& position);
    void setPosition(const float x, const float y);

private:
    sf::Sprite& sprite;
    sf::RectangleShape hitbox;
    sf::FloatRect nextPosition;
    float offsetX;
    float offsetY;

};
#endif //GUJARUNSFML_HITBOXCOMPONENT_H
