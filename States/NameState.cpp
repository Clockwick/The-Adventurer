#include "NameState.h"


NameState::NameState(StateData *state_data, sf::Event* event)
        : State(state_data)
{
    this->event = event;
    this->initVariables();
    this->initBox();
}
//NameState::NameState()
//: State(state_data)
//{
//
//}
NameState::~NameState() {

}

void NameState::initBox() {

    if (!this->font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf"))
        std::cout << "Can't Load Font" << "\n";




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

    this->inputText.setFont(this->font);
    this->inputText.setCharacterSize(48.f);
    this->inputText.setFillColor(sf::Color(50,50,50));
    this->inputText.setPosition(this->cursorText.getPosition().x + 5, this->cursorText.getPosition().y);

}

void NameState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        this->saveToFile("kit.txt");
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
    if (this->totalTime >= this->blinkq)
    {
        this->totalTime = 0.f;
        this->blink = !this->blink;
        this->clock.restart();
    }

    if (event->type == sf::Event::EventType::TextEntered)
    {
        if (this->last_char != event->text.unicode && ((event->text.unicode >= 'a' && event->text.unicode <= 'z') ||
                                                       (event->text.unicode >= 'A' && event->text.unicode <= 'Z') ||
                                                       (event->text.unicode >= '0' && event->text.unicode <= '9')))
        {
            this->last_char = event->text.unicode;
            this->input += event->text.unicode;
            this->inputText.setString(this->input);
            this->cursorText.setPosition(950.f + this->inputText.getGlobalBounds().width + 5.f, this->cursorText.getPosition().y);
        }
        if (this->last_char != event->text.unicode && event->text.unicode == 8 && this->input.length() > 0)
        {
            this->last_char = event->text.unicode;
            this->input.erase(this->input.length() - 1);
            inputText.setString(this->input);
            this->cursorText.setPosition(950.0f + this->inputText.getGlobalBounds().width + 5, this->cursorText.getPosition().y);
        }
    }
    if (event->type == sf::Event::EventType::KeyReleased && this->last_char != ' ')
    {
        this->last_char = ' ';
    }

//    std::cout << "NameState: " << this->event << "\n";


}

void NameState::saveToFile(const std::string file_name) {
    std::ofstream ofs;
    ofs.open(file_name);
    if (ofs.is_open())
    {
        ofs << this->input << " ";
    }
    ofs.close();

}
