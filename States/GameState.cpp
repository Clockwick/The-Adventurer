//
// Created by Paratthakorn Sribunyong on 1/9/2019 AD.
//

#include "GameState.h"
#include "../Entities/Slime.h"


GameState::GameState(StateData* state_data)
: State(state_data)
{
    this->initVariables();
    this->initGui();
    this->initDeferredRender();
    this->initView();
    this->initTextures();
    this->initEnemies();
    this->initItems();
    this->initPlayers();
    this->initPlayerGUI();
    this->initFonts();
    this->initPauseMenu();
    this->initDeadMenu();
    this->initTileMap();
    this->loadFromFile("kit.txt");

    this->inventorySelector = new gui::InventorySelector(gui::p2pX(60.f, vm), this->state_data->gfxSettings->resolution.height - this->sidebar.getSize().y + 20,
                                                         900.f, 900.f,
                                                         this->state_data->gridSize, this->font, "Inventory"

    );
    this->status = new gui::Status(this->player,gui::p2pX(70.f, vm), this->state_data->gfxSettings->resolution.height - this->sidebar.getSize().y + 20,
                                   900.f, 900.f,
                                   this->state_data->gridSize, this->font, "Status", this->playerName
    );




}

GameState::~GameState() {
    delete this->player;
    delete this->playerGui;
    delete this->inventorySelector;
    delete this->pmenu;
    delete this->tileMap;
    delete this->deadmenu;
    delete this->status;


    for (size_t i = 0; i < this->activeEnemies.size(); i++)
        delete this->activeEnemies[i];
    for (size_t j = 0; j < this->itemElements.size(); j++)
        delete this->itemElements[j];


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

    if (!this->textures["CANDY_1"].loadFromFile("resources/images/Assets/Map/16x16/Tilesets/MV Icons Halloween/Candy.png"))
    {
        std::cout << "Cannot Load Candy" << std::endl;
    }
    std::cout << "Successfully Loaded Candy_1" << std::endl;
    if (!this->textures["BOSS_SHEET"].loadFromFile("resources/images/Assets/Monsters/Boss/Boss.png"))
    {
        std::cout << "Cannot Load Boss" << std::endl;
    }
    std::cout << "Successfully Loaded Boss" << std::endl;

}
void GameState::initFonts() {
    if (!this->font.loadFromFile("fonts/RobotoCondensed-Regular.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }

    std::cout << "Successfully Loaded Fonts" << std::endl;


}

void GameState::initGui() {

    this->sidebar.setSize(sf::Vector2f(this->state_data->gfxSettings->resolution.width, 75.f));
    this->sidebar.setPosition(sf::Vector2f(0.f, this->state_data->gfxSettings->resolution.height - this->sidebar.getSize().y));
    this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
    this->sidebar.setOutlineThickness(1.f);

}


void GameState::initVariables() {
    this->attacking = false;
    this->attacking1 = false;
    this->attacking2 = false;
    this->isHit = false;
    this->blink = false;
    this->count = 0;
    this->autoMoveLeft = false;
    this->autoMoveRight = false;
    this->isDead = false;
    this->reallyDead = false;
    this->slimeBlink = false;
    this->inventoryRect = sf::IntRect(0, 0, static_cast<int>(this->state_data->gridSize) * 0.45,
                                    static_cast<int>(this->state_data->gridSize) * 0.45);
}

void GameState::initPlayers() {
    this->player = new Player(500.f,475.f, 200.f, this->textures["PLAYER_SHEET"]);
    this->boss = new Boss(1000.f, 475.f, 200.f, this->textures["BOSS_SHEET"]);
}

void GameState::initPlayerGUI() {
    this->playerGui = new PlayerGUI(this->player,this->state_data->gfxSettings->resolution);
}
void GameState::initEnemies() {
    if (this->activeEnemies.size() < 10)
    {
        this->activeEnemies.push_back(new Slime(((rand()%30) * 100) + 1500, 475.f, 40.f, this->textures["SLIME_SHEET"]));

    }
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

    if (!this->paused && !this->reallyDead && !this->isDead)//Unpausesd
    {
        this->updateView(dt);
        this->player->getAttributeComponents()->update();
        this->updatePlayerInput(dt);
        this->updateGui(dt);
        this->player->update(dt);
        this->playerGui->update(dt);
        this->updateMovementAI(dt);
        this->initEnemies();

        for (auto *i : this->activeEnemies)
        {
            this->updateCollision(this->player, i, dt);
            i->update(dt);
        }
        for (auto *j : this->itemElements)
        {
            //Update Items Collision Here
            this->updateCollision(this->player, j, dt);
            j->update(dt);
        }
        this->boss->update(dt);
        this->updateTileMap(dt);
    }
    else if (this->isDead)
    {
        this->playerGui->update(dt);
        this->playDead(dt);
    }
    else if (this->reallyDead)
    {
        this->deadmenu->update(this->mousePosWindow);
        this->updateDeadMenuButtons();
    }
    else //Paused
    {
        this->pmenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();

    }
//    std::cout << this->slimeBlink << "\n";

}

void GameState::render(sf::RenderTarget *target) {

    if(!target)
        target = this->window;

    this->renderTexture.clear();
    this->renderTexture.setView(this->view);
    this->tileMap->render(this->renderTexture, this->player->getGridPosition(static_cast<int>(this->state_data->gridSize)), false);
    for (auto *j : this->itemElements)
    {
        j->render(this->renderTexture, true);
    }
    for (auto *i : this->activeEnemies)
    {
        i->render(this->renderTexture, true);
    }
    this->boss->render(this->renderTexture, true);

    if (!this->blink)
    {
        this->player->setColor(sf::Color::White);
        this->player->render(this->renderTexture, true);
    }

    else
    {

        this->smallTime = this->smallClock.getElapsedTime().asSeconds();
        if (this->smallTime >= 0.5f) {

            this->player->setColor(sf::Color::Transparent);
            this->player->render(this->renderTexture, true);
            this->smallCount++;
            this->smallClock.restart();
            if (this->smallCount >= 4) {
                this->smallCount = 0;
                this->blink = false;
            }
        }
        else
        {

            this->player->setColor(sf::Color::Red);
            this->player->render(this->renderTexture, true);
        }

    }


    this->renderTexture.setView(this->renderTexture.getDefaultView());
    this->renderGui(this->renderTexture);


    this->playerGui->render(this->renderTexture);
    //Pause Menu Render
    if (this->paused)
    {
        this->renderTexture.setView(this->renderTexture.getDefaultView());
        this->pmenu->render(renderTexture);
    }
    if (this->reallyDead)
    {
        this->renderTexture.setView(this->renderTexture.getDefaultView());
        this->deadmenu->render(renderTexture);
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

void GameState::initDeadMenu() {
    const sf::VideoMode& vm = this->state_data->gfxSettings->resolution;
    this->deadmenu = new DeadMenu(this->state_data->gfxSettings->resolution, this->font);

    this->deadmenu->addButton("QUIT",gui::p2pY(61.11f, vm), gui::p2pX(6.94f, vm),gui::p2pY(3.61f, vm), gui::calcCharSize(vm), "Exit");


}

void GameState::updatePauseMenuButtons() {
    if (this->pmenu->isButtonPressed(("QUIT")) && this->getKeyTime())
    {
        this->endState();
    }


}
void GameState::updateDeadMenuButtons() {
    if (this->deadmenu->isButtonPressed("QUIT") && this->getKeyTime())
        this->endState();

}
void GameState::updateGui(const float &dt) {
    this->inventorySelector->update(this->mousePosWindow, dt);
    this->status->update(this->mousePosWindow, dt);
}

void GameState::renderGui(sf::RenderTarget &target) {

    target.setView(this->state_data->window->getDefaultView());
    this->inventorySelector->render(target);
    this->status->render(target);
    target.draw(this->sidebar);
}



void GameState::updateView(const float &dt) {

    if (this->inventorySelector->getActive() || this->status->getActive())
    {
        this->view.setCenter(this->player->getPosition().x, this->player->getPosition().y);

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

    else {
        this->view.setCenter(
                std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) -
                                                            static_cast<float>(
                                                                    this->state_data->gfxSettings->resolution.width /
                                                                    2.f)) / 10.f),
                std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) -
                                                            static_cast<float>(
                                                                    this->state_data->gfxSettings->resolution.height /
                                                                    2)) / 10.f)
        );

        if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x) {
            if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f) {
                this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
            } else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x) {
                this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f,
                                     this->view.getCenter().y);
            }
        }

        if (this->tileMap->getMaxSizeF().y >= this->view.getSize().y) {
            if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f) {
                this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
            } else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y) {
                this->view.setCenter(this->view.getCenter().x,
                                     this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
            }
        }

        this->viewGridPosition.x =
                static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->state_data->gridSize);
        this->viewGridPosition.y =
                static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->state_data->gridSize);

        if (!this->player->getMovementComponents()->faceRight && (this->player->getAttack() || this->player->getAttack1() || this->player->getAttack2()) )
        {
            this->view.setCenter(
                    std::floor(25 + this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) -
                                                                static_cast<float>(
                                                                        this->state_data->gfxSettings->resolution.width /
                                                                        2)) / 10.f),
                    std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) -
                                                                static_cast<float>(
                                                                        this->state_data->gfxSettings->resolution.height /
                                                                        2)) / 10.f)
            );

            if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x) {
                if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f) {
                    this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
                } else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x) {
                    this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f,
                                         this->view.getCenter().y);
                }
            }

            if (this->tileMap->getMaxSizeF().y >= this->view.getSize().y) {
                if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f) {
                    this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
                } else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y) {
                    this->view.setCenter(this->view.getCenter().x,
                                         this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
                }
            }
        }

    }
}


void GameState::updateTileMap(const float &dt) {
    this->tileMap->update(this->player, dt);
    this->tileMap->update(this->boss, dt);
    for (auto *i : this->activeEnemies)
    {
        this->tileMap->update(i, dt);
    }
//    for (auto *j : this->itemElements)
//    {
//        this->tileMap->update(j, dt);
//    }

}

void GameState::updatePlayerGUI(const float &dt) {
    this->playerGui->update(dt);
}

void GameState::updateCollision(Entity *entity, Entity* enemy, const float& dt) {

    sf::FloatRect playerBounds = entity->getGlobalBounds();
    sf::FloatRect enemyBounds = enemy->getGlobalBounds();
    sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
    this->time = this->clock.getElapsedTime().asSeconds();
    this->blinkTime = this->blinkClock.getElapsedTime().asSeconds();
    this->slimeTime = this->slimeClock.getElapsedTime().asSeconds();
    if (this->blinkTime >= 2.f)
    {
        this->blink = false;
        this->blinkClock.restart();
    }
//    std::cout << this->slimeTime << " " << this->slimeBlink << "\n";
    if (this->slimeTime > 0.3f && this->slimeBlink)
    {
        for (int i = 0; i < this->hitEnemies.size(); i++)
        {
            this->hitEnemies[i]->setColor(sf::Color::White);
            this->slimeBlink = false;
            this->slimeClock.restart();
        }


    }


    for (int i = 0; i < this->activeEnemies.size(); i++) {
        if (this->activeEnemies[i]->intersects(nextPositionBounds) && this->player->getType() == HitTypes::ATTACK_COL)
        {
            if (playerBounds.left < enemyBounds.left
                && playerBounds.left + playerBounds.width < enemyBounds.left + enemyBounds.width
                && playerBounds.top < enemyBounds.top + enemyBounds.height + 5
                && playerBounds.top + playerBounds.height > enemyBounds.top && this->time > 1.f)
            {
                this->autoMoveLeft = true;
                this->setAI(this->activeEnemies[i]);
                this->activeEnemies[i]->setColor(sf::Color::Red);
                this->activeEnemies[i]->gotAttackRight();
                this->activeEnemies[i]->loseHP((this->player->getAttributeComponents()->damageMax + this->player->getAttributeComponents()->damageMin) / 2);
                this->slimeBlink = true;
                this->slimeClock.restart();
//                std::cout << "Enemy HP: " << this->activeEnemies[i]->getAttributeComponents()->hp << "\n";

                if (this->activeEnemies[i]->getAttributeComponents()->hp <= 0)
                {
                    this->player->gainEXP(10);
                    int chance = rand()%5 + 1;
                    if (chance == 2)
                            this->itemElements.push_back(new Item(this->activeEnemies[i]->getPosition().x, this->activeEnemies[i]->getPosition().y - 60, this->textures["CANDY_1"]));
                    this->hitEnemies.erase(this->hitEnemies.begin() + i);
                    this->activeEnemies.erase(this->activeEnemies.begin() + i);
                }

            }
            else if (playerBounds.left > enemyBounds.left
                     && playerBounds.left + playerBounds.width > enemyBounds.left + enemyBounds.width
                     && playerBounds.top < enemyBounds.top + enemyBounds.height
                     && playerBounds.top + playerBounds.height > enemyBounds.top && this->time > 1.f) {
                this->autoMoveRight = true;
                this->setAI(this->activeEnemies[i]);
                this->activeEnemies[i]->gotAttackLeft();
                this->activeEnemies[i]->loseHP((this->player->getAttributeComponents()->damageMax + this->player->getAttributeComponents()->damageMin) / 2);
                this->activeEnemies[i]->setColor(sf::Color::Red);
                this->slimeBlink = true;
                this->slimeClock.restart();
//                std::cout << "Enemy HP: " << this->activeEnemies[i]->getAttributeComponents()->hp << "\n";
                if (this->activeEnemies[i]->getAttributeComponents()->hp <= 0)
                {
                    this->player->gainEXP(10);
                    int chance = rand()%5 + 1;
                    if (chance == 2)
                        this->itemElements.push_back(new Item(this->activeEnemies[i]->getPosition().x, this->activeEnemies[i]->getPosition().y - 60, this->textures["CANDY_1"]));
                    this->hitEnemies.erase(this->hitEnemies.begin() + i);
                    this->activeEnemies.erase(this->activeEnemies.begin() + i);
                }

            }


        }
        else if (this->activeEnemies[i]->intersects(nextPositionBounds) && this->player->getType() == HitTypes::DEFAULT_COL) {

            //Right collision
            if (playerBounds.left < enemyBounds.left
                && playerBounds.left + playerBounds.width < enemyBounds.left + enemyBounds.width
                && playerBounds.top < enemyBounds.top + enemyBounds.height + 5
                && playerBounds.top + playerBounds.height > enemyBounds.top && this->time > 2.f) {
//                std::cout << "Right Collision" << std::endl;
                this->player->loseHP((this->activeEnemies[i]->getAttributeComponents()->damageMin + this->activeEnemies[i]->getAttributeComponents()->damageMax) / 2);
                this->player->stopVelocityX();
                this->isHit = true;

                if (this->isHit) {
                    this->blink = true;
                    this->blinkClock.restart();
                    this->isHit = false;
                    this->clock.restart();
                }
                if (this->player->getAttributeComponents()->hp <= 0)
                {
                    this->player->loseEXP(50);
                    this->isDead = true;
                }
            }

                //Left collision
            else if (playerBounds.left > enemyBounds.left
                     && playerBounds.left + playerBounds.width > enemyBounds.left + enemyBounds.width
                     && playerBounds.top < enemyBounds.top + enemyBounds.height
                     && playerBounds.top + playerBounds.height > enemyBounds.top && this->time > 2.f) {
//                std::cout << "Left Collision" << std::endl;

                this->player->loseHP((this->activeEnemies[i]->getAttributeComponents()->damageMin + this->activeEnemies[i]->getAttributeComponents()->damageMax) / 2);
                this->player->stopVelocityX();
                this->isHit = true;
                if (this->isHit) {
                    this->blink = true;
                    this->blinkClock.restart();
                    this->isHit = false;
                    this->clock.restart();
                }
                if (this->player->getAttributeComponents()->hp <= 0)
                {
                    this->player->loseEXP(50);
                    this->isDead = true;
                }
            }




        }

    }
    for (int i = 0; i < this->itemElements.size(); i++) {
        if (this->itemElements[i]->intersects(nextPositionBounds))
        {
            if (playerBounds.left < enemyBounds.left
                && playerBounds.left + playerBounds.width < enemyBounds.left + enemyBounds.width
                && playerBounds.top < enemyBounds.top + enemyBounds.height + 5
                && playerBounds.top + playerBounds.height > enemyBounds.top)
            {

                this->player->gainHP(30);
                this->itemElements.erase(this->itemElements.begin() + i);
            }
            else if (playerBounds.left > enemyBounds.left
                     && playerBounds.left + playerBounds.width > enemyBounds.left + enemyBounds.width
                     && playerBounds.top < enemyBounds.top + enemyBounds.height
                     && playerBounds.top + playerBounds.height > enemyBounds.top)
            {
                this->player->gainHP(30);
                this->itemElements.erase(this->itemElements.begin() + i);
            }
            }

        }


}

void GameState::updateMovementAI(const float &dt) {
    for (int i = 0; i < this->activeEnemies.size(); i++)
    {
        
        if (this->player->getPosition().x > this->activeEnemies[i]->getPosition().x)
            this->activeEnemies[i]->move(1.f,0.f,dt);
        else if (this->player->getPosition().x - this->activeEnemies[i]->getPosition().x > -500.f)
            this->activeEnemies[i]->move(-1.f,0.0f,dt);

    }
    if (this->autoMoveLeft)
    {
//        std::cout << "AutoMoveL" << "\n";

        if (this->enemyAI->getPosition().x > this->player->getPosition().x)
            this->enemyAI->move(-1.0f, 0.f, dt);

        else if (this->enemyAI->getPosition().x < this->player->getPosition().x)
            this->enemyAI->move(1.0f, 0.f, dt);


    }

    if (this->autoMoveRight)
    {
//        std::cout << "AutoMoveR" << "\n";

        if (this->enemyAI->getPosition().x < this->player->getPosition().x)
            this->enemyAI->move(1.0f, 0.f, dt);

        else if (this->enemyAI->getPosition().x > this->player->getPosition().x)
            this->enemyAI->move(-1.0f, 0.f, dt);

    }

}

void GameState::setAI(Enemy *enemy) {
    this->enemyAI = enemy;
    this->hitEnemies.push_back(this->enemyAI);
}
void GameState::playDead(const float& dt)
{
    if (this->isDead)
    {
        this->view.setCenter(this->player->getPosition());
        if (this->player->getAnimationComponents()->play("Dead",dt, 25 ,100, true))
        {
            this->reallyDead = true;
            this->isDead = false;
        }

    }

}

void GameState::initItems() {


}

void GameState::loadFromFile(const std::string file_name) {
    std::ifstream in_file;
    in_file.open(file_name);
    if (in_file.is_open())
    {
        std::string player_name = "Easy";
        //Load
        in_file >> player_name;

        this->playerName = player_name;

    }
    in_file.close();


}


