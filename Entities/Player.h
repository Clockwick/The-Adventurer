//
// Created by Paratthakorn Sribunyong on 7/9/2019 AD.
//
#include "Entity.h"
#ifndef GUJARUNSFML_PLAYER_H
#define GUJARUNSFML_PLAYER_H


class Player : public Entity
{
public:
    Player(float x,  float y, const float& jumpHeight, sf::Texture& texture_sheet);
    virtual ~Player();

    void updateAttack();
    void updateAnimation(const float& dt);
    void updateJumping(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget& target);

    //Variables
    bool sliding;
    bool sitting;
private:
    void initVariables();
    void initComponents();
    void initAudio();
private:
    bool attacking;
    const float jumpHeight;
    bool isJump;


    //Audio
    sf::SoundBuffer swordSoundBF;
    sf::Sound swordSound;



};
#endif //GUJARUNSFML_PLAYER_H
