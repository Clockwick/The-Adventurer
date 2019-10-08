//
// Created by Paratthakorn Sribunyong on 8/10/2019 AD.
//

#include "TileMap.h"

TileMap::TileMap()

{

    this->gridSizeF = 50.f;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSize.x = 100;
    this->maxSize.y = 100;
    this->layers = 1;

    this->map.resize(this->maxSize.x);
    for (size_t x = 0; x < this->maxSize.x;x++)
    {
        this->map.push_back(std::vector <std::vector<Tile>>());

        for (size_t y = 0; y < this->maxSize.y; y++)
        {
            this->map[x].resize(this->maxSize.y);
            this->map[x].push_back(std::vector<Tile>());

            for (size_t z = 0; z < this->layers; z++)
            {
                this->map[x][y].resize(this->layers);
                this->map[x][y].push_back(Tile(static_cast<float>(x)  * this->gridSizeF, static_cast<float>(y) * gridSizeF, this->gridSizeF));

            }
        }
    }
}

TileMap::~TileMap()
{

}


//Functions
void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget &target)
{
    for (auto &x : this->map)
    {

        for (auto &y : x)
        {

            for (auto &z : y)
            {
                z.render(target);

            }
        }

    }
}

