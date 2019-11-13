#include "Slime.h"

Slime::Slime(float x, float y, const float &jumpHeight, sf::Texture &texture_sheet)
: Enemy()
{
    this->initVariables();
    this->initAudio();

    this->createMovementComponents(300, 1500.0f, 500.0f, this->jumpHeight);
    this->createAttributeComponents(1);
    this->createSkillComponents();
    this->createAnimationComponents(texture_sheet);
    this->initAnimation();
    this->setPosition(x, y);
}

Slime::~Slime() {

}
//Initializer Function

void Slime::initVariables() {
    this->attacking = false;
    this->isJump = false;
    this->canJump = true;
}

void Slime::initAnimation() {
    this->animationComponents->addAnimation("IDLE", 25.f, 0 , 1, 1, 1, 90, 90);
    this->animationComponents->addAnimation("RUN", 15.f, 0, 0, 3, 0, 90, 90);
}


void Slime::update(const float &dt) {
    this->movementComponents->update(dt);
    this->updateAnimation(dt);
    this->hitboxComponents->update();
}

void Slime::render(sf::RenderTarget &target, const bool show_hitbox) {

    if (show_hitbox)
        this->hitboxComponents->render(target);
    else
        target.draw(this->sprite);
}

void Slime::initAudio() {

}

void Slime::updateAnimation(const float &dt) {
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
