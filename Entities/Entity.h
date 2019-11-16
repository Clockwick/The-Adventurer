//
// Created by Paratthakorn Sribunyong on 2/9/2019 AD.
//
#include "../Components/HitboxComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/AttributeComponent.h"
#include "../Components/SkillComponent.h"
#ifndef GUJARUNSFML_ENTITY_H
#define GUJARUNSFML_ENTITY_H


class Entity
{
public:
    Entity();
    virtual ~Entity();

    //Functions
    virtual void render(sf::RenderTarget& target, const bool show_collision) = 0;
    virtual void update(const float &dt) = 0;
    virtual void move(const float x, const float y, const float &dt);
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();
    virtual void jump();


    void createMovementComponents(const float maxVelocity, const float acceleration, const float deceleration , const float& jumpHeight);
    void createAnimationComponents(sf::Texture& texture_sheet);
    void createHitboxComponents(sf::Sprite& sprite, float offset_x,
            float offset_y, float width, float height, short type = HitTypes::DEFAULT_COL);
    void createAttributeComponents(int level);
    void createSkillComponents();
    //Accessors
    virtual const sf::Vector2f& getPosition() const;
    virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual const sf::FloatRect& getNextPositionBounds(const float& dt) const;
    virtual const sf::Vector2f& getVelocity() const {return this->movementComponents->getVelocity();}

    //Modifiers
    virtual void setPosition(const float x ,const float y);
    //Component Functions
    void setTexture(sf::Texture& texture);

    //Allow
    void allowJump(bool* canJump);


protected:
    float movementSpeed;
    sf::Sprite sprite;
    bool canJump;

    MovementComponents* movementComponents;
    AnimationComponent* animationComponents;
    HitboxComponent* hitboxComponents;
    AttributeComponent* attributeComponents;
    SkillComponent* skillComponents;


private:
    void initVariables();

};

#endif //GUJARUNSFML_ENTITY_H
