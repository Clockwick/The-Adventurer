//
// Created by Paratthakorn Sribunyong on 7/9/2019 AD.
//
#include "Entity.h"
#ifndef GUJARUNSFML_PLAYER_H
#define GUJARUNSFML_PLAYER_H

enum ATTACK_TYPE {
    EARTH = 0,
    FIRE, ICE, TROPHY
};
class Player : public Entity
{
public:
    Player(float x,  float y, const float& jumpHeight,sf::Texture& texture_sheet);
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
    void gotAttackLeft(const float velocity, const float& dt);
    void gotAttackRight(const float velocity, const float& dt);
    bool getAttack();
    bool getAttack1();
    bool getAttack2();
    void setColor(sf::Color color);
    const bool& getJump() const;
    void changeAttackType(const short& attack_type);
    const short& getAttackType() const;
    const short& getType() const;
    //Variables
    bool sliding;
    bool sitting;
    AttributeComponent* getAttributeComponents();
    MovementComponents* getMovementComponents();
    AnimationComponent* getAnimationComponents();
private:
    void initVariables();
    void initAudio();
    void initAnimation();
private:
    bool attacking;
    bool attacking1;
    bool attacking2;
    short attackType;
    const float jumpHeight;
    bool isJump;
    bool playSound;
    sf::Vector2f velocity;
    short type;
    std::map <std::string, sf::Texture> textureSheet;




    //Audio
    sf::SoundBuffer swordSoundBF;
    sf::Sound swordSound;
    sf::Sound burnSound;
    sf::SoundBuffer burnSoundBuffer;



};
#endif //GUJARUNSFML_PLAYER_H
