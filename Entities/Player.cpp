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
    this->setPosition(x , y);

    this->initComponents();

    this->createAttributeComponents(1);
    this->createMovementComponents(300, 1500.0f, 500.0f, this->jumpHeight);
    this->createAnimationComponents( texture_sheet);

    this->animationComponents->addAnimation("IDLE", 15.f, 0, 0, 3, 0, 100, 74);
    this->animationComponents->addAnimation("RUN", 15.f, 1, 1, 6, 1, 100, 74);
    this->animationComponents->addAnimation("SLIDE", 15.f, 3, 3, 6, 3, 100, 74);
    this->animationComponents->addAnimation("SIT", 15.f, 4, 0, 6, 0, 100, 74);
    this->animationComponents->addAnimation("ATTACK1", 15.f, 3, 6, 6, 6, 100, 74);
    this->animationComponents->addAnimation("ATTACK2", 15.f, 0, 7, 3, 7, 100, 74);
    this->animationComponents->addAnimation("JUMP", 15.f , 1 , 2, 7 , 2 , 100 , 74);
    this->animationComponents->addAnimation("JUMP2", 12.f , 0 , 3, 2 , 3 ,100, 74);

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
    this->isJump = false;
}

void Player::update(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        this->attributeComponents->gainExp(20);
//    system("clear");
//    std::cout << this->attributeComponents->debugPrint() << std::endl;
    this->movementComponents->update(dt);
    this->updateAttack();
    this->updateJumping(dt);
    this->updateAnimation(dt);


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
    if (this->attacking)
    {

        if(this->animationComponents->play("ATTACK2", dt, true))
            this->attacking = false;

    }
    else if (this->movementComponents->getState(IDLE) && !this->isJump)
    {

        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("IDLE", dt);

    }

    if (this->movementComponents->getState(SLIDE_RIGHT))
    {
        this->sliding = true;
        this->sprite.setOrigin(0.f,0.f);
        this->sprite.setScale(1.f,1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);;
        this->animationComponents->play("SLIDE", dt);
    }

    else if (this->movementComponents->getState(SLIDE_LEFT))
    {
        this->sliding = true;
        this->sprite.setOrigin(100.f,0.f);
        this->sprite.setScale(-1.f,1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("SLIDE", dt);
    }
    else if (this->movementComponents->getState(MOVING_RIGHT))
    {


        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("RUN", dt, this->movementComponents->getVelocity().x,
                                        this->movementComponents->getMaxVelocity());
    }
    else if (this->movementComponents->getState(MOVING_LEFT)) {
        this->sprite.setOrigin(100.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("RUN", dt, this->movementComponents->getVelocity().x,
                                        this->movementComponents->getMaxVelocity());
    }
    else if (this->movementComponents->getState(SIT))
    {
        this->sitting = true;
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("SIT", dt);
    }
    else if (this->isJump)
    {
        this->animationComponents->play("JUMP", dt, true);
        this->animationComponents->play("JUMP2" ,  dt, true);
    }




    this->hitboxComponents->update();

}

void Player::render(sf::RenderTarget& target) {
    target.draw(this->sprite);

    if (this->hitboxComponents)
        this->hitboxComponents->render(target);
}

void Player::initAudio() {
    this->swordSoundBF.loadFromFile("resources/Audio/swordswing.wav");
    this->swordSound.setBuffer(swordSoundBF);

}

void Player::updateJumping(const float& dt) {
    if (this->movementComponents->getVelocity().y != 0)
    {
        this->isJump = true;
    }
    else {
        this->isJump = false;

    }

}

