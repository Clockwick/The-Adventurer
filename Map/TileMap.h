//
// Created by Paratthakorn Sribunyong on 8/10/2019 AD.
//

#ifndef GUJARUNSFML_TILEMAP_H
#define GUJARUNSFML_TILEMAP_H

#include "../Tile.h"

class TileMap
{
public:
    TileMap();
    virtual ~TileMap();
    void update();
    void render(sf::RenderTarget& target);


private:
    unsigned gridSizeU;
    sf::Vector2u maxSize;
    std::vector <std::vector<std::vector<Tile>>> map;
    unsigned layers;
    float gridSizeF;


};

#endif //GUJARUNSFML_TILEMAP_H
