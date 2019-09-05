//
// Created by Paratthakorn Sribunyong on 1/9/2019 AD.
//
#include "State.h"
#ifndef GUJARUNSFML_GAMESTATE_H
#define GUJARUNSFML_GAMESTATE_H

class GameState : public State
{

public:
    GameState(sf::RenderWindow* window, std::stack <State*>* states);
    virtual ~GameState();
    void endState();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void updateInput(const float& dt);


private:
    Entity player;


};

#endif //GUJARUNSFML_GAMESTATE_H


