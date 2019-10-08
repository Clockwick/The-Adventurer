//
// Created by Paratthakorn Sribunyong on 6/10/2019 AD.
//

#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(float x, float y, float gridSizeF)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setFillColor(sf::Color::Red);

}
Tile::~Tile()
{

}


//Functions
void Tile::update()
{

}

void Tile::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
}

