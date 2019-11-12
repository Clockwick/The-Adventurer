//
// Created by Paratthakorn Sribunyong on 1/9/2019 AD.
//
#include "State.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"
#include "../PlayerGUI.h"
#include "../Entities/Enemy.h"
#ifndef GUJARUNSFML_GAMESTATE_H
#define GUJARUNSFML_GAMESTATE_H

class PauseMenu;
class Player;
class TileMap;
class PlayerGUI;

class GameState : public State
{

public:
    GameState(StateData* state_data);
    virtual ~GameState();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void updatePlayerInput(const float& dt);
    void updateInput(const float& dt);
    void updateView(const float& dt);
    void updateTileMap(const float& dt);
    void updatePlayerGUI(const float& dt);

private:
    //Player
    Player* player;
    PlayerGUI* playerGui;

    //Enemy
    Enemy* testEnemy;
//
    PauseMenu* pmenu;
    TileMap* tileMap;

    sf::Vector2i viewGridPosition;

    //Variables
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;

    bool canJump;



    //Functions
    void initDeferredRender();
    void initView();
    void initTextures();
    void initPlayers();
    void initFonts();
    void initPauseMenu();
    void initTileMap();
    void initPlayerGUI();
    void updatePauseMenuButtons();


};

#endif //GUJARUNSFML_GAMESTATE_H


