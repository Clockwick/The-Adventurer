//
// Created by Paratthakorn Sribunyong on 17/11/2019 AD.
//

#include "Items.h"

Item::Item(float x, float y, sf::Texture& texture_sheet) {
    this->initVariables();
    this->createHitboxComponents(this->sprite, 20.f, 10.f, 55.f, 65.f);
//    this->createMovementComponents(300, 1500.0f, 500.0f, 0);
    this->createAnimationComponents( texture_sheet);
    this->animationComponents->getptr(&this->isJump);
    this->setPosition(x, y);
    this->initAnimations();

}

Item::~Item() {

}
void Item::initAnimations() {
    this->animationComponents->addAnimation("DROP", 100.f, 0, 0, 1, 0, 100, 74);

}

void Item::initVariables() {
//    this->isJump = false;

}

void Item::update(const float &dt) {
//    this->updateJumping(dt);
//    this->movementComponents->update(dt);
    this->updateAnimations(dt);
}

void Item::render(sf::RenderTarget &target, const bool show_hitbox) {
    target.draw(this->sprite);
    if (show_hitbox)
        this->hitboxComponents->render(target);
}

void Item::updateAnimations(const float &dt) {

    this->animationComponents->play("DROP", dt);
    this->createHitboxComponents(this->sprite,20.f, 10.f, 55.f, 65.f);

    this->hitboxComponents->update();

}
void Item::updateJumping(const float& dt) {
    this->isJump = this->movementComponents->getVelocity().y != 0;
//    std::cout << this->getVelocity().x << std::endl;

}
const bool Item::intersects(const sf::FloatRect bounds) const
{
    return this->sprite.getGlobalBounds().intersects(bounds);
}






