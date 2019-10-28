//
// Created by Paratthakorn Sribunyong on 8/10/2019 AD.
//

#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width , unsigned height, std::string texture_file)

{

    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSizeWorldGrid.x = width;
    this->maxSizeWorldGrid.y = height;
    this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
    this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
    this->layers = 1;
    this->textureFile = texture_file;

    this->fromX = 0;
    this->toX = 0;
    this->fromY = 0;
    this->toY = 0;
    this->layer = 0;

    this->map.resize(this->maxSizeWorldGrid.x, std::vector <std::vector<Tile*>>());
    for (size_t x = 0; x < this->maxSizeWorldGrid.x;x++)
    {

        for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
        {
            this->map[x].resize(this->maxSizeWorldGrid.y,std::vector<Tile*>());

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
    this->collisionBox.setOutlineThickness(-1.f);
}

TileMap::~TileMap()
{
    this->clear();
}

void TileMap::addTile(const unsigned x , const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short type) {

    //Add tile if internal Tile map allowed
    if (x < this->maxSizeWorldGrid.x && x >= 0 &&
    y < this->maxSizeWorldGrid.y && y >= 0 &&
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
    if (x < this->maxSizeWorldGrid.x && x >= 0 &&
        y < this->maxSizeWorldGrid.y && y >= 0 &&
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

void TileMap::render(sf::RenderTarget &target,Entity *entity) {
        if (entity) {
            this->layer = 0;
            this->fromX = entity->getGridPosition(this->gridSizeU).x - 1;
            if (this->fromX < 2) {
                this->fromX = 2;
            } else if (this->fromX > this->maxSizeWorldGrid.x) {
                this->fromX = this->maxSizeWorldGrid.x;
            }
            this->toX = entity->getGridPosition(this->gridSizeU).x + 3;
            if (this->toX < 0) {
                this->toX = 0;
            } else if (this->toX > this->maxSizeWorldGrid.x) {
                this->toX = this->maxSizeWorldGrid.x;
            }
            this->fromY = entity->getGridPosition(this->gridSizeU).y - 1;
            if (this->fromY < 0) {
                this->fromY = 0;
            } else if (this->fromY > this->maxSizeWorldGrid.y) {
                this->fromY = this->maxSizeWorldGrid.y;
            }
            this->toY = entity->getGridPosition(this->gridSizeU).y + 3;
            if (this->toY < 0) {
                this->toY = 0;
            } else if (this->toY > this->maxSizeWorldGrid.y) {
                this->toY = this->maxSizeWorldGrid.y;
            }

            for (size_t x = this->fromX; x < this->toX; x++) {
                for (size_t y = this->fromY; y < this->toY; y++) {
                    this->map[x][y][this->layer]->render(target);
                    if (this->map[x][y][this->layer]->getCollision()) {
                        this->collisionBox.setPosition(this->map[x][y][this->layer]->getPosition());
                        target.draw(this->collisionBox);
                    }
                }
            }
        }

        else {
            for (auto &x : this->map) {

                for (auto &y : x) {

                    for (auto *z : y) {
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

}


    const sf::Texture *TileMap::getTileSheet() const {
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

        if (out_file.is_open()) {
            out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << std::endl
                     << this->gridSizeU << std::endl
                     << this->layers << std::endl
                     << this->textureFile << std::endl;

            for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++) {

                for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++) {

                    for (size_t z = 0; z < this->layers; z++) {
                        if (this->map[x][y][z])
                            out_file << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString()
                                     << " "; //Last space must not saved
                    }
                }
            }
        } else {
            std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << std::endl;

        }
        out_file.close();

    }

    void TileMap::loadFromFile(const std::string file_name) {
        std::ifstream in_file;
        in_file.open(file_name);

        if (in_file.is_open()) {
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
            this->maxSizeWorldGrid.x = size.x;
            this->maxSizeWorldGrid.y = size.y;
            this->layers = layers;
            this->textureFile = texture_file;

            this->clear();

            this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<Tile *>>());
            for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++) {

                for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++) {
                    this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile *>());

                    for (size_t z = 0; z < this->layers; z++) {
                        this->map[x][y].resize(this->layers, nullptr);

                    }
                }
            }
            if (!this->tileSheet.loadFromFile(texture_file)) {
                std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE_TEXTURE_SHEET." << std::endl;
            }

            //Load All Tiles
            while (in_file >> x >> y >> z >> trX >> trY >> collision >> type) {
                this->map[x][y][z] = new Tile(x, y,
                                              this->gridSizeF, this->tileSheet,
                                              sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU),
                                              collision, type);

            }


        } else {
            std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << std::endl;

        }
        in_file.close();
    }

    void TileMap::clear() {
        for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++) {
            this->map.push_back(std::vector<std::vector<Tile *>>());

            for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++) {
                this->map[x].resize(this->maxSizeWorldGrid.y);
                this->map[x].push_back(std::vector<Tile *>());

                for (size_t z = 0; z < this->layers; z++) {
                    delete this->map[x][y][z];
                    this->map[x][y][z] = nullptr;
                }
                this->map[x][y].clear();
            }
            this->map[x].clear();
        }
        this->map.clear();

    }

    void TileMap::updateCollision(Entity *entity, const float& dt) {

        //World Bounds
        if (entity->getPosition().x < 180.f) {
            entity->setPosition(180.f, entity->getPosition().y);
            entity->stopVelocityX();
        } else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x + 25) {
            entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width + 25, entity->getPosition().y);
            entity->stopVelocityX();
        }
        if (entity->getPosition().y < 0.f) {
            entity->setPosition(entity->getPosition().x + entity->getGlobalBounds().height, 0.f);
            entity->stopVelocityY();
        } else if (entity->getPosition().y > this->maxSizeWorldF.y) {
            entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
            entity->stopVelocityY();
        }

        // Tiles
        this->layer = 0;
        this->fromX = entity->getGridPosition(this->gridSizeU).x - 1;
        if (this->fromX < 2) {
            this->fromX = 2;
        } else if (this->fromX > this->maxSizeWorldGrid.x) {
            this->fromX = this->maxSizeWorldGrid.x;
        }
        this->toX = entity->getGridPosition(this->gridSizeU).x + 3;
        if (this->toX < 0) {
            this->toX = 0;
        } else if (this->toX > this->maxSizeWorldGrid.x) {
            this->toX = this->maxSizeWorldGrid.x;
        }
        this->fromY = entity->getGridPosition(this->gridSizeU).y - 1;
        if (this->fromY < 0) {
            this->fromY = 0;
        } else if (this->fromY > this->maxSizeWorldGrid.y) {
            this->fromY = this->maxSizeWorldGrid.y;
        }
        this->toY = entity->getGridPosition(this->gridSizeU).y + 3;
        if (this->toY < 0) {
            this->toY = 0;
        } else if (this->toY > this->maxSizeWorldGrid.y) {
            this->toY = this->maxSizeWorldGrid.y;
        }

        for (size_t x = fromX; x < this->toX; x++) {
            for (size_t y = fromY; y < this->toY; y++) {
                sf::FloatRect playerBounds = entity->getGlobalBounds();
                sf::FloatRect wallBounds = this->map[x][y][this->layer]->getGlobalBounds();
                sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
                if (this->map[x][y][this->layer]->getCollision() &&
                    this->map[x][y][this->layer]->intersects(nextPositionBounds)) {
                    //Bottom collision
                    if (playerBounds.top < wallBounds.top
                        && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                        && playerBounds.left < wallBounds.left + wallBounds.width
                        && playerBounds.left + playerBounds.width > wallBounds.left
                            ) {
                        std::cout << "Bottom Collision" << std::endl;
                        this->canJump = true;
                        entity->allowJump(this->canJump);
                        entity->stopVelocityY();
                        entity->setPosition(playerBounds.left + 20, wallBounds.top - playerBounds.height + 9);
                    }

//                        Top collision
                    else if (playerBounds.top > wallBounds.top
                             && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                             && playerBounds.left < wallBounds.left + wallBounds.width
                             && playerBounds.left + playerBounds.width > wallBounds.left
                            ) {
                        std::cout << "Top Collision" << std::endl;

                        entity->stopVelocityY();
                        entity->setPosition(playerBounds.left + 20, wallBounds.top + wallBounds.height);
                    }

                    //Right collision
                    if (playerBounds.left < wallBounds.left
                        && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width - 62
                        && playerBounds.top < wallBounds.top + wallBounds.height + 5
                        && playerBounds.top + playerBounds.height > wallBounds.top
                            ) {
                        std::cout << "Right Collision" << std::endl;

                        entity->stopVelocityX();
                        entity->setPosition(wallBounds.left - playerBounds.width + 45, playerBounds.top + 10);
                    }



                        //Left collision
                    else if (playerBounds.left > wallBounds.left
                             && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width + 75
                             && playerBounds.top < wallBounds.top + wallBounds.height + 5
                             && playerBounds.top + playerBounds.height > wallBounds.top
                            ) {
                        std::cout << "Left Collision" << std::endl;


                        entity->stopVelocityX();
                        entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top + 10);
                    }



                    }

                }
            }


        }




