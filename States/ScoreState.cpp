//
// Created by Paratthakorn Sribunyong on 23/11/2019 AD.
//

#include "ScoreState.h"

ScoreState::ScoreState(StateData *state_data) : State(state_data) {

}

ScoreState::~ScoreState() {

}

void ScoreState::update(const float &dt) {
    updateInput(dt);

}

void ScoreState::render(sf::RenderTarget *target) {

}

void ScoreState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->endState();

}

void ScoreState::loadFromFile(const std::string file_name) {


}

void ScoreState::initVariables() {


}
