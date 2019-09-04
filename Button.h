#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#ifndef GUJARUNSFML_BUTTON_H
#define GUJARUNSFML_BUTTON_H


enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};


class Button
{
public:
    Button(float x, float y, float width, float height, sf::Font* font,std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    ~Button();
    //Accessories
    const bool isPressed() const;

    //Functions
    void render(sf::RenderTarget *target);
    void update(const sf::Vector2f mousePos);

private:

    unsigned short buttonStates;
    bool pressed;
    bool hover;


    sf::RectangleShape shape;
    sf::Font *font;
    sf::Text text;


    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;



};
#endif //GUJARUNSFML_BUTTON_H
