//
// Created by Paratthakorn Sribunyong on 12/11/2019 AD.
//

#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(int grid_x, int grid_y, float gridSizeF, sf::Texture& texture, const sf::IntRect& texture_rect,
                           sf::Vector2i grid_position,float grid_size, int enemy_type, int enemy_amount, int enemy_timeToSpawn, float enemy_maxDistance
        ) : Tile(grid_x, grid_y, gridSizeF, texture, texture_rect, false, TileTypes::ENEMYSPAWNER)
{
    this->enemyType = enemy_type;
    this->enemyAmount = enemy_amount;
    this->enemyTimeToSpawn = enemy_timeToSpawn;
    this->enemyMaxDistance = enemy_maxDistance;
}

EnemySpawner::~EnemySpawner() {

}

//FUNCTIONS
void EnemySpawner::update() {

}

void EnemySpawner::render(sf::RenderTarget &target, const sf::Vector2f player_position) {
    target.draw(this->shape);
}


