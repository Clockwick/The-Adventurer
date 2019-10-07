//
// Created by Paratthakorn Sribunyong on 1/9/2019 AD.
//
#include "State.h"
#include "../GUI/PauseMenu.h"
#ifndef GUJARUNSFML_GAMESTATE_H
#define GUJARUNSFML_GAMESTATE_H

class GameState : public State
{

public:
    GameState(sf::RenderWindow* window, std::stack <State*>* states);
    virtual ~GameState();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void updatePlayerInput(const float& dt);
    void updateInput(const float& dt);




private:
    Player* player;
    PauseMenu* pmenu;


    //Variables
    sf::Font font;

    //Functions

    void initTextures();
    void initPlayers();
    void initFonts();
    void initPauseMenu();
    void updatePauseMenuButtons();


};

#endif //GUJARUNSFML_GAMESTATE_H


