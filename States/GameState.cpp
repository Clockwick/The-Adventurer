//
// Created by Paratthakorn Sribunyong on 1/9/2019 AD.
//

#include "GameState.h"


GameState::GameState(StateData* state_data)
: State(state_data)
{
    this->initDeferredRender();
    this->initView();
    this->initTextures();
    this->initPlayers();
    this->initFonts();
    this->initPauseMenu();
    this->initTileMap();

}

GameState::~GameState() {
    delete this->player;
    delete this->pmenu;
    delete this->tileMap;
}

void GameState::update(const float &dt) {

    this->updateMousePos(&this->view);
    this->updateKeytime(dt);
    this->updateInput(dt);
    std::cout << this->player->getVelocity().y << std::endl;

    if (!this->paused)//Unpaused
    {
        this->updateView(dt);
        this->updatePlayerInput(dt);
        this->updateTileMap(dt);
        this->player->update(dt);

    }
    else //Paused
    {

        this->pmenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();

    }

}

void GameState::render(sf::RenderTarget *target) {

    if(!target)
    {
        target = this->window;
    }
    this->renderTexture.clear();

    this->renderTexture.setView(this->view);
    this->tileMap->render(this->renderTexture, this->player->getGridPosition(static_cast<int>(this->state_data->gridSize)));
    this->player->render(this->renderTexture);
    if (this->paused)//Pause Menu Render
    {
        this->renderTexture.setView(this->renderTexture.getDefaultView());
        this->pmenu->render(renderTexture);
    }
    //Final Render
    this->renderTexture.display();
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(this->renderSprite);


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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->player->jump();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->player->move(0.f, 1.0f, dt);
    }



}

void GameState::initTextures() {

    if (!this->textures["PLAYER_SHEET"].loadFromFile("resources/images/Assets/Player/Adventurer/adventurer-Sheet2x.png"))
    {
        std::cout << "Cannot Load Player Image" << std::endl;
    }
    std::cout << "Successfully Loaded Player" << std::endl;



}
void GameState::initFonts() {
    if (!this->font.loadFromFile("fonts/RobotoCondensed-Regular.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }

    std::cout << "Successfully Loaded Fonts" << std::endl;


}

void GameState::initPlayers() {
    this->player = new Player(500,470, 150.f, this->textures["PLAYER_SHEET"]);

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

void GameState::initTileMap() {
    this->tileMap = new TileMap(this->state_data->gridSize, 100,100, "resources/images/Assets/Map/16x16/Tile/TerrainSet.png");
    this->tileMap->loadFromFile("text.slmp");
}

void GameState::initView() {

    this->view.setSize(sf::Vector2f(this->state_data->gfxSettings->resolution.width/2.f, this->state_data->gfxSettings->resolution.height/2.f));
    this->view.setCenter(sf::Vector2f(this->state_data->gfxSettings->resolution.width/2.f, this->state_data->gfxSettings->resolution.height/2.f));

}

void GameState::updateView(const float &dt) {
    this->view.setCenter(this->player->getPosition());

    if (this->player->sliding)
    {
        this->player->sliding = false;
        this->view.setCenter(this->player->getPosition().x, this->player->getPosition().y);
    }
    else if(this->player->sitting)
    {
        this->player->sitting = false;
        this->view.setCenter(this->player->getPosition().x, this->player->getPosition().y );
    }

}

void GameState::initDeferredRender() {
    this->renderTexture.create(this->state_data->gfxSettings->resolution.width, this->state_data->gfxSettings->resolution.height);
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect(0,0,
            this->state_data->gfxSettings->resolution.width,
            this->state_data->gfxSettings->resolution.height)
            );
}

void GameState::updateTileMap(const float &dt) {
    this->tileMap->update();
    this->tileMap->updateCollision(this->player, dt);
}




