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
    void updateGui(const float& dt);
    void updatePlayerInput(const float& dt);
    void updateInput(const float& dt);
    void updateView(const float& dt);
    void updateTileMap(const float& dt);
    void updatePlayerGUI(const float& dt);
    void updateCollision(Entity *entity, Enemy* enemy, const float& dt);

    //Render
    void render(sf::RenderTarget* target = nullptr);
    void renderGui(sf::RenderTarget& target);

private:
    //Player
    Player* player;
    PlayerGUI* playerGui;

    //Enemy
    std::vector<Enemy*> activeEnemies;
    PauseMenu* pmenu;
    TileMap* tileMap;

    sf::Vector2i viewGridPosition;

    //Variables
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;

    bool canJump;
    bool attacking;
    bool attacking1;
    bool attacking2;
    bool isHit;
    int count;

    //Hitbox

    //Clock
    sf::Clock clock;
    float time;

    //Blink
    bool blink;
    bool slimeBlink;
    sf::Clock blinkClock;
    float blinkTime;
    sf::Clock blinkSlimeClock;
    float blinkSlimeTime;
    sf::Clock smallClock;
    float smallTime;
    int smallCount;


    bool bounceLeft;
    bool bounceRight;


    //Gui Staff
    sf::RectangleShape sidebar;

    //Functions
    void initVariables();
    void initDeferredRender();
    void initView();
    void initTextures();
    void initPlayers();
    void initFonts();
    void initPauseMenu();
    void initTileMap();
    void initPlayerGUI();
    void updatePauseMenuButtons();
    void initEnemies();
    void initGui();


};

#endif //GUJARUNSFML_GAMESTATE_H


