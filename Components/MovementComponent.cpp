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
    /* Set Maximum Velocity and Deceleration */
    /* X-axis */
    if (this->velocity.x > 0.0f)
    {

        if (this->velocity.x > this->maxVelocity) {
            this->velocity.x = this->maxVelocity;
        }
        this->velocity.x -= this->deceleration;
        if (this->velocity.x < 0.0f)
        {
            this->velocity.x = 0;
        }
    }
    else if (this->velocity.x < 0.0f) {
        if (this->velocity.x < -this->maxVelocity)
        {
            this->velocity.x = -this->maxVelocity;
        }
        this->velocity.x += this->deceleration;
        if (this->velocity.x > 0.0f)
        {
            this->velocity.x = 0;
        }
    }
    /* Y-axis */
    if (this->velocity.y > 0.0f) {
        if(this->velocity.y > this->maxVelocity)
        {
            this->velocity.y = this->maxVelocity;
        }
        this->velocity.y -= this->deceleration;
        if (this->velocity.y < 0.0f) {
            this->velocity.y = 0.0f;
        }
    }
    else if (this->velocity.y < 0.0f)
    {
        if (this->velocity.y < -this->maxVelocity)
        {
            this->velocity.y = -this->maxVelocity;
        }
        this->velocity.y += this->deceleration;
        if (this->velocity.y > 0.0f)
        {
            this->velocity.y = 0.0f;
        }
    }
    //Final move
    this->sprite.move(this->velocity * dt);
}

void MovementComponents::move(const float dir_x, const float dir_y, const float& dt) {
    //Acceleration
    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->acceleration * dir_y;




}

const sf::Vector2f &MovementComponents::getVelocity( ) const {
   return this->velocity;
}

const bool MovementComponents::idle() const {
    return false;
}

const bool MovementComponents::moving() const {
    return false;
}

const bool MovementComponents::leftMoving() const {
    return 0;
}

const bool MovementComponents::slide() const {
    return 0;
}
const bool MovementComponents::standstill() const {
    if (this->velocity.x == 0.f && this->velocity.y == 0.f)
        return true;
    return false;
}
const bool MovementComponents::isSit() const {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        return true;
    return 0;
}
const float &MovementComponents::getMaxVelocity() const {
    return this->maxVelocity;
}


const bool MovementComponents::getState(const short unsigned state) const {
    switch (state)
    {
        case IDLE:
            if (standstill() && !isSit())
                return true;

            break;
        case MOVING:

            if (this->velocity.x != 0.f || this->velocity.y != 0.f)
                return true;
            break;

        case MOVING_LEFT:
            if (this->velocity.x < 0.f)
                return true;

            break;
        case MOVING_RIGHT:
            if (this->velocity.x > 0.f)
                return true;

            break;
        case SIT:
            if (isSit() && standstill())
                return true;
            break;
        case SLIDE_RIGHT:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->velocity.x > 0.f)
                return true;

            break;
        case SLIDE_LEFT:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->velocity.x < 0.f)
                return true;
            break;
        case ATTACK:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                return true;
            break;
    }
    return false;
}

void MovementComponents::stopVelocity() {
    //Stop velocity
    this->velocity.x = 0.f;
    this->velocity.y = 0.f;
}

void MovementComponents::stopVelocityX() {
    this->velocity.x = 0.f;
}

void MovementComponents::stopVelocityY() {
    this->velocity.y = 0.f;
}




