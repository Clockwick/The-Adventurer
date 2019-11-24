//
// Created by Paratthakorn Sribunyong on 2/9/2019 AD.
//

#include "Entity.h"


Entity::Entity() {

    this->initVariables();
}

Entity::~Entity() {
    delete this->movementComponents;
    delete this->animationComponents;
    delete this->hitboxComponents;
    delete this->attributeComponents;
    delete this->skillComponents;
}

void Entity::initVariables() {
    this->movementComponents = NULL;
    this->animationComponents = NULL;
    this->hitboxComponents = NULL;
    this->attributeComponents = NULL;
    this->skillComponents = NULL;
}

void Entity::move(const float dir_x, const float dir_y, const float& dt) {
    if(this->movementComponents)
    {
        this->movementComponents->move(dir_x,dir_y, dt);

    }
//    if (this->skillComponents) {
//        this->skillComponents->gainExp(SKILLS::ENDURANCE, 1);
//    }

}
//Component Functions
void Entity::setTexture(sf::Texture& texture) {
    this->sprite.setTexture(texture);

}

void Entity::setPosition(const float x, const float y) {
    if (this->hitboxComponents)
        this->hitboxComponents->setPosition(x, y);
    else
        this->sprite.move(x , y);

}

void Entity::createMovementComponents(const float maxVelocity, const float acceleration, const float deceleration , const float& jumpHeight) {

    this->movementComponents = new MovementComponents(this->sprite, maxVelocity, acceleration, deceleration , jumpHeight);

}

void Entity::createAnimationComponents(sf::Texture &texture_sheet) {
    this->animationComponents = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponents(sf::Sprite& sprite, float offset_x,
                                    float offset_y, float width, float height, short type) {
    this->hitboxComponents = new HitboxComponent(sprite, offset_x,offset_y, width, height, type);
}

void Entity::createAttributeComponents(int level, int hp) {
    this->attributeComponents = new AttributeComponent(level, hp);
}
void Entity::createSkillComponents() {
    this->skillComponents = new SkillComponent();
}


const sf::Vector2f &Entity::getPosition() const {
    if (this->hitboxComponents)
        return this->hitboxComponents->getPosition();
    return this->sprite.getPosition();
}

const sf::FloatRect Entity::getGlobalBounds() const {
    if (this->hitboxComponents)
        this->hitboxComponents->getGlobalBounds();
    return this->sprite.getGlobalBounds();
}

void Entity::stopVelocity() {
    if (this->movementComponents)
        this->movementComponents->stopVelocity();
}

void Entity::stopVelocityX() {
    if (this->movementComponents)
        this->movementComponents->stopVelocityX();
}

void Entity::stopVelocityY() {
    if (this->movementComponents)
        this->movementComponents->stopVelocityY();
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const {
    if (this->hitboxComponents)
        return sf::Vector2i(
                static_cast<int>(this->hitboxComponents->getPosition().x) / gridSizeI ,
                static_cast<int>(this->hitboxComponents->getPosition().y) / gridSizeI
        );
    return sf::Vector2i(
            static_cast<int>(this->sprite.getPosition().x) / gridSizeI ,
            static_cast<int>(this->sprite.getPosition().y) / gridSizeI
    );
}

const sf::FloatRect &Entity::getNextPositionBounds(const float& dt) const {
    if (this->hitboxComponents && this->movementComponents)
        return this->hitboxComponents->getNextPosition(this->movementComponents->getVelocity() * dt);

    return sf::FloatRect(1,1,1,1);
}

void Entity::jump() {
    if (this->movementComponents && this->canJump) {
        this->canJump = false;
        this->movementComponents->getcanJump(&this->canJump);
        this->movementComponents->jump();
    }
}

void Entity::allowJump(bool *canJump) {
    this->canJump = *canJump;

}

MovementComponents* Entity::getMovementComponents() {
    return nullptr;
}

bool Entity::getAttack() {
    return false;

}

bool Entity::getAttack1() {
    return false;
}

bool Entity::getAttack2() {
    return false;
}











