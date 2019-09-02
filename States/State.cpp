//
// Created by Paratthakorn Sribunyong on 31/8/2019 AD.
//
#include "State.h"



State::State(sf::RenderWindow* window)

{
    this->window = window;
    this->quit = false;
}

State::~State() {

}

void State::render(sf::RenderTarget* target)
{



}

void State::update(const float& dt)
{



}

void State::endState()
{


}

void State::checkForQuit(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->quit = true;
    }

}

const bool &State::getQuit() const {
    return this->quit;
}


