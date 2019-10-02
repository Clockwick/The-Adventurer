#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>


#ifndef GUJARUNSFML_MOVEMENTCOMPONENTS_H
#define GUJARUNSFML_MOVEMENTCOMPONENTS_H

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, SLIDE};
class MovementComponents
{
public:

    MovementComponents(sf::Sprite& sprite, float maxVelocity, float accerelation, float deceleration);
    virtual ~MovementComponents();


    //functions
    void update(const float& dt);
    void move(const float x, const float y, const float& dt);
    const sf::Vector2f& getVelocity() const;
    const bool getState(const short unsigned state) const;
    const bool idle() const;
    const bool moving() const;
    const bool leftMoving() const;
    const bool rightMoving() const;
    const bool slide() const;

private:
    float maxVelocity;
    float acceleration;
    float deceleration;


    sf::Sprite& sprite;
    sf::Vector2f velocity;


    //Initializer functions



};
#endif //GUJARUNSFML_MOVEMENTCOMPONENTS_H
