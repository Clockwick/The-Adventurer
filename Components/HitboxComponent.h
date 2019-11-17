
#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H
#include "../Precom.h"

enum HitTypes {DEFAULT_COL = 0 , ATTACK_COL};

class HitboxComponent
{
private:
    sf::Sprite& sprite;
    sf::RectangleShape hitbox;
    sf::FloatRect nextPosition;
    float offsetX;
    float offsetY;

    short type;

    //Func
    void initVariables();

public:
    HitboxComponent(sf::Sprite& sprite,
                    float offset_x, float offset_y,
                    float width, float height, short type = HitTypes::DEFAULT_COL);
    virtual ~HitboxComponent();

    //Accessors
    const sf::Vector2f& getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);
    const short& getType() const;

    //Modifiers
    void setPosition(const sf::Vector2f& position);
    void setPosition(const float x, const float y);

    //Functions
    bool intersects(const sf::FloatRect& frect);

    void update();
    void render(sf::RenderTarget& target);
};

#endif