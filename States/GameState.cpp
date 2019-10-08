//
// Created by Paratthakorn Sribunyong on 1/9/2019 AD.
//

#include "GameState.h"


GameState::GameState(sf::RenderWindow* window, std::stack <State*>* states)
: State(window, states)
{
    this->initTextures();
    this->initPlayers();
    this->initFonts();
    this->initPauseMenu();

}

GameState::~GameState() {
    delete this->player;
    delete this->pmenu;
}

void GameState::update(const float &dt) {

    this->updateMousePos();
    this->updateKeytime(dt);
    this->updateInput(dt);
    if (!this->paused)//Unpaused
    {
        this->updatePlayerInput(dt);
        this->player->update(dt);


    }
    else //Paused
    {

        this->pmenu->update(this->mousePosView);
        this->updatePauseMenuButtons();

    }

}

void GameState::render(sf::RenderTarget *target) {

    if(!target)
    {
        target = this->window;
    }

    this->map.render(*target);

    this->player->render(*target);
    if (this->paused)
    {
        //Pause Menu Render
        this->pmenu->render(*target);

    }



}


void GameState::updatePlayerInput(const float &dt) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->player->move(-1.0f, 0.0f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->player->move(1.0f, 0.0f, dt);
    }






}

void GameState::initTextures() {

    if (!this->textures["PLAYER_SHEET"].loadFromFile("resources/images/Assets/Player/Adventurer/adventurer-Sheet.png"))
    {
        std::cout << "Cannot Load Player Image" << std::endl;
    }
    std::cout << "Welcome to the Game!!" << std::endl;



}
void GameState::initFonts() {
    if (!this->font.loadFromFile("fonts/RobotoCondensed-Regular.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }

    std::cout << "Successfully Loaded Fonts" << std::endl;


}

void GameState::initPlayers() {
    this->player = new Player(500,500, this->textures["PLAYER_SHEET"]);

}

void GameState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->getKeyTime())
    {

        if(!this->paused)
            this->pauseState();
        else
            this->unpauseState();
    }

}

void GameState::initPauseMenu() {
    this->pmenu = new PauseMenu(*this->window, this->font);

    this->pmenu->addButton("QUIT",1100.f, "Quit");

}

void GameState::updatePauseMenuButtons() {
    if (this->pmenu->isButtonPressed(("QUIT")) && this->getKeyTime())
        this->endState();

}




