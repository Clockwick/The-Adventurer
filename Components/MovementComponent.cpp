//
// Created by Paratthakorn Sribunyong on 7/9/2019 AD.
//

#include "MovementComponent.h"

MovementComponents::MovementComponents(sf::Sprite& sprite, float maxVelocity, float accerelation, float deceleration)
: sprite(sprite),maxVelocity(maxVelocity), acceleration(accerelation), deceleration(deceleration)
{

}

MovementComponents::~MovementComponents() {

}

void MovementComponents::update(const float &dt) {
    //Deceleration

    if (this->velocity.x > 0.0f)
    {
        this->velocity.x -= this->deceleration;
        if (this->velocity.x < 0.0f)
        {
            this->velocity.x = 0;
        }
    }
    else if (this->velocity.x < 0.0f) {
        this->velocity.x += this->deceleration;
        if (this->velocity.x > 0.0f)
        {
            this->velocity.x = 0;
        }
    }

    //Final move
    this->sprite.move(this->velocity * dt);
}

void MovementComponents::move(const float dir_x, const float dir_y, const float& dt) {
    //Acceleration
    this->velocity.x += this->acceleration * dir_x;

    if (this->velocity.x > 0.0f) {
        if (this->velocity.x > this->maxVelocity) {
            this->velocity.x = this->maxVelocity;
        }
    }
    else if (this->velocity.x < 0.0f)
    {
        if (this->velocity.x < -this->maxVelocity)
        {
            this->velocity.x = -this->maxVelocity;
        }

    }

    this->velocity.y += this->acceleration * dir_y;




}

const sf::Vector2f &MovementComponents::getVelocity( ) const {
   return this->velocity;
}