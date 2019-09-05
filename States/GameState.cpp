//
// Created by Paratthakorn Sribunyong on 1/9/2019 AD.
//

#include "GameState.h"


GameState::GameState(sf::RenderWindow* window, std::stack <State*>* states)
: State(window, states)
{

}

GameState::~GameState() {

}

void GameState::update(const float &dt) {

    this->updateMousePos();
    this->updateInput(dt);
    this->player.update(dt);


}

void GameState::render(sf::RenderTarget *target) {

    if(!target)
    {
        target = this->window;
    }


    this->player.render(target);
}


void GameState::updateInput(const float &dt) {
    this->checkForQuit();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->player.move(dt, -1.0f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->player.move(dt, 0.0f, 1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->player.move(dt, 1.0f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->player.move(dt, 0.0f, -1.0f);
    }


}

void GameState::endState() {
   //Working!!



}



