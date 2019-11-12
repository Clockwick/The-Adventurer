//
// Created by Paratthakorn Sribunyong on 31/8/2019 AD.
//

#include "Game.h"


Game::Game()
{
    //Priority Initialization !!!!!!
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initStateData();
    this->initstates();


}


Game::~Game()
{
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();

    }

}
//Functions
void Game::update() {
    this->updateSFMLEvent();

    if (!this->states.empty()) {
    {
        if (this->window->hasFocus()) {
            this->states.top()->update(this->deltaTime);

            if (this->states.top()->getQuit()) {
                this->states.top()->endState();
                delete this->states.top();
                this->states.pop();

            }
        }
    }
    }

    else
    {
        this->window->close();
        this->endApps();
    }



}

void Game::render() {
    this->window->clear();

    //Render
    if (!this->states.empty())
    {
        this->states.top()->render();
    }


    this->window->display();
}

void Game::updateDt() {
    this->deltaTime = this->dtClock.restart().asSeconds();

}

void Game::updateSFMLEvent() {
    while (this->window->pollEvent(event)) {
        if (event.type == event.Closed)
            this->window->close();

    }
}

void Game::run() {
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();

    }



}

void Game::initWindow() {

    if (this->gfxSettings.fullscreen)
    {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution,
                                            this->gfxSettings.title,
                                            sf::Style::Fullscreen,
                                            this->gfxSettings.contextSettings);

    }
    else
    {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution,
                this->gfxSettings.title,
                sf::Style::Titlebar | sf::Style::Close,
                this->gfxSettings.contextSettings);

    }
    this->window->setFramerateLimit(this->gfxSettings.framerateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.vsync);



}

void Game::initstates() {
    this->states.push(new Mainmenu(&this->state_data));

}

void Game::endApps() {
    std::cout << "GoodBye :D" << std::endl;

}

void Game::initVariables() {

    this->window = NULL;
    this->deltaTime = 0.f;
    this->gridSize = 90.f;

}

void Game::initGraphicsSettings() {
    this->gfxSettings.loadFromFile("config/graphics.ini");

}

void Game::initStateData() {
    this->state_data.window = this->window;
    this->state_data.gfxSettings = &this->gfxSettings;
    this->state_data.states = &this->states;
    this->state_data.gridSize = this->gridSize;
}


