
#include "mainmenuState.h"

Mainmenu::Mainmenu(sf::RenderWindow* window)
        : State(window)
{
    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Magenta);
}

Mainmenu::~Mainmenu() {

}

void Mainmenu::update(const float &dt) {

    this->updateInput(dt);



}

void Mainmenu::render(sf::RenderTarget *target) {

    if(!target)
    {
        target = this->window;
    }

    target->draw(this->background);
}


void Mainmenu::updateInput(const float &dt) {
    this->checkForQuit();



}

void Mainmenu::endState() {
    //Working!!



}