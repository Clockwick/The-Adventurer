//
// Created by Paratthakorn Sribunyong on 17/11/2019 AD.
//

#ifndef GUJARUNSFML_ITEMS_H
#define GUJARUNSFML_ITEMS_H
#include "../Precom.h"
#include "../Entities/Entity.h"
class Item : public Entity
{
private:
    void initVariables();
    void initAnimations();


    bool isJump;
    short type;


public:
    Item(float x, float y, sf::Texture& texture_sheet, short type = 0);
    virtual ~Item();

    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget& target, const bool show_hitbox = false);
    virtual void updateJumping(const float& dt);
    virtual void updateAnimations(const float& dt);
    const bool intersects(const sf::FloatRect bounds) const;
};

#endif //GUJARUNSFML_ITEMS_H
