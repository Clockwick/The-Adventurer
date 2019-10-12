//
// Created by Paratthakorn Sribunyong on 8/10/2019 AD.
//

#ifndef GUJARUNSFML_TILEMAP_H
#define GUJARUNSFML_TILEMAP_H

#include "../Tile.h"

class TileMap
{
public:
    TileMap(float gridSize, unsigned width, unsigned height);
    virtual ~TileMap();
    void update();
    void render(sf::RenderTarget& target);

    void addTile(const unsigned x, const unsigned y, const unsigned z);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);




private:
    unsigned gridSizeU;
    sf::Vector2u maxSize;
    std::vector <std::vector<std::vector<Tile*>>> map;
    unsigned layers;
    float gridSizeF;
    sf::Texture tileTextureSheet;


};

#endif //GUJARUNSFML_TILEMAP_H
