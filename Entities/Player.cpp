//
// Created by Paratthakorn Sribunyong on 7/9/2019 AD.
//

#include "Player.h"
//Constructor , DeConstructor
Player::Player(float x,  float y, const float& jumpHeight,sf::Texture& texture_sheet)
: jumpHeight(jumpHeight)
{

    this->initVariables();
    this->initAudio();


    this->initComponents();


    this->createMovementComponents(300, 1500.0f, 500.0f, this->jumpHeight);
    this->createAttributeComponents(1);
    this->createSkillComponents();
    this->createAnimationComponents( texture_sheet);
    this->animationComponents->getptr(&this->isJump);
    this->initAnimation();
    this->setPosition(x , y);


//    std::cout << "Player.cpp: "<< this->isJump << std::endl;


}

Player::~Player() {


}
//Initializer Function

void Player::initComponents() {
    //GIVE VALUE TO createMovementComponents
}

void Player::initVariables() {
    this->attacking = false;
    this->sliding = false;
    this->sitting = false;
    this->isJump = true;
    this->canJump = true;
}
void Player::initAnimation() {
    this->animationComponents->addAnimation("IDLE", 15.f, 0, 0, 3, 0, 100, 74);
    this->animationComponents->addAnimation("RUN", 15.f, 0, 1, 5, 1, 100, 74);
    this->animationComponents->addAnimation("SLIDE", 15.f, 0, 3, 3, 3, 100, 74);
    this->animationComponents->addAnimation("SIT", 15.f, 4, 0, 6, 0, 100, 74);
    this->animationComponents->addAnimation("ATTACK1", 15.f, 0, 6, 6, 6, 100, 74);
    this->animationComponents->addAnimation("ATTACK2", 15.f, 0, 7, 3, 7, 100, 74);
    this->animationComponents->addAnimation("ATTACK3", 15.f, 0, 8, 5, 8, 100 , 74);
    this->animationComponents->addAnimation("JUMP", 15.f , 0 , 2, 13 , 2 , 100 , 74);
}


void Player::update(const float& dt)
{
    this->updateJumping(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        this->attributeComponents->gainExp(20);
//    system("clear");
//    std::cout << this->attributeComponents->debugPrint() << std::endl;
    this->movementComponents->update(dt);
    this->updateAttack();
    this->updateAnimation(dt);

//    std::cout << "In player.cpp: " << this->isJump << std::endl;



}

void Player::updateAttack()
{
    if(this->movementComponents->getState(ATTACK))
    {
        this->attacking = true;
        this->swordSound.play();
        //this->createHitboxComponents(this->sprite,15.f,5.f,31.f,30.f);
    }

}

void Player::updateAnimation(const float &dt)
{
    if (this->attacking && this->canJump)
    {

        if(this->animationComponents->play("ATTACK1", dt, true))
            this->attacking = false;

    }
    if (this->movementComponents->getState(IDLE) && !this->isJump)
    {
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("IDLE", dt);

    }

    else if (this->movementComponents->getState(SLIDE_RIGHT) && this->canJump)
    {
        this->sliding = true;
        this->sprite.setOrigin(0.f,0.f);
        this->sprite.setScale(1.f,1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);;
        this->animationComponents->play("SLIDE", dt);
    }

    else if (this->movementComponents->getState(SLIDE_LEFT) && this->canJump)
    {
        this->sliding = true;
        this->sprite.setOrigin(100.f,0.f);
        this->sprite.setScale(-1.f,1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("SLIDE", dt);
    }
    else if (this->movementComponents->getState(MOVING_RIGHT) && this->canJump)
    {
        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("RUN", dt, this->movementComponents->getVelocity().x,
                                        this->movementComponents->getMaxVelocity());
    }
    else if (this->movementComponents->getState(MOVING_LEFT) && this->canJump) {
        this->sprite.setOrigin(100.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("RUN", dt, this->movementComponents->getVelocity().x,
                                        this->movementComponents->getMaxVelocity());
    }
    else if (this->movementComponents->getState(SIT) && this->canJump)
    {
        this->sitting = true;
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("SIT", dt);
    }
    else if (!this->canJump && this->movementComponents->getState(JUMP_LEFT)) {
        this->sprite.setOrigin(100.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);
        this->animationComponents->play("JUMP", dt, 135, 100);
    }
    else if (!this->canJump && this->movementComponents->getState(JUMP_RIGHT)) {
        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->animationComponents->play("JUMP", dt, 120, 100);
    }


    this->hitboxComponents->update();

}

void Player::render(sf::RenderTarget& target, const bool show_hitbox) {
    if (show_hitbox)
        this->hitboxComponents->render(target);
    else
        target.draw(this->sprite);

}

void Player::initAudio() {
    this->swordSoundBF.loadFromFile("resources/Audio/swordswing.wav");
    this->swordSound.setBuffer(swordSoundBF);

}

void Player::updateJumping(const float& dt) {
    this->isJump = this->movementComponents->getVelocity().y != 0;

}

AttributeComponent *Player::getAttributeComponents() {
    return this->attributeComponents;
}

void Player::gainHP(const int hp) {
    this->attributeComponents->hp += hp;

    if (this->attributeComponents->hp > this->attributeComponents->hpMax)
        this->attributeComponents->hp = this->attributeComponents->hpMax;
}

void Player::loseHP(const int hp) {
    this->attributeComponents->hp -= hp;

    if (this->attributeComponents->hp < 0)
        this->attributeComponents->hp = 0;

}
void Player::gainEXP(const int exp) {
    this->attributeComponents->gainExp(exp);

}

void Player::loseEXP(const int exp) {
    this->attributeComponents->exp -= exp;

    if (this->attributeComponents->exp < 0)
        this->attributeComponents->exp = 0;
}



