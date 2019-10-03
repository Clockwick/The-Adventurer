//
// Created by Paratthakorn Sribunyong on 1/9/2019 AD.
//

#include "GameState.h"


GameState::GameState(sf::RenderWindow* window, std::stack <State*>* states)
: State(window, states)
{
    this->initTextures();
    this->initPlayers();
}

GameState::~GameState() {
    delete this->player;
}

void GameState::update(const float &dt) {

    this->updateMousePos();
    this->updateInput(dt);
    this->player->update(dt);


}

void GameState::render(sf::RenderTarget *target) {

    if(!target)
    {
        target = this->window;
    }


    this->player->render(*target);
}


void GameState::updateInput(const float &dt) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->player->move(-1.0f, 0.0f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->player->move(1.0f, 0.0f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->player->move(0.0f, -1.0f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->quit = true;
    }




}

void GameState::initTextures() {
    this->textures["PLAYER_SHEET"].loadFromFile("resources/images/Assets/Player/Adventurer/adventurer-Sheet.png");

    if (!this->textures["PLAYER_SHEET"].loadFromFile("resources/images/Assets/Player/Adventurer/adventurer-Sheet.png"))
    {
        std::cout << "Cannot Load Player Image" << std::endl;
    }
    std::cout << "Welcome to the Game!!" << std::endl;



}

void GameState::initPlayers() {
    this->player = new Player(500,500, this->textures["PLAYER_SHEET"]);

}




