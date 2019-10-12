//
// Created by Paratthakorn Sribunyong on 6/10/2019 AD.
//

#ifndef GUJARUNSFML_TILE_H
#define GUJARUNSFML_TILE_H
#include "Precom.h"

class Tile{
public:
    Tile();
    Tile(float x, float y, float gridSizeF, sf::Texture& texture);
    virtual ~Tile();
    void update();
    void render(sf::RenderTarget& target);
protected:
    sf::RectangleShape shape;

private:

};
#endif //GUJARUNSFML_TILE_H
