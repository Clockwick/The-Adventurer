//
// Created by Paratthakorn Sribunyong on 2/9/2019 AD.
//
#include "../Components/HitboxComponent.h"
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
    virtual void render(sf::RenderTarget& target) = 0;
    virtual void update(const float &dt) = 0;
    virtual void move(const float x, const float y, const float &dt);
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();

    void createMovementComponents(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponents(sf::Texture& texture_sheet);
    void createHitboxComponents(sf::Sprite& sprite, float offset_x,
            float offset_y, float width, float height);
    //Accessors
    virtual const sf::Vector2f& getPosition() const;
    virtual const sf::Vector2u getGridPosition(const unsigned gridSizeI) const;
    virtual const sf::FloatRect getGlobalBounds() const;
    //Modifiers
    virtual void setPosition(const float x ,const float y);
    //Component Functions
    void setTexture(sf::Texture& texture);

protected:
    float movementSpeed;
    sf::Sprite sprite;

    MovementComponents* movementComponents;
    AnimationComponent* animationComponents;
    HitboxComponents* hitboxComponents;


private:
    void initVariables();

};

#endif //GUJARUNSFML_ENTITY_H
