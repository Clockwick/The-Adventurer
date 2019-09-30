//
// Created by Paratthakorn Sribunyong on 2/9/2019 AD.
//
#include "../Components/MovementComponent.h"
#include "../Components/AnimationComponent.h"
#ifndef GUJARUNSFML_ENTITY_H
#define GUJARUNSFML_ENTITY_H


class Entity
{
public:
    Entity();
    virtual ~Entity();

    //Functions
    virtual void render(sf::RenderTarget* target);
    virtual void update(const float &dt);
    virtual void move(const float x, const float y, const float &dt);
    virtual void setPosition(const float x ,const float y);
    void createMovementComponents(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponents(sf::Sprite& sprite, sf::Texture& texture_sheet);
    //Component Functions
    void setTexture(sf::Texture& texture);

protected:
    float movementSpeed;
    sf::Sprite sprite;

    MovementComponents* movementComponents;
    AnimationComponent* animationComponents;


private:
    void initVariables();

};

#endif //GUJARUNSFML_ENTITY_H
