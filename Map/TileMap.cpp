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
        std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET" << std::endl;
    }
    this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
    this->collisionBox.setFillColor(sf::Color(255,0,0,50));
    this->collisionBox.setOutlineColor(sf::Color::Red);
    this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
    this->clear();
}

void TileMap::addTile(const unsigned x , const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short type) {

    //Add tile if internal Tile map allowed
    if (x < this->maxSize.x && x >= 0 &&
    y < this->maxSize.y && y >= 0 &&
    z <= this->layers && z >= 0)
    {
        if (this->map[x][y][z] == nullptr)
        {
            /* Allow to Add Tiles */
            this->map[x][y][z] = new Tile(x , y , this->gridSizeF, this->tileSheet, texture_rect, collision, type);
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

void TileMap::render(sf::RenderTarget &target,Entity *entity)
{
    for (auto &x : this->map)
    {

        for (auto &y : x)
        {

            for (auto *z : y)
            {
                if (z != nullptr) {
                    z->render(target);
                    if (z->getCollision()) {
                        this->collisionBox.setPosition(z->getPosition());
                        target.draw(this->collisionBox);
                    }
                }
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
     gridPos x y layer, Texture rect x y, collision ,type
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
                    if (this->map[x][y][z])
                        out_file << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString() << " "; //Last space must not saved
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
    std::ifstream in_file;
    in_file.open(file_name);

    if (in_file.is_open())
    {
        sf::Vector2i size;
        unsigned gridSize = 0;
        unsigned layers = 0;
        std::string texture_file = "I love Thanunchai";
        unsigned x = 0;
        unsigned y = 0;
        unsigned z = 0;
        unsigned trX = 0;
        unsigned trY = 0;
        bool collision = false;
        short type = 0;

        //Basic Loading
        in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

        //Tiles

        this->gridSizeU = gridSize;
        this->gridSizeF = static_cast<float>(gridSize);
        this->maxSize.x = size.x;
        this->maxSize.y = size.y;
        this->layers = layers;
        this->textureFile = texture_file;

        this->clear();

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
            std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE_TEXTURE_SHEET." << std::endl;
        }

        //Load All Tiles
        while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
        {
            this->map[x][y][z] = new Tile(x ,y ,
                    this->gridSizeF, this->tileSheet,
                    sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU),
                    collision, type);

        }


    }
    else
    {
        std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << std::endl;

    }
    in_file.close();
}

void TileMap::clear() {
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
                this->map[x][y][z] = nullptr;
            }
            this->map[x][y].clear();
        }
        this->map[x].clear();
    }
    this->map.clear();

}

void TileMap::updateCollision(Entity *entity) {


}



