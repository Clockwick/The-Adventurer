//
// Created by Paratthakorn Sribunyong on 7/9/2019 AD.
//
#include "Entity.h"
#ifndef GUJARUNSFML_PLAYER_H
#define GUJARUNSFML_PLAYER_H
class Player : public Entity
{
public:
    Player(float x,  float y,sf::Texture& texture);
    virtual ~Player();
private:
    void initVariables();
    void initComponents();




};
#endif //GUJARUNSFML_PLAYER_H
