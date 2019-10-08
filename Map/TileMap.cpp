//
// Created by Paratthakorn Sribunyong on 8/10/2019 AD.
//

#include "TileMap.h"

TileMap::TileMap() {
    this->gridSizeU = 50;
    this->maxSize.x = 100;
    this->maxSize.y = 100;
    this->layers = 1;


    for (size_t x = 0; this->maxSize.x;x++)
    {
        this->map.push_back(std::vector <std::vector<Tile>>());

        for (size_t y = 0; y < this->maxSize.y; y++)
        {
            this->map[x].push_back(std::vector<Tile>());

            for (size_t z = 0; z < this->layers; z++)
            {
                this->map[x][y].push_back(Tile());

            }
        }
    }
}

TileMap::~TileMap() {

}
