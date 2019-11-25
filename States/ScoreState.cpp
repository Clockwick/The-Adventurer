//
// Created by Paratthakorn Sribunyong on 23/11/2019 AD.
//

#include "ScoreState.h"

ScoreState::ScoreState(StateData *state_data) : State(state_data) {
    this->initVariables();
    this->initGui();
}

ScoreState::~ScoreState() {

}

void ScoreState::update(const float &dt) {
    this->updateInput(dt);
    this->updateMousePos();

}

void ScoreState::render(sf::RenderTarget *target) {
    if(!target)
    {
        target = this->window;
    }
    target->draw(this->background);

}

void ScoreState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->endState();

}

void ScoreState::loadFromFile(const std::string file_name) {


}

void ScoreState::initVariables() {


}

void ScoreState::initGui() {
    if (!this->font.loadFromFile("fonts/karma.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }

    std::cout << "Successfully Loaded Fonts" << std::endl;

    const sf::VideoMode& vm = this->state_data->gfxSettings->resolution;

    //Background

    this->background.setSize(
            sf::Vector2f(
                    static_cast<float>(vm.width),
                    static_cast<float>(vm.height)
            )
    );

    if(!this->backgroundTexture.loadFromFile("resources/images/background/Testbackground.jpg"))
    {
        std::cout << "Failed to load BackgroundImage" << std::endl;


    }
    this->background.setTexture(&this->backgroundTexture);
    std::cout << "Successfully Loaded BackgroundImage" << std::endl;

}
