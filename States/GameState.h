//
// Created by Paratthakorn Sribunyong on 1/9/2019 AD.
//
#include "State.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"
#include "../PlayerGUI.h"
#include "../Entities/Enemy.h"
#include "../GUI/Dead.h"
#include "../Items/Items.h"
#include "../Entities/Boss.h"

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
    void updateCollision(Entity *entity, Entity* enemy, const float& dt);
    void updatePlayerState(const float &dt);
    void renderPlayerState(sf::RenderTarget& target);
    void updateFireBall();

    //Render
    void render(sf::RenderTarget* target = nullptr);
    void renderGui(sf::RenderTarget& target);

    //Save && Load
    void loadFromFile(const std::string file_name);

    //Acessors

private:
    //Player
    Player* player;
    PlayerGUI* playerGui;
    std::string playerName;
    const sf::VideoMode& vm = this->state_data->gfxSettings->resolution;

    //Enemy
    std::vector<Enemy*> activeEnemies;
    PauseMenu* pmenu;
    TileMap* tileMap;
    DeadMenu* deadmenu;

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
    sf::Clock blinkClock;
    float blinkTime;
    sf::Clock smallClock;
    float smallTime;
    int smallCount;
    bool slimeBlink;
    sf::Clock slimeClock;
    float slimeTime;

    //Bot
    void updateMovementAI(const float &dt);
    bool autoMoveLeft;
    bool autoMoveRight;
    Enemy* enemyAI;
    Boss* boss;
    void setAI(Enemy* enemy);

    int playerState;
    sf::RectangleShape skillShape;
    std::vector <Item*> fireRed;
    bool shootFire;
    bool activeFire;






    //Gui Staff
    sf::RectangleShape sidebar;
    sf::RectangleShape selectorRect;
    sf::IntRect inventoryRect;
    sf::Text cursorText;
    gui::InventorySelector* inventorySelector;

    sf::RectangleShape statusSideBar;
    sf::IntRect statusRect;
    sf::Text statusCursorText;
    gui::Status* status;

    short type;
    bool collision;
    int layer;
    bool tileAddLock;

    //Dead
    bool isDead;
    bool reallyDead;

    //Items
    std::vector<Item*> itemElements;

    std::vector<Enemy*> hitEnemies;

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
    void updateDeadMenuButtons();
    void initEnemies();
    void initGui();
    void initDeadMenu();
    void playDead(const float& dt);
    void initItems();


};

#endif //GUJARUNSFML_GAMESTATE_H


