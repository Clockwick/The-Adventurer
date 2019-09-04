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

class Button
{
public:
    Button(float x, float y, float width, float height, sf::Font* font,std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    ~Button();

    //Functions
    void render(sf::RenderTarget *target);
    void update(const sf::Vector2f mousePos);

private:
    sf::RectangleShape shape;
    sf::Font *font;
    sf::Text text;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;



};
#endif //GUJARUNSFML_BUTTON_H
