//
// Created by Paratthakorn Sribunyong on 6/10/2019 AD.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window)
{
    //Init Background
    this->background.setSize(
            sf::Vector2f(static_cast<float>(window.getSize().x),
                    static_cast<float>(window.getSize().y)
            )
            );
    this->background.setFillColor(sf::Color(20,20,20,100));

    //Init Container
    this->container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x),
            static_cast<float>(window.getSize().y)
            )
            );
    this->container.setFillColor(sf::Color(20,20,20,200));
    this->container.setPosition(static_cast<float>(window.getSize().x / 2.f - this->container.getSize().x / 2.f), 0.f);
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

}

