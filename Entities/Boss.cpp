//
// Created by Paratthakorn Sribunyong on 22/11/2019 AD.
//

#include "Boss.h"

Boss::Boss(float x, float y, const float &jumpHeight, sf::Texture &texture_sheet)
        : Enemy(), jumpHeight(jumpHeight)
{
    this->initVariables();
    this->initAudio();


    this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f,HitTypes::ATTACK_COL);
    this->createMovementComponents(100, 1000.0f, 250.0f, this->jumpHeight);
    this->createAttributeComponents(20);
    this->createSkillComponents();
    this->createAnimationComponents(texture_sheet);
    this->initAnimation();
    this->setPosition(x, y);
}

Boss::~Boss() {

}
//Initializer Function

void Boss::initVariables() {
    this->attacking = false;
    this->isJump = false;
    this->canJump = true;
    this->isAttacked = false;
}

void Boss::initAnimation() {
    this->animationComponents->addAnimation("IDLE", 25.f, 0 , 0, 8, 0, 100, 74);
    this->animationComponents->addAnimation("RUN", 15.f, 0, 1, 7, 1, 100, 74);
    
}


void Boss::update(const float &dt) {
    this->updateHit();
    this->updateMoving(dt);
    this->updateJumping(dt);
    this->movementComponents->update(dt);
    this->updateAnimation(dt);

}

void Boss::render(sf::RenderTarget &target, const bool show_hitbox) {

    target.draw(this->sprite);
    if (show_hitbox)
        this->hitboxComponents->render(target);
}

void Boss::initAudio() {

}

void Boss::updateAnimation(const float &dt) {
//    std::cout << this->isAttacked << std::endl;


    if (this->movementComponents->getState(IDLE) && !this->isJump) {
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f, HitTypes::ATTACK_COL);
        this->animationComponents->play("IDLE", dt);

    }  else if (this->movementComponents->getState(MOVING_RIGHT) && this->canJump) {
        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f, HitTypes::ATTACK_COL);
        this->animationComponents->play("RUN", dt, this->movementComponents->getVelocity().x,
                                        this->movementComponents->getMaxVelocity());
    } else if (this->movementComponents->getState(MOVING_LEFT) && this->canJump) {
        this->sprite.setOrigin(100.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f, HitTypes::ATTACK_COL);
        this->animationComponents->play("RUN", dt, this->movementComponents->getVelocity().x,
                                        this->movementComponents->getMaxVelocity());
    }
    if (!this->canJump && this->movementComponents->getState(JUMP_LEFT)) {
        this->sprite.setOrigin(100.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);
        this->animationComponents->play("JUMP", dt);
    } else if (!this->canJump && this->movementComponents->getState(JUMP_RIGHT)) {
        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->animationComponents->play("JUMP", dt);
    }

    this->hitboxComponents->update();

}
void Boss::updateJumping(const float& dt) {
    this->isJump = this->movementComponents->getVelocity().y != 0;
//    std::cout << this->getVelocity().x << std::endl;

}
const bool Boss::intersects(const sf::FloatRect bounds) const
{
    return this->sprite.getGlobalBounds().intersects(bounds);
}

void Boss::gotAttackLeft() {
//    this->getVelocity().x += 5;
////    if (this->getVelocity().x <= 0.f)
////        this->getVelocity().x = 0.f;
////    if (this->getVelocity().x >= 4.f)
////        this->getVelocity().x = 4.f;
//    this->getVelocity().y = 10 * abs(-pow(this->getVelocity().x - 2,2)+4);
    this->isAttacked = true;
    this->getVelocity().x -= 100.0f;
    this->jump();

}
void Boss::gotAttackRight() {
//    this->getVelocity().x -= 5;
////    if (this->getVelocity().x <= -4.f)
////        this->getVelocity().x = -4.f;
////    if (this->getVelocity().x >= 0.f)
////        this->getVelocity().x = 0.f;
//    this->getVelocity().y = 10 * abs(-pow(this->getVelocity().x + 2,2)+4);
    this->isAttacked = true;
    this->getVelocity().x += 100.0f;
    this->jump();
}
void Boss::gainHP(const int hp) {
    this->attributeComponents->hp += hp;

    if (this->attributeComponents->hp > this->attributeComponents->hpMax)
        this->attributeComponents->hp = this->attributeComponents->hpMax;
}

void Boss::loseHP(const int hp) {

    if (this->isAttacked)
    {
        this->attributeComponents->hp -= hp;
    }


    if (this->attributeComponents->hp < 0)
        this->attributeComponents->hp = 0;

}

AttributeComponent *Boss::getAttributeComponents() {
    return this->attributeComponents;
}

MovementComponents *Boss::getMovementComponents() {
    return this->movementComponents;
}

void Boss::updateMoving(const float &dt) {
    this->sprite.move(this->getVelocity() * dt);

}

void Boss::updateHit() {
    this->delayAttackedTime = this->delayAttackedClock.getElapsedTime().asSeconds();
//    std::cout << this->delayAttackedTime << "\n";
    {
        if (this->delayAttackedTime > 0.01f)
        {
            this->isAttacked = false;
            this->delayAttackedClock.restart();
        }

    }
}



