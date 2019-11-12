//
// Created by Paratthakorn Sribunyong on 12/11/2019 AD.
//
#include "Precom.h"
#include "Tile.h"

#ifndef GUJARUNSFML_ENEMYSPAWNER_H
#define GUJARUNSFML_ENEMYSPAWNER_H


class EnemySpawner : public Tile
{
private:
    int enemyType;
    int enemyAmount;
    int enemyTimeToSpawn;
    float enemyMaxDistance;

    sf::Vector2i gridPosition;

public:
    EnemySpawner(int grid_x, int grid_y, float gridSizeF, sf::Texture& texture, const sf::IntRect& texture_rect,
            sf::Vector2i grid_position,float grid_size, int enemy_type, int enemy_amount, int enemy_timeToSpawn, float enemy_maxDistance
                 );
    virtual ~EnemySpawner();

    //FUNCTIONS
    void update();
    void render(sf::RenderTarget& target, const sf::Vector2f player_position = sf::Vector2f());

};

#endif //GUJARUNSFML_ENEMYSPAWNER_H
