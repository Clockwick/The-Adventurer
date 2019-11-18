//
// Created by Paratthakorn Sribunyong on 18/11/2019 AD.
//

#include "Dead.h"

const bool DeadMenu::isButtonPressed(const std::string key) {
    return this->buttons[key]->isPressed();
}

void DeadMenu::update(const sf::Vector2i &mousePosWindow) {
    for (auto &i : this->buttons)
    {
        i.second->update(mousePosWindow);
    }
}

void DeadMenu::render(sf::RenderTarget &target) {
    target.draw(this->background);
    target.draw(this->container);

    for (auto &i : this->buttons)
    {
        i.second->render(target);
    }

    target.draw(this->deadText);
}

void DeadMenu::addButton(const std::string key, const float y, const float width, const float height,
                         const unsigned char_size, const std::string text) {

    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
    this->buttons[key] = new gui::Button(x,y,width,height,
                                         &this->font, text, char_size,
                                         sf::Color(255,255,255,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                         sf::Color(70,70,70,50),sf::Color(150,150,150,50),sf::Color(20,20,20,50)
    );
}

std::map<std::string, gui::Button *> &DeadMenu::getButtons() {
    return this->buttons;
}

DeadMenu::DeadMenu(sf::VideoMode &vm, sf::Font &font) : font(font){
    //Init Background
    this->background.setSize(
            sf::Vector2f(static_cast<float>(vm.width),
                         static_cast<float>(vm.height)
            )
    );
    this->background.setFillColor(sf::Color(255, 51, 51, 150));

    //Init Container
    this->container.setSize(sf::Vector2f(static_cast<float>(vm.width)/4.f,
                                         static_cast<float>(vm.height) - gui::p2pY(58.f, vm)
                            )
    );
    this->container.setFillColor(sf::Color(255, 51, 51, 200));
    this->container.setPosition(static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f, gui::p2pY(32.f,vm));

    //Text
    this->deadText.setFont(font);
    this->deadText.setFillColor(sf::Color(255,255,255,200));
    this->deadText.setCharacterSize(gui::calcCharSize(vm, 100));
    this->deadText.setString("You're already dead");
    this->deadText.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->deadText.getGlobalBounds().width/2.f, this->container.getPosition().y + gui::p2pY(10.f, vm));

}

DeadMenu::~DeadMenu() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end();++it){
        delete it->second;

    }
}
