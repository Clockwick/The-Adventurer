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

    void loseHP(const int hp);
    void loseEXP(const int exp);
    void gainHP(const int hp);
    void gainEXP(const int exp);
    void updateAttack();
    void updateAnimation(const float& dt);
    void updateJumping(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget& target, const bool show_hitbox = false);
    bool getAttack();
    bool getAttack1();
    bool getAttack2();

    //Variables
    bool sliding;
    bool sitting;
    AttributeComponent* getAttributeComponents();
private:
    void initVariables();
    void initAudio();
    void initAnimation();
private:
    bool attacking;
    bool attacking1;
    bool attacking2;
    const float jumpHeight;
    bool isJump;
    bool playSound;



    //Audio
    sf::SoundBuffer swordSoundBF;
    sf::Sound swordSound;



};
#endif //GUJARUNSFML_PLAYER_H
