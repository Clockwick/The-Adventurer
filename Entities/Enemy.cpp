
#include "Enemy.h"
#include "../Items/Items.h"

//Constructor , DeConstructor
Enemy::Enemy()
{


}

Enemy::~Enemy() {


}

void Enemy::setColor(sf::Color color)
{
    this->sprite.setColor(color);
}

void Enemy::gainHP(const int hp) {

}

void Enemy::loseHP(const int hp) {

}

AttributeComponent *Enemy::getAttributeComponents() {
    return nullptr;
}

void Enemy::dropItem() {


}



