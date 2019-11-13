//
// Created by Paratthakorn Sribunyong on 6/10/2019 AD.
//

#ifndef GUJARUNSFML_TILE_H
#define GUJARUNSFML_TILE_H
#include "Precom.h"

enum TileTypes {DEFAULT = 0, DAMAGING, ENEMYSPAWNER};
class Tile{
public:
    Tile();
    Tile(int grid_x, int grid_y, float gridSizeF, sf::Texture& texture, const sf::IntRect& texture_rect,
            bool collision = false, short type = TileTypes::DEFAULT);
    virtual ~Tile();
    virtual void update();
    virtual void render(sf::RenderTarget &target, const sf::Vector2f player_position = sf::Vector2f());

    //ACCESSORS
    const std::string getAsString() const;
    const sf::Vector2f& getPosition() const;
    const bool intersects(const sf::FloatRect bounds) const;
    const sf::FloatRect getGlobalBounds() const;
    const bool& getCollision() const;
    const short& getType() const;

protected:
    sf::RectangleShape shape;
    short type;
    bool collision;

private:

};
#endif //GUJARUNSFML_TILE_H
