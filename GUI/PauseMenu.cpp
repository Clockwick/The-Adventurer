//
// Created by Paratthakorn Sribunyong on 6/10/2019 AD.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window,sf::Font& font) : font(font)
{
    //Init Background
    this->background.setSize(
            sf::Vector2f(static_cast<float>(window.getSize().x),
                    static_cast<float>(window.getSize().y)
            )
            );
    this->background.setFillColor(sf::Color(20,20,20,100));

    //Init Container
    this->container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x/4.f),
            static_cast<float>(window.getSize().y - 60.f)
            )
            );
    this->container.setFillColor(sf::Color(100,20,20,200));
    this->container.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f, 30.f);

    //Text
    this->menuText.setFont(font);
    this->menuText.setFillColor(sf::Color(255,255,255,200));
    this->menuText.setCharacterSize(30);
    this->menuText.setString("PAUSE");
    this->menuText.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width, this->container.getPosition().y + 40.f);
}
PauseMenu::~PauseMenu()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end();++it){
        delete it->second;


    }

}

//Functions
void PauseMenu::update()
{

}

void PauseMenu::render(sf::RenderTarget &target)
{
    target.draw(this->background);
    target.draw(this->container);

    for (auto &i : this->buttons)
    {
        i.second->render(target);
    }

    target.draw(this->menuText);

}

