#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>




#ifndef GUJARUNSFML_MOVEMENTCOMPONENTS_H
#define GUJARUNSFML_MOVEMENTCOMPONENTS_H

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, SLIDE_RIGHT, SLIDE_LEFT, SIT, ATTACK,ATTACK1, ATTACK2, JUMP_LEFT, JUMP_RIGHT};
class MovementComponents
{
public:

    MovementComponents(sf::Sprite& sprite, float maxVelocity, float accerelation, float deceleration, const float& jumpHeight);
    virtual ~MovementComponents();


    //functions
    void update(const float& dt);
    void move(const float x, const float y, const float& dt);
    const sf::Vector2f& getVelocity() const;
    const float& getMaxVelocity() const;
    const bool getState(const short unsigned state) const;
    const bool standstill() const;
    const bool isSit() const;
    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();
    void jump();
    void getcanJump(bool* canJump);
private:
    float maxVelocity;
    float acceleration;
    float deceleration;
    const float jumpHeight;
    const float maxVelocityY = -300.f;
    bool canJump;
    bool faceRight;


    sf::Sprite& sprite;
    sf::Vector2f velocity;


    //Initializer functions



};
#endif //GUJARUNSFML_MOVEMENTCOMPONENTS_H
