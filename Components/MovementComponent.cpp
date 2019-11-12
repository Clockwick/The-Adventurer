//
// Created by Paratthakorn Sribunyong on 7/9/2019 AD.
//

#include "MovementComponent.h"

MovementComponents::MovementComponents(sf::Sprite &sprite, float maxVelocity, float accerelation, float deceleration,
                                       const float &jumpHeight)
        : sprite(sprite), maxVelocity(maxVelocity), acceleration(accerelation), deceleration(deceleration),
          jumpHeight(jumpHeight) {


}

MovementComponents::~MovementComponents() {

}

void MovementComponents::update(const float &dt) {
    /* Set Maximum Velocity and Deceleration */
    /* X-axis */

    if (this->velocity.x > 0.0f) {
        this->faceRight = true;
        if (this->velocity.x > this->maxVelocity) {
            this->velocity.x = this->maxVelocity;
        }
        this->velocity.x -= this->deceleration * dt;
        if (this->velocity.x < 0.0f) {
            this->velocity.x = 0;
        }
    } else if (this->velocity.x < 0.0f) {
        this->faceRight = false;
        if (this->velocity.x < -this->maxVelocity) {
            this->velocity.x = -this->maxVelocity;
        }
        this->velocity.x += this->deceleration * dt;
        if (this->velocity.x > 0.0f) {
            this->velocity.x = 0;
        }
    }
    if (!this->canJump && this->velocity.y != 0 && this->sprite.getPosition().y < 465) {
        this->velocity.y += 981.f * dt;
    } else if (!this->canJump && this->sprite.getPosition().y < 465) {
        this->velocity.y += 981.f * dt;
    } else {
    }
//    std::cout << this->sprite.getPosition().y << std::endl;


    //Final move
    this->sprite.move(this->velocity * dt);
}

void MovementComponents::move(const float dir_x, const float dir_y, const float &dt) {
    //Acceleration
    this->velocity.x += this->acceleration * dir_x * dt;


}

const sf::Vector2f &MovementComponents::getVelocity() const {
    return this->velocity;
}

const bool MovementComponents::standstill() const {
    return this->velocity.x == 0.f;
}

const bool MovementComponents::isSit() const {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return true;
    return 0;
}

const float &MovementComponents::getMaxVelocity() const {
    return this->maxVelocity;
}


const bool MovementComponents::getState(const short unsigned state) const {
    switch (state) {
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->velocity.x > 0.f)
                return true;

            break;
        case SLIDE_LEFT:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->velocity.x < 0.f)
                return true;
            break;
        case ATTACK:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                return true;
            break;
        case JUMP_RIGHT:
            if (!this->canJump && this->faceRight)
                return true;
            break;
        case JUMP_LEFT:
            if (!this->canJump && !this->faceRight)
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

void MovementComponents::jump() {

    this->velocity.y = -sqrtf(2 * 981.f * this->jumpHeight);
}

void MovementComponents::getcanJump(bool *canJump) {
    this->canJump = *canJump;
}








