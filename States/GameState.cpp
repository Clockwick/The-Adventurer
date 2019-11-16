//
// Created by Paratthakorn Sribunyong on 1/9/2019 AD.
//

#include "GameState.h"
#include "../Entities/Slime.h"


GameState::GameState(StateData* state_data)
: State(state_data)
{
    this->initVariables();
    this->initDeferredRender();
    this->initView();
    this->initTextures();
    this->initEnemies();
    this->initPlayers();
    this->initPlayerGUI();
    this->initFonts();
    this->initPauseMenu();
    this->initTileMap();


}

GameState::~GameState() {
    delete this->player;
    delete this->playerGui;
    delete this->pmenu;
    delete this->tileMap;

    for (size_t i = 0; i < this->activeEnemies.size(); i++)
        delete this->activeEnemies[i];

}


void GameState::initTextures() {

    if (!this->textures["PLAYER_SHEET"].loadFromFile("resources/images/Assets/Player/Adventurer/adventurer-Sheet3x.png"))
    {
        std::cout << "Cannot Load Player Image" << std::endl;
    }
    std::cout << "Successfully Loaded Player" << std::endl;

    if (!this->textures["SLIME_SHEET"].loadFromFile("resources/images/Assets/Monsters/Slime/Slime.png"))
    {
        std::cout << "Cannot Load Slime Image" << std::endl;
    }
    std::cout << "Successfully Loaded Slime" << std::endl;


}
void GameState::initFonts() {
    if (!this->font.loadFromFile("fonts/RobotoCondensed-Regular.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }

    std::cout << "Successfully Loaded Fonts" << std::endl;


}


void GameState::initVariables() {
    this->attacking = false;
    this->attacking1 = false;
    this->attacking2 = false;
    this->isHit = false;
    this->blink = false;
    this->count = 0;

}

void GameState::initPlayers() {
    this->player = new Player(500.f,470.f, 200.f, this->textures["PLAYER_SHEET"]);

}

void GameState::initPlayerGUI() {
    this->playerGui = new PlayerGUI(this->player,this->state_data->gfxSettings->resolution);
}
void GameState::initEnemies() {
    this->activeEnemies.push_back(new Slime(900.f, 475.f, 100.f, this->textures["SLIME_SHEET"]));
    this->activeEnemies.push_back(new Slime(1000.f , 475.f, 100.f, this->textures["SLIME_SHEET"]));
    this->activeEnemies.push_back(new Slime(1100.f , 475.f, 100.f, this->textures["SLIME_SHEET"]));
    this->activeEnemies.push_back(new Slime(1200.f , 475.f, 100.f, this->textures["SLIME_SHEET"]));
}



void GameState::initTileMap() {
    this->tileMap = new TileMap(this->state_data->gridSize, 100,100, "resources/images/Assets/Map/16x16/Tile/TerrainSet.png");
    this->tileMap->loadFromFile("text.slmp");
}

void GameState::initView() {

    this->view.setSize(sf::Vector2f(static_cast<float>(this->state_data->gfxSettings->resolution.width)/2.f, static_cast<float>(this->state_data->gfxSettings->resolution.height)/2.f));
    this->view.setCenter(sf::Vector2f(static_cast<float>(this->state_data->gfxSettings->resolution.width)/2.f, static_cast<float>(this->state_data->gfxSettings->resolution.height)/2.f));

}
void GameState::initDeferredRender() {
    this->renderTexture.create(this->state_data->gfxSettings->resolution.width, this->state_data->gfxSettings->resolution.height);
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect(0,0,
                                                  this->state_data->gfxSettings->resolution.width,
                                                  this->state_data->gfxSettings->resolution.height)
    );
}



void GameState::update(const float &dt) {

    this->updateMousePos(&this->view);
    this->updateKeytime(dt);
    this->updateInput(dt);

    if (!this->paused)//Unpaused
    {
        this->updateView(dt);
        this->updatePlayerInput(dt);
        this->updateTileMap(dt);
        this->player->update(dt);
        this->playerGui->update(dt);

        for (auto *i : this->activeEnemies)
        {
            this->updateCollision(this->player, i, dt);
            i->update(dt);
        }
    }
    else //Paused
    {

        this->pmenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();

    }

}

void GameState::render(sf::RenderTarget *target) {

    if(!target)
        target = this->window;

    this->renderTexture.clear();
    this->renderTexture.setView(this->view);
    this->tileMap->render(this->renderTexture, this->player->getGridPosition(static_cast<int>(this->state_data->gridSize)), false);
    for (auto *i : this->activeEnemies)
    {
        i->render(this->renderTexture, true);
    }
    if (!this->blink)
        this->player->render(this->renderTexture, true);



    this->renderTexture.setView(this->renderTexture.getDefaultView());

    this->playerGui->render(this->renderTexture);
    //Pause Menu Render
    if (this->paused)
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !this->player->getAttack()&& !this->player->getAttack1()&& !this->player->getAttack2())
    {
        this->player->move(-1.0f, 0.0f, dt);
//        for (auto *i : this->activeEnemies)
//            i->move(-1.0f, 0.0f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !this->player->getAttack()&& !this->player->getAttack1()&& !this->player->getAttack2())
    {
        this->player->move(1.0f, 0.0f, dt);
//        for (auto *i : this->activeEnemies)
//            i->move(1.0f,0.0f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->player->jump();
//        for (auto *i : this->activeEnemies)
//            i->jump();
    }

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
    const sf::VideoMode& vm = this->state_data->gfxSettings->resolution;
    this->pmenu = new PauseMenu(this->state_data->gfxSettings->resolution, this->font);

    this->pmenu->addButton("QUIT",gui::p2pY(61.11f, vm), gui::p2pX(6.94f, vm),gui::p2pY(3.61f, vm), gui::calcCharSize(vm), "Quit");

}

void GameState::updatePauseMenuButtons() {
    if (this->pmenu->isButtonPressed(("QUIT")) && this->getKeyTime())
        this->endState();

}


void GameState::updateView(const float &dt) {
//    this->view.setCenter(this->player->getPosition());
//
//    if (this->player->sliding)
//    {
//        this->player->sliding = false;
//        this->view.setCenter(this->player->getPosition().x, this->player->getPosition().y);
//    }
//    else if(this->player->sitting)
//    {
//        this->player->sitting = false;
//        this->view.setCenter(this->player->getPosition().x, this->player->getPosition().y );
//    }
    this->view.setCenter(
            std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->state_data->gfxSettings->resolution.width / 2)) / 10.f),
            std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->state_data->gfxSettings->resolution.height / 2)) / 10.f)
    );

    if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x)
    {
        if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
        {
            this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
        }
        else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x)
        {
            this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
        }
    }

    if (this->tileMap->getMaxSizeF().y >= this->view.getSize().y)
    {
        if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
        {
            this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
        }
        else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y)
        {
            this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
        }
    }

    this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->state_data->gridSize);
    this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->state_data->gridSize);

}


void GameState::updateTileMap(const float &dt) {
    this->tileMap->update(this->player, dt);
    for (auto *i : this->activeEnemies)
    {
        this->tileMap->update(i, dt);
    }



}

void GameState::updatePlayerGUI(const float &dt) {
    this->playerGui->update(dt);

}

void GameState::updateCollision(Entity *entity, Enemy* enemy, const float& dt) {
    sf::FloatRect playerBounds = entity->getGlobalBounds();
    sf::FloatRect enemyBounds = enemy->getGlobalBounds();
    sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
    this->time = this->clock.getElapsedTime().asSeconds();
    for (auto *i : this->activeEnemies) {
        if (i->intersects(nextPositionBounds)) {

            //Right collision
            if (playerBounds.left < enemyBounds.left
                && playerBounds.left + playerBounds.width < enemyBounds.left + enemyBounds.width
                && playerBounds.top < enemyBounds.top + enemyBounds.height + 5
                && playerBounds.top + playerBounds.height > enemyBounds.top && this->time > 3.f) {
                std::cout << "Right Collision" << std::endl;
                this->player->loseHP(1);
                this->player->gotAttackLeft();
                this->isHit = true;
                if (this->isHit) {
                    this->isHit = false;
                    this->clock.restart();
                }

            }



                //Left collision
            else if (playerBounds.left > enemyBounds.left
                     && playerBounds.left + playerBounds.width > enemyBounds.left + enemyBounds.width
                     && playerBounds.top < enemyBounds.top + enemyBounds.height
                     && playerBounds.top + playerBounds.height > enemyBounds.top && this->time > 3.f) {
                std::cout << "Left Collision" << std::endl;

                this->player->loseHP(1);
                this->player->gotAttackRight();
                this->isHit = true;
                if (this->isHit) {
                    this->isHit = false;
                    this->clock.restart();
                }
            }


        }

    }


}
