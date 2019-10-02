//
// Created by Paratthakorn Sribunyong on 2/10/2019 AD.
//

#include "HitboxComponent.h"

HitboxComponents::HitboxComponents(sf::Sprite& sprite,float offset_x, float offset_y, float width, float height)
: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
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

bool HitboxComponents::checkIntersect(const sf::FloatRect& frect) {

    return this->hitbox.getGlobalBounds().intersects(frect);
}
