//
// Created by Paratthakorn Sribunyong on 19/11/2019 AD.
//

#include "NameState.h"

NameState::NameState(StateData *state_data)
: State(state_data)
{
    this->quit = false;
    this->initBox();
}

NameState::~NameState() {

}

void NameState::initBox() {
    const sf::VideoMode& vm = this->state_data->gfxSettings->resolution;
    this->box.setSize(sf::Vector2f(1400.f, 600.f));
    this->box.setFillColor(sf::Color(50,50,50));
    this->box.setPosition(sf::Vector2f(gui::p2pX(20.f, vm),gui::p2pY(20.f,vm)));

    this->textIntro.setPosition(sf::Vector2f(this->box.getPosition().x + this->box.getGlobalBounds().width/3.f, this->box.getPosition().y + 20.f));
    this->textIntro.setFillColor(sf::Color::White);
    this->textIntro.setCharacterSize(48);
    this->textIntro.setString("Enter Player Name");

}

void NameState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        this->states->push(new GameState(this->state_data));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->quit = true;
        this->endState();
    }
//    std::cout << this->quit << "\n";
}

void NameState::update(const float &dt) {
    this->updateInput(dt);
}

void NameState::render(sf::RenderTarget *target) {
    target->draw(this->box);
    target->draw(this->textIntro);
}

bool* NameState::getQuit()
{
    return &this->quit;
}
