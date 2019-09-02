//
// Created by Paratthakorn Sribunyong on 1/9/2019 AD.
//

#include "GameState.h"


GameState::GameState(sf::RenderWindow* window)
: State(window)
{

}

GameState::~GameState() {

}

void GameState::update(const float &dt) {

    updateKeybinds(dt);


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        std::cout << "A" << std::endl;
}

void GameState::render(sf::RenderTarget *target) {

}


void GameState::updateKeybinds(const float &dt) {
    this->checkForQuit();


}

void GameState::endState() {
   //Working!!



}



