//
// Created by Paratthakorn Sribunyong on 18/11/2019 AD.
//

#ifndef GUJARUNSFML_DEAD_H
#define GUJARUNSFML_DEAD_H
#include "../Precom.h"
#include "../GUI.h"
class DeadMenu
{
public:
    DeadMenu(sf::VideoMode& vm, sf::Font& font);
    virtual ~DeadMenu();

public:
    const bool isButtonPressed(const std::string key);
    void update(const sf::Vector2i& mousePosWindow);
    void render(sf::RenderTarget& target);
    void addButton(const std::string key, const float y,  const float width, const float height, const unsigned char_size, const std::string text);
    void getMessage(const std::string score);

    //Accessor
    std::map<std::string, gui::Button*>& getButtons();


    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);

private:
    sf::Font& font;
    sf::Text deadText;
    sf::RectangleShape background;
    sf::RectangleShape container;
    sf::Text scoreText;
    sf::Text scoreText2;
    std::string scoreString;


    std::map<std::string, gui::Button*> buttons;


    const sf::VideoMode& vm;


};
#endif //GUJARUNSFML_DEAD_H
