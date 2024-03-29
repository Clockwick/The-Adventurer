//
// Created by Paratthakorn Sribunyong on 8/10/2019 AD.
//

#include "TileMap.h"

TileMap::TileMap(float gridSize, int width, int height, std::string texture_file) {

    this->gridSizeF = gridSize;
    this->gridSizeI = static_cast<int>(this->gridSizeF);
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

    this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile *>>>());
    for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {

        for (int y = 0; y < this->maxSizeWorldGrid.y; y++) {
            this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile *>>());

            for (int z = 0; z < this->layers; z++) {
                this->map[x][y].resize(this->layers, std::vector<Tile *>());

            }
        }
    }
    if (!this->tileSheet.loadFromFile(texture_file)) {
        std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET" << std::endl;
    }
    this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
    this->collisionBox.setFillColor(sf::Color(250, 250, 250, 50));
    this->collisionBox.setOutlineColor(sf::Color::Yellow);
    this->collisionBox.setOutlineThickness(-1.f);
}


TileMap::~TileMap() {
    this->clear();
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect &texture_rect, const bool &collision,
                      const short type) {

    //Add tile if internal Tile map allowed
    if (x < this->maxSizeWorldGrid.x && x >= 0 &&
        y < this->maxSizeWorldGrid.y && y >= 0 &&
        z <= this->layers && z >= 0) {

        /* Add Tiles */
        this->map[x][y][z].push_back(new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type));
        std::cout << "DEBUG:: ADD TILE!" << std::endl;
    }


}


void TileMap::removeTile(const int x, const int y, const int z, const int type) {
    //Remove tile if internal Tile map allowed
    if (x < this->maxSizeWorldGrid.x && x >= 0 &&
        y < this->maxSizeWorldGrid.y && y >= 0 &&
        z < this->layers && z >= 0) {
        if (!this->map[x][y][z].empty()) {
            if (type >= 0)
            {
                if (this->map[x][y][z].back()->getType() == type) {
                    /* Remove Tiles */
                    delete this->map[x][y][z][this->map[x][y][z].size() - 1];
                    this->map[x][y][z].pop_back();
//                    std::cout << "DEBUG:: REMOVE TILE!" << std::endl;
                }

            }
            else
            {
                /* Remove Tiles */
                delete this->map[x][y][z][this->map[x][y][z].size() - 1];
                this->map[x][y][z].pop_back();
//                std::cout << "DEBUG:: REMOVE TILE!" << std::endl;
            }


        }
    }

}

//Functions
void TileMap::update(Entity *entity, const float &dt) {

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
    this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
    if (this->fromX < 2) {
        this->fromX = 2;
    } else if (this->fromX > this->maxSizeWorldGrid.x) {
        this->fromX = this->maxSizeWorldGrid.x;
    }
    this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
    if (this->toX < 0) {
        this->toX = 0;
    } else if (this->toX > this->maxSizeWorldGrid.x) {
        this->toX = this->maxSizeWorldGrid.x;
    }
    this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
    if (this->fromY < 0) {
        this->fromY = 0;
    } else if (this->fromY > this->maxSizeWorldGrid.y) {
        this->fromY = this->maxSizeWorldGrid.y;
    }
    this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
    if (this->toY < 0) {
        this->toY = 0;
    } else if (this->toY > this->maxSizeWorldGrid.y) {
        this->toY = this->maxSizeWorldGrid.y;
    }

    for (int x = fromX; x < this->toX; x++) {
        for (int y = fromY; y < this->toY; y++) {
            for (int k = 0; k < this->map[x][y][this->layer].size(); k++) {
                this->map[x][y][this->layer][k]->update();

                sf::FloatRect playerBounds = entity->getGlobalBounds();
                sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
                sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
                if (this->map[x][y][this->layer][k]->getCollision() &&
                    this->map[x][y][this->layer][k]->intersects(nextPositionBounds)) {
                    //Bottom collision

                    if (
                        playerBounds.left < wallBounds.left + wallBounds.width
                        && playerBounds.left + playerBounds.width  + 25> wallBounds.left && !entity->getMovementComponents()->faceRight && (entity->getAttack() || entity->getAttack1() || entity->getAttack2())
                            ) {
                        std::cout << "Case" << std::endl;
                        this->canJump = true;
                        entity->allowJump(&this->canJump);
                        entity->stopVelocityY();
                        entity->setPosition(entity->getPosition().x, wallBounds.top - playerBounds.height + 9);
                    }
                    else if (playerBounds.top < wallBounds.top - 69.999f
                             && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                             && playerBounds.left < wallBounds.left + wallBounds.width
                             && playerBounds.left + playerBounds.width > wallBounds.left
                            ) {
                        std::cout << "Bottom Collision" << std::endl;
                        this->canJump = true;
                        entity->allowJump(&this->canJump);
                        entity->stopVelocityY();
                        entity->setPosition(playerBounds.left + 20, wallBounds.top - playerBounds.height + 9);
                    }

                        //Top collision
                    else if (playerBounds.top > wallBounds.top
                             && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height + 63
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
                             && playerBounds.top < wallBounds.top + wallBounds.height
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
}

void TileMap::render(sf::RenderTarget &target, const sf::Vector2i &gridPosition, const bool show_collision) {

    this->layer = 0;
    this->fromX = gridPosition.x - 10;
    if (this->fromX < 2) {
        this->fromX = 2;
    } else if (this->fromX > this->maxSizeWorldGrid.x) {
        this->fromX = this->maxSizeWorldGrid.x;
    }
    this->toX = gridPosition.x + 15 ;
    if (this->toX < 0) {
        this->toX = 0;
    } else if (this->toX > this->maxSizeWorldGrid.x) {
        this->toX = this->maxSizeWorldGrid.x;
    }
    this->fromY = gridPosition.y - 5;
    if (this->fromY < 0) {
        this->fromY = 0;
    } else if (this->fromY > this->maxSizeWorldGrid.y) {
        this->fromY = this->maxSizeWorldGrid.y;
    }
    this->toY = gridPosition.y + 7;
    if (this->toY < 0) {
        this->toY = 0;
    } else if (this->toY > this->maxSizeWorldGrid.y) {
        this->toY = this->maxSizeWorldGrid.y;
    }

    for (int x = this->fromX; x < this->toX; x++) {
        for (int y = this->fromY; y < this->toY; y++) {
            for (int k = 0; k < this->map[x][y][this->layer].size(); k++) {
                this->map[x][y][this->layer][k]->render(target);
                if (show_collision) {
                    if (this->map[x][y][this->layer][k]->getCollision()) {
                        this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
                        target.draw(this->collisionBox);
                    }
                }
                    if (this->map[x][y][this->layer][k]->getType() == TileTypes::ENEMYSPAWNER)
                    {
                        this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
                        target.draw(this->collisionBox);
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
                 << this->gridSizeI << std::endl
                 << this->layers << std::endl
                 << this->textureFile << std::endl;

        for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {

            for (int y = 0; y < this->maxSizeWorldGrid.y; y++) {

                for (int z = 0; z < this->layers; z++) {
                    if (!this->map[x][y][z].empty()) {
                        for (int k = 0; k < this->map[x][y][z].size(); k++) {
                            out_file << x << " " << y << " " << z << " " << this->map[x][y][z][k]->getAsString()
                                     << " "; //Last space must not saved
                        }

                    }
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
        int gridSize = 0;
        int layers = 0;
        std::string texture_file = "I love Thanunchai";
        int x = 0;
        int y = 0;
        int z = 0;
        int trX = 0;
        int trY = 0;
        bool collision = false;
        short type = 0;

        //Basic Loading
        in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

        //Tiles

        this->gridSizeI = gridSize;
        this->gridSizeF = static_cast<float>(gridSize);
        this->maxSizeWorldGrid.x = size.x;
        this->maxSizeWorldGrid.y = size.y;
        this->maxSizeWorldF.x = static_cast<float>(size.x) * gridSizeF;
        this->maxSizeWorldF.y = static_cast<float>(size.y) * gridSizeF;
        this->layers = layers;
        this->textureFile = texture_file;

        this->clear();

        this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile *>>>());
        for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {

            for (int y = 0; y < this->maxSizeWorldGrid.y; y++) {
                this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile *>>());

                for (int z = 0; z < this->layers; z++) {
                    this->map[x][y].resize(this->layers, std::vector<Tile *>());

                }
            }
        }
        if (!this->tileSheet.loadFromFile(texture_file)) {
            std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE_TEXTURE_SHEET." << std::endl;
        }

        //Load All Tiles
        while (in_file >> x >> y >> z >> trX >> trY >> collision >> type) {
            this->map[x][y][z].push_back(new Tile(x, y,
                                                  this->gridSizeF, this->tileSheet,
                                                  sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
                                                  collision, type));

        }


    } else {
        std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << std::endl;

    }
    in_file.close();
}

void TileMap::clear() {
    if (!this->map.empty()) {
        for (int x = 0; x < this->map.size(); x++) {

            for (int y = 0; y < this->map[x].size(); y++) {

                for (int z = 0; z < this->map[x][y].size(); z++) {

                    for (size_t k = 0; k < this->map[x][y][z].size(); k++) {
                        delete this->map[x][y][z][k];
                        this->map[x][y][z][k] = nullptr;
                    }
                    this->map[x][y][z].clear();
                }
                this->map[x][y].clear();
            }
            this->map[x].clear();
        }
        this->map.clear();
    }

}


const int TileMap::getLayerSize(const int x, const int y, const int layer) const {
    if (x >= 0 && x <= static_cast<int>(this->map.size())) {
        if (y >= 0 && static_cast<int>(this->map[x].size())) {
            if (layer >= 0 && layer < static_cast<int>(this->map[x][y].size())) {
                return this->map[x][y][layer].size();
            }
        }
    }
    return -1;

}

const bool TileMap::tileEmpty(const int x, const int y, const int z) const {
    if (x >= 0 && x < this->maxSizeWorldGrid.x &&
        y >= 0 && y < this->maxSizeWorldGrid.y &&
        z >= 0 && z < this->layers) {
        return this->map[x][y][z].empty();
    }
    return false;
}

const sf::Vector2f &TileMap::getMaxSizeF() const {
    return this->maxSizeWorldF;
}

const bool TileMap::checkType(const int x, const int y, const int z,const int type) const {
    return this->map[x][y][this->layer].back()->getType() == type;
}






