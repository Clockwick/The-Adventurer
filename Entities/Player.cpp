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
    this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
    this->createMovementComponents(300, 1500.0f, 500.0f, this->jumpHeight);
    this->createAnimationComponents( texture_sheet);
    this->createAttributeComponents(1);
    this->createSkillComponents();
    this->animationComponents->getptr(&this->isJump);
    this->setPosition(x , y);
    this->initAnimation();

}

Player::~Player() {


}
//Initializer Function


void Player::initVariables() {
    this->attackType = ATTACK_TYPE::EARTH;
    this->attacking = false;
    this->attacking1 = false;
    this->attacking2 = false;
    this->sliding = false;
    this->sitting = false;
    this->isJump = true;
    this->canJump = true;
    this->playSound = true;
    this->type = HitTypes::DEFAULT_COL;
}
void Player::initAnimation() {

    this->animationComponents->addAnimation("IDLE", 15.f, 0, 0, 3, 0, 100, 74);
    this->animationComponents->addAnimation("RUN", 15.f, 0, 1, 5, 1, 100, 74);
    this->animationComponents->addAnimation("SLIDE", 15.f, 0, 3, 3, 3, 100, 74);
    this->animationComponents->addAnimation("SIT", 15.f, 4, 0, 6, 0, 100, 74);
    this->animationComponents->addAnimation("ATTACK1", 13.f, 0, 6, 6, 6, 100, 74);
    this->animationComponents->addAnimation("ATTACK2", 17.f, 0, 7, 3, 7, 100, 74);
    this->animationComponents->addAnimation("ATTACK3", 12.f, 0, 8, 5, 8, 100 , 74);
    this->animationComponents->addAnimation("JUMP", 15.f , 0 , 2, 13 , 2 , 100 , 74);
    this->animationComponents->addAnimation("Dead", 25.f , 0 ,9, 9 , 9, 100, 74);
}


void Player::update(const float& dt)
{
    this->updateJumping(dt);
    this->movementComponents->update(dt);
    this->attributeComponents->update();
    this->updateAttack();
    this->updateAnimation(dt);

//    std::cout << this->movementComponents->getVelocity().y << "\n";

}

void Player::updateAttack()
{
    if(this->movementComponents->getState(ATTACK) && !this->sliding && !this->isJump && this->getMovementComponents()->faceRight) {
        this->type = HitTypes::ATTACK_COL;
        this->attacking = true;
        if (this->playSound)
            this->burnSound.play();
        this->createHitboxComponents(this->sprite,20.f,10.f,80.f,65.f, this->type); // Attack type
    }
    else if (this->movementComponents->getState(ATTACK) && !this->sliding && !this->isJump && !this->getMovementComponents()->faceRight)
    {
        this->type = HitTypes::ATTACK_COL;
        this->attacking = true;
        if (this->playSound)
            this->burnSound.play();
        this->createHitboxComponents(this->sprite,-5.f,10.f,80.f,65.f, this->type); // Modify

    }
    if (this->movementComponents->getState(ATTACK1) && !this->sliding&& !this->isJump && this->getMovementComponents()->faceRight)
    {
        this->type = HitTypes::ATTACK_COL;
        this->attacking1 = true;
        if (this->playSound)
            this->burnSound.play();
        this->createHitboxComponents(this->sprite,20.f,10.f,80.f,65.f, this->type);// Attack type
    }
    else if (this->movementComponents->getState(ATTACK1) && !this->sliding&& !this->isJump && !this->getMovementComponents()->faceRight)
    {
        this->type = HitTypes::ATTACK_COL;
        this->attacking1 = true;
        if (this->playSound)
            this->burnSound.play();
        this->createHitboxComponents(this->sprite,-5.f,10.f,80.f,65.f, this->type);// Modify
    }
    if (this->movementComponents->getState(ATTACK2) && !this->sliding&& !this->isJump&& this->getMovementComponents()->faceRight)
    {
        this->type = HitTypes::ATTACK_COL;
        this->attacking2 = true;
        if (this->playSound)
            this->burnSound.play();
        this->createHitboxComponents(this->sprite,20.f,10.f,80.f,65.f, this->type);// Attack type
    }
    if (this->movementComponents->getState(ATTACK2) && !this->sliding&& !this->isJump&& !this->getMovementComponents()->faceRight)
    {
        this->type = HitTypes::ATTACK_COL;
        this->attacking2 = true;
        if (this->playSound)
            this->burnSound.play();
        this->createHitboxComponents(this->sprite,-5.f,10.f,80.f,65.f, this->type);// Modify
    }


}

void Player::updateAnimation(const float &dt)
{

    if (this->attacking && !this->isJump)
    {
        this->movementComponents->stopVelocityX();

        if(this->animationComponents->play("ATTACK1", dt))
        {
            this->attacking = false;
            this->playSound = true;
        }
        else
            this->playSound = false;

    }

    else if (this->attacking1 && !this->isJump)
    {
        this->movementComponents->stopVelocityX();
        if (this->animationComponents->play("ATTACK2", dt))
        {
            this->attacking1 = false;
            this->playSound = true;
        }
        else
            this->playSound = false;

    }
    else if (this->attacking2 && !this->isJump)
    {
        this->movementComponents->stopVelocityX();
        if (this->animationComponents->play("ATTACK3", dt)) {
            this->attacking2 = false;
            this->playSound = true;
        }
        else
            this->playSound = false;
    }
    if (this->movementComponents->getState(IDLE) && !this->isJump && !this->attacking && !this->attacking1 && !this->attacking2)
    {
        this->type = HitTypes::DEFAULT_COL;
        this->sliding = false;
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("IDLE", dt);

    }

    else if (this->movementComponents->getState(SLIDE_RIGHT) && this->canJump && !this->attacking && !this->attacking1 && !this->attacking2)
    {
        this->type = HitTypes::DEFAULT_COL;
        this->sliding = true;
        this->sprite.setOrigin(0.f,0.f);
        this->sprite.setScale(1.f,1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("SLIDE", dt);
    }

    else if (this->movementComponents->getState(SLIDE_LEFT) && this->canJump && !this->attacking && !this->attacking1 && !this->attacking2)
    {
        this->type = HitTypes::DEFAULT_COL;
        this->sliding = true;
        this->sprite.setOrigin(100.f,0.f);
        this->sprite.setScale(-1.f,1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("SLIDE", dt);
    }
    else if (this->movementComponents->getState(MOVING_RIGHT) && this->canJump)
    {
        this->type = HitTypes::DEFAULT_COL;
        this->sliding = false;
        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("RUN", dt, this->movementComponents->getVelocity().x,
                                        this->movementComponents->getMaxVelocity());
    }
    else if (this->movementComponents->getState(MOVING_LEFT) && this->canJump) {
        this->type = HitTypes::DEFAULT_COL;
        this->sliding = false;
        this->sprite.setOrigin(100.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("RUN", dt, this->movementComponents->getVelocity().x,
                                        this->movementComponents->getMaxVelocity());
    }
    else if (this->movementComponents->getState(SIT) && this->canJump && !this->attacking && !this->attacking1 && !this->attacking2)
    {
        this->type = HitTypes::DEFAULT_COL;
        this->sliding = false;
        this->sitting = true;
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("SIT", dt);
    }
    if (!this->canJump && this->movementComponents->getState(ATTACK))
    {
        this->movementComponents->stopVelocityX();
        this->type = HitTypes::ATTACK_COL;
    }
    else if (!this->canJump && this->movementComponents->getState(JUMP_LEFT)) {
        this->type = HitTypes::DEFAULT_COL;
        this->sliding = false;
        this->sprite.setOrigin(100.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);
        this->animationComponents->play("JUMP", dt, 135, 100);
    }
    else if (!this->canJump && this->movementComponents->getState(JUMP_RIGHT)) {
        this->type = HitTypes::DEFAULT_COL;
        this->sliding = false;
        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->animationComponents->play("JUMP", dt, 120, 100);
    }

//    std::cout << this->movementComponents->getState(ATTACK) << "\n";
    this->hitboxComponents->update();

}

void Player::render(sf::RenderTarget& target, const bool show_hitbox) {
    target.draw(this->sprite);
    if (show_hitbox)
        this->hitboxComponents->render(target);


}

void Player::initAudio() {
    this->swordSoundBF.loadFromFile("resources/Audio/swordswing.wav");
    this->swordSound.setBuffer(swordSoundBF);

    //FIRE
    this->burnSoundBuffer.loadFromFile("resources/Audio/burning.wav");
    this->burnSound.setBuffer(this->burnSoundBuffer);
    this->burnSound.setVolume(50.f);

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

bool Player::getAttack() {
    return this->attacking;
}
bool Player::getAttack1() {
    return this->attacking1;
}
bool Player::getAttack2() {
    return this->attacking2;
}

void Player::gotAttackLeft(const float velocity, const float& dt) {

}

void Player::gotAttackRight(const float velocity, const float& dt) {


}

void Player::setColor(sf::Color color) {
    this->sprite.setColor(color);

}

const short &Player::getType() const {
    return this->type;
}

MovementComponents *Player::getMovementComponents() {
    return this->movementComponents;
}

AnimationComponent *Player::getAnimationComponents() {
    return this->animationComponents;
}

const bool &Player::getJump() const {
    return this->isJump;

}

void Player::changeAttackType(const short& attack_type) {
    this->attackType = attack_type;

}

const short &Player::getAttackType() const {
    return this->attackType;
}










