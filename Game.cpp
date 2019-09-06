//
// Created by Paratthakorn Sribunyong on 31/8/2019 AD.
//

#include "Game.h"


Game::Game()
{
    this->initWindow();
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
        this->states.top()->update(this->deltaTime); // ???


        if (this->states.top()->getQuit()) {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();

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
        this->states.top()->render(); // ???
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
    std::ifstream ifs;
    ifs.open("config/window.ini");
    /* IMPORT FROM "window.ini" FILE*/
    std::cout << "System Initialize..." << std::endl;
    this->videoModes = sf::VideoMode::getFullscreenModes();
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    std::string title = "None";
    unsigned int framerate_limited = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;



    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limited;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;

        std::cout << "Import file from config/window.ini" << std::endl;



    }

    ifs.close();
    this->fullscreen = fullscreen;
    this->window_settings.antialiasingLevel = antialiasing_level;
    if (this->fullscreen)
    {
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, window_settings);

    }
    else
    {
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, window_settings);

    }
    this->window->setFramerateLimit(framerate_limited);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);



}

void Game::initstates() {
    this->states.push(new Mainmenu(this->window, &this->states));

}

void Game::endApps() {
    std::cout << "Finish!!" << std::endl;

}

void Game::initVariables() {

    this->window = nullptr;
    this->fullscreen = false;
    this->deltaTime = 0.0f;

}
