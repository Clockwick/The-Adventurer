//
// Created by Paratthakorn Sribunyong on 1/9/2019 AD.
//
#include "State.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"
#ifndef GUJARUNSFML_GAMESTATE_H
#define GUJARUNSFML_GAMESTATE_H

class PauseMenu;
class Player;
class TileMap;

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



private:
    Player* player;
    PauseMenu* pmenu;
    TileMap* tileMap;

    //Variables
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;

    //Functions
    void initDeferredRender();
    void initView();
    void initTextures();
    void initPlayers();
    void initFonts();
    void initPauseMenu();
    void initTileMap();
    void updatePauseMenuButtons();


};

#endif //GUJARUNSFML_GAMESTATE_H


