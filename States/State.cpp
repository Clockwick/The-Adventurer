//
// Created by Paratthakorn Sribunyong on 31/8/2019 AD.
//
#include "State.h"



State::State(sf::RenderWindow* window, std::stack <State*>* states)

{
    this->window = window;
    this->quit = false;
    this->states = states;
}

State::~State() {

}


const bool &State::getQuit() const {
    return this->quit;
}

void State::updateMousePos() {

    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

}

void State::endState() {
    this->quit = true;

}

void State::pauseState()
{
    this->paused = true;
}

void State::unpauseState()
{
    this->paused = false;
}


