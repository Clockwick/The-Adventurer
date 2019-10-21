//
// Created by Paratthakorn Sribunyong on 2/10/2019 AD.
//

#include "HitboxComponent.h"

HitboxComponents::HitboxComponents(sf::Sprite& sprite,float offset_x, float offset_y, float width, float height)
: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
    this->nextPosition.left = 0.f;
    this->nextPosition.top = 0.f;
    this->nextPosition.width = width;
    this->nextPosition.height= height;

    this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
    this->hitbox.setSize(sf::Vector2f(width, height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(1.f);
    this->hitbox.setOutlineColor(sf::Color::Red);

}

HitboxComponents::~HitboxComponents()
{

}

void HitboxComponents::render(sf::RenderTarget &target) {
    target.draw(this->hitbox);
}

void HitboxComponents::update() {
    this->hitbox.setPosition(this->sprite.getPosition().x + offsetX, this->sprite.getPosition().y + offsetY);
}
bool HitboxComponents::Intersect(const sf::FloatRect& frect) {

    return this->hitbox.getGlobalBounds().intersects(frect);
}
//Accessors
const sf::Vector2f& HitboxComponents::getPosition() const {
    return this->hitbox.getPosition();
}

//Modifiers
void HitboxComponents::setPosition(sf::Vector2f& position) {
    this->hitbox.setPosition(position);
    this->sprite.setPosition(position.x - offsetX, position.y - offsetY);

}

void HitboxComponents::setPosition(const float x, const float y) {

    this->hitbox.setPosition(x, y);
    this->sprite.setPosition(x - offsetX, y - offsetY);

}

const sf::FloatRect HitboxComponents::getGlobalBounds() const {
    return this->hitbox.getGlobalBounds();
}

const sf::FloatRect &HitboxComponents::getNextPosition(const sf::Vector2f &velocity) {
    this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
    this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;
    return this->nextPosition;
}
