//
// Created by Paratthakorn Sribunyong on 8/10/2019 AD.
//

#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width , unsigned height, std::string texture_file)

{

    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSize.x = width;
    this->maxSize.y = height;
    this->layers = 1;
    this->textureFile = texture_file;

    this->map.resize(this->maxSize.x, std::vector <std::vector<Tile*>>());
    for (size_t x = 0; x < this->maxSize.x;x++)
    {

        for (size_t y = 0; y < this->maxSize.y; y++)
        {
            this->map[x].resize(this->maxSize.y,std::vector<Tile*>());

            for (size_t z = 0; z < this->layers; z++)
            {
                this->map[x][y].resize(this->layers, nullptr);

            }
        }
    }
    if (!this->tileSheet.loadFromFile(texture_file))
    {
        std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET." << std::endl;
    }
}

TileMap::~TileMap()
{
    for (size_t x = 0; x < this->maxSize.x;x++)
    {
        this->map.push_back(std::vector <std::vector<Tile*>>());

        for (size_t y = 0; y < this->maxSize.y; y++)
        {
            this->map[x].resize(this->maxSize.y);
            this->map[x].push_back(std::vector<Tile*>());

            for (size_t z = 0; z < this->layers; z++)
            {
                delete this->map[x][y][z];

            }
        }
    }
}

void TileMap::addTile(const unsigned x , const unsigned y, const unsigned z, const sf::IntRect& texture_rect) {

    //Add tile if internal Tile map allowed
    if (x < this->maxSize.x && x >= 0 &&
    y < this->maxSize.y && y >= 0 &&
    z <= this->layers && z >= 0)
    {
        if (this->map[x][y][z] == nullptr)
        {
            /* Allow to Add Tiles */
            this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileSheet, texture_rect);
            std::cout << "DEBUG:: ADD TILE!" << std::endl;}
    }



}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z) {
    //Remove tile if internal Tile map allowed
    if (x < this->maxSize.x && x >= 0 &&
        y < this->maxSize.y && y >= 0 &&
        z <= this->layers && z >= 0)
    {
        if (this->map[x][y][z] != nullptr)
        {
            /* Remove Tiles */
            delete this->map[x][y][z];
            this->map[x][y][z] = nullptr;
            std::cout << "DEBUG:: REMOVE TILE!" << std::endl;
        }
    }

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

            for (auto *z : y)
            {
                if (z != nullptr)
                    z->render(target);

            }
        }

    }
}

const sf::Texture *TileMap::getTileSheet() const
{
    return &this->tileSheet;
}

void TileMap::saveToFile(const std::string file_name) {
    /*Save Tilemap to text file
    Format:
     Size x y
     gridSize
     layers
     texture_file

     All tiles:
     gridPos x y , Texture rect x y, type
     */

    std::ofstream out_file;
    out_file.open(file_name);

    if (out_file.is_open())
    {
        out_file << this->maxSize.x << " " << this->maxSize.y << std::endl
         << this->gridSizeU << std::endl
         << this->layers << std::endl
         << this->textureFile << std::endl;

        for (size_t x = 0; x < this->maxSize.x;x++)
        {

            for (size_t y = 0; y < this->maxSize.y; y++)
            {

                for (size_t z = 0; z < this->layers; z++)
                {
                    out_file << 1 << 1 << 2 << 3 << 5 << " ";
                    //out_file << this->map[x][y][z];
                }
            }
        }
    }
    else
    {
        std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << std::endl;

    }
    out_file.close();

}

void TileMap::loadFromFile(const std::string file_name) {

}



