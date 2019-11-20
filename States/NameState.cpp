//
// Created by Paratthakorn Sribunyong on 19/11/2019 AD.
//

#include "NameState.h"

NameState::NameState(StateData *state_data)
: State(state_data)
{
    this->initVariables();
    this->initBox();
}

NameState::~NameState() {

}

void NameState::initBox() {

    if (!this->font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf"))
        std::cout << "Can't Load Font" << "\n";


    this->inputText.setFont(this->font);
    this->inputText.setCharacterSize(36.f);
    this->inputText.setFillColor(sf::Color(50,50,50));
    this->inputText.setPosition(this->cursorText.getPosition().x + 5, this->cursorText.getPosition().y);

    this->bg.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
    this->bg.setFillColor(sf::Color(50,50,50,100));

    this->box.setSize(sf::Vector2f(1400.f, 600.f));
    this->box.setFillColor(sf::Color(50,50,50));
    this->box.setPosition(sf::Vector2f(gui::p2pX(25.f, vm),gui::p2pY(20.f,vm)));

    this->textIntro.setFont(this->font);
    this->textIntro.setPosition(sf::Vector2f(this->box.getPosition().x + this->box.getGlobalBounds().width/3.f + 50.f, this->box.getPosition().y + 20.f));
    this->textIntro.setFillColor(sf::Color::White);
    this->textIntro.setCharacterSize(48);
    this->textIntro.setString("Enter Player Name");

    this->inputBox.setSize(sf::Vector2f(1000.f, 100.f));
    this->inputBox.setFillColor(sf::Color::White);
    this->inputBox.setPosition(sf::Vector2f(this->box.getPosition().x + this->box.getGlobalBounds().width * 0.15f,
            this->box.getPosition().y + this->box.getGlobalBounds().height * 0.4));

    this->cursorText.setSize(sf::Vector2f(5.f, this->inputBox.getSize().y * 0.6));
    this->cursorText.setPosition(sf::Vector2f(this->inputBox.getPosition().x + 12.f, this->inputBox.getPosition().y + 15.f));
    this->cursorText.setFillColor(sf::Color::Black);


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
}

void NameState::update(const float &dt) {
    this->updateCursor();
    this->updateInput(dt);

}

void NameState::render(sf::RenderTarget *target) {
    target->draw(this->bg);
    target->draw(this->box);
    target->draw(this->textIntro);
    target->draw(this->inputBox);
    if (blink)
        target->draw(this->cursorText);
    target->draw(this->inputText);

}

const bool& NameState::getQuit()
{
    return this->quit;
}

void NameState::initVariables() {
    this->quit = false;
    this->totalTime = 0.f;
    this->blink = false;
    this->blinkq = 2.5f;
    this->last_char = ' ';

}

void NameState::updateCursor() {
    this->totalTime += this->clock.getElapsedTime().asSeconds();
    sf::Event event;
    if (this->totalTime >= this->blinkq)
    {
        this->totalTime = 0.f;
        this->blink = !this->blink;
        this->clock.restart();
    }

        if (event.type == sf::Event::EventType::TextEntered)
        {
            if (this->last_char != event.text.unicode)
            {
                this->last_char = event.text.unicode;
                this->input += event.text.unicode;
                std::cout << this->input << std::endl;
                this->inputText.setString(this->input);
            }
        }
        if (event.type == sf::Event::EventType::KeyReleased && this->last_char != ' ')
        {
            this->last_char = ' ';
        }




}
