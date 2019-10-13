//
// Created by Paratthakorn Sribunyong on 6/10/2019 AD.
//

#ifndef GUJARUNSFML_TILE_H
#define GUJARUNSFML_TILE_H
#include "Precom.h"

enum TileTypes {DEFAULT = 0, DAMAGING};
class Tile{
public:
    Tile();
    Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, sf::Texture& texture, const sf::IntRect& texture_rect,
            bool collision = false, short type = TileTypes::DEFAULT);
    virtual ~Tile();
    void update();
    void render(sf::RenderTarget& target);
    const std::string getAsString() const;
protected:
    sf::RectangleShape shape;
    short type;
    bool collision;

private:

};
#endif //GUJARUNSFML_TILE_H
