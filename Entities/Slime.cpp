#include "Slime.h"

Slime::Slime(float x, float y, const float &jumpHeight, sf::Texture &texture_sheet)
: Enemy(), jumpHeight(jumpHeight)
{
    this->initVariables();
    this->initAudio();


    this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f,HitTypes::ATTACK_COL);
    this->createMovementComponents(100, 1000.0f, 250.0f, this->jumpHeight);
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
    this->animationComponents->addAnimation("IDLE", 25.f, 0 , 1, 1, 1, 100, 74);
    this->animationComponents->addAnimation("RUN", 15.f, 0, 0, 3, 0, 100, 74);
    this->animationComponents->addAnimation("JUMP", 17.f, 0, 2, 8, 2, 100, 74);
}


void Slime::update(const float &dt) {
    this->updateMoving(dt);
    this->updateJumping(dt);
    this->movementComponents->update(dt);
    this->updateAnimation(dt);

}

void Slime::render(sf::RenderTarget &target, const bool show_hitbox) {

    target.draw(this->sprite);
    if (show_hitbox)
        this->hitboxComponents->render(target);
}

void Slime::initAudio() {

}

void Slime::updateAnimation(const float &dt) {


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
void Slime::updateJumping(const float& dt) {
    this->isJump = this->movementComponents->getVelocity().y != 0;
    std::cout << this->getVelocity().x << std::endl;

}
const bool Slime::intersects(const sf::FloatRect bounds) const
{
    return this->sprite.getGlobalBounds().intersects(bounds);
}

void Slime::gotAttackLeft() {
//    this->getVelocity().x += 5;
////    if (this->getVelocity().x <= 0.f)
////        this->getVelocity().x = 0.f;
////    if (this->getVelocity().x >= 4.f)
////        this->getVelocity().x = 4.f;
//    this->getVelocity().y = 10 * abs(-pow(this->getVelocity().x - 2,2)+4);
    this->getVelocity().x -= 100.0f;
    this->jump();
}

void Slime::gotAttackRight() {
//    this->getVelocity().x -= 5;
////    if (this->getVelocity().x <= -4.f)
////        this->getVelocity().x = -4.f;
////    if (this->getVelocity().x >= 0.f)
////        this->getVelocity().x = 0.f;
//    this->getVelocity().y = 10 * abs(-pow(this->getVelocity().x + 2,2)+4);
    this->getVelocity().x += 100.0f;
    this->jump();
}
void Slime::gainHP(const int hp) {
    this->attributeComponents->hp += hp;

    if (this->attributeComponents->hp > this->attributeComponents->hpMax)
        this->attributeComponents->hp = this->attributeComponents->hpMax;
}

void Slime::loseHP(const int hp) {
    this->attributeComponents->hp -= hp;

    if (this->attributeComponents->hp < 0)
        this->attributeComponents->hp = 0;

}

AttributeComponent *Slime::getAttributeComponents() {
    return this->attributeComponents;
}

MovementComponents *Slime::getMovementComponents() {
    return this->movementComponents;
}

void Slime::updateMoving(const float &dt) {
    this->sprite.move(this->getVelocity() * dt);

}

