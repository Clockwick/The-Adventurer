//
// Created by Paratthakorn Sribunyong on 8/10/2019 AD.
//

#ifndef GUJARUNSFML_TILEMAP_H
#define GUJARUNSFML_TILEMAP_H

#include "../Tile.h"
#include "../Entities/Entity.h"


class Tile;
class Entity;
class TileMap
{
public:
    TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
    virtual ~TileMap();
    void update();
    void render(sf::RenderTarget& target, const sf::Vector2i& gridPosition, const bool show_collision = false);

    void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short type);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);

    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);

    void updateCollision(Entity* entity, const float& dt);

    //Accessor
    const int getLayerSize(const int x, const int y, const int layer) const;
    const sf::Texture * getTileSheet() const;
    const bool tileEmpty(const int x , const int y, const int z) const;
private:
    unsigned gridSizeU;
    sf::Vector2u maxSizeWorldGrid;
    sf::Vector2f maxSizeWorldF;
    std::vector <std::vector<std::vector<std::vector<Tile*>>>> map;
    unsigned layers;
    float gridSizeF;
    sf::Texture tileSheet;
    std::string textureFile;
    sf::RectangleShape collisionBox;
    bool canJump;




    //Culling
    int fromX;
    int fromY;
    int toX;
    int toY;
    int layer;


    void clear();


};

#endif //GUJARUNSFML_TILEMAP_H
