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
    /* IMPORT FROM "window.ini" FILE*/
    std::cout << "System Initialize..." << std::endl;
    sf::VideoMode window_bounds(1440, 1080);
    std::ifstream ifs;
    ifs.open("config/window.ini");
    std::string title = "None";
    unsigned int framerate_limited = 120;
    bool vertical_sync_enabled = false;



    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limited;
        ifs >> vertical_sync_enabled;

        std::cout << "Import file from config/window.ini" << std::endl;



    }

    ifs.close();
    this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limited);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
    std::cout << "Ready!"<< std::endl;



}

void Game::initstates() {
    this->states.push(new Mainmenu(this->window));
    this->states.push(new GameState(this->window));
}

void Game::endApps() {
    std::cout << "Finish!!" << std::endl;

}
