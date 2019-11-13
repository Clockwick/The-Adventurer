//
// Created by Paratthakorn Sribunyong on 12/11/2019 AD.
//

#include "Enemy.h"

//Constructor , DeConstructor
Enemy::Enemy( float x, float y, const float &jumpHeight, sf::Texture &texture_sheet)
: jumpHeight(jumpHeight) {

    this->initVariables();
    this->initAudio();

    this->createMovementComponents(300, 1500.0f, 500.0f, this->jumpHeight);
    this->createAttributeComponents(1);
    this->createSkillComponents();
    this->createAnimationComponents(texture_sheet);
    this->initAnimation();
    this->setPosition(x, y);

}

Enemy::~Enemy() {


}
//Initializer Function


void Enemy::initVariables() {
    this->attacking = false;
    this->isJump = false;
    this->canJump = true;
}

void Enemy::initAnimation() {
    this->animationComponents->addAnimation("IDLE", 25.f, 0 , 1, 1, 1, 90, 90);
    this->animationComponents->addAnimation("RUN", 15.f, 0, 0, 3, 0, 90, 90);
}


void Enemy::update(const float &dt) {
    this->movementComponents->update(dt);
    this->updateAnimation(dt);
    this->hitboxComponents->update();
}

void Enemy::render(sf::RenderTarget &target, const bool show_hitbox) {

    if (show_hitbox)
        this->hitboxComponents->render(target);
    else
        target.draw(this->sprite);
}

void Enemy::initAudio() {

}

void Enemy::updateAnimation(const float &dt) {
    if (this->attacking && this->canJump) {

        if (this->animationComponents->play("ATTACK1", dt, true))
            this->attacking = false;

    }
    if (this->movementComponents->getState(IDLE) && !this->isJump) {
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("IDLE", dt);

    }  else if (this->movementComponents->getState(MOVING_RIGHT) && this->canJump) {
        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("RUN", dt, this->movementComponents->getVelocity().x,
                                        this->movementComponents->getMaxVelocity());
    } else if (this->movementComponents->getState(MOVING_LEFT) && this->canJump) {
        this->sprite.setOrigin(100.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);
        this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
        this->animationComponents->play("RUN", dt, this->movementComponents->getVelocity().x,
                                        this->movementComponents->getMaxVelocity());
    }
//     else if (!this->canJump && this->movementComponents->getState(JUMP_LEFT)) {
//        this->sprite.setOrigin(100.f, 0.f);
//        this->sprite.setScale(-1.f, 1.f);
//        this->animationComponents->play("JUMP", dt, 135, 100);
//    } else if (!this->canJump && this->movementComponents->getState(JUMP_RIGHT)) {
//        this->sprite.setOrigin(0.f, 0.f);
//        this->sprite.setScale(1.f, 1.f);
//        this->animationComponents->play("JUMP", dt, 120, 100);
//    }

    this->hitboxComponents->update();

}
