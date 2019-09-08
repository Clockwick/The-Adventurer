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
    Button(float x, float y, float width, float height, sf::Font* font,std::string text,unsigned character_size,
           sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
           sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
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

    sf::Color textIdleColor;
    sf::Color textHoverColor;
    sf::Color textActiveColor;



};
#endif //GUJARUNSFML_BUTTON_H
