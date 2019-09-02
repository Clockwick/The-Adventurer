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

    this->player.update(dt);


}

void GameState::render(sf::RenderTarget *target) {

    this->player.render(this->window);
}


void GameState::updateKeybinds(const float &dt) {
    this->checkForQuit();


}

void GameState::endState() {
   //Working!!



}



