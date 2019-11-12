//
// Created by Paratthakorn Sribunyong on 6/10/2019 AD.
//

#include "Tile.h"

Tile::Tile()
{
    this->collision = false;
    this->type = 0;
}

Tile::Tile(int grid_x, int grid_y, float gridSizeF, sf::Texture& texture, const sf::IntRect& texture_rect ,
        bool collision , short type)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setFillColor(sf::Color::White);
    this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float> (grid_y) * gridSizeF);
    this->shape.setTexture(&texture);
    this->shape.setTextureRect(texture_rect);

    this->collision = collision;
    this->type = 0;

}
Tile::~Tile()
{

}


//Functions
void Tile::update()
{

}

void Tile::render(sf::RenderTarget &target, const sf::Vector2f player_position)
{
    target.draw(this->shape);
}

const std::string Tile::getAsString() const {
    std::stringstream ss;
    ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;

    return ss.str();
}
//Accessors

const bool &Tile::getCollision() const {
    return this->collision;
}

const sf::Vector2f &Tile::getPosition() const {
    return this->shape.getPosition();
}


const bool Tile::intersects(const sf::FloatRect bounds) const {
    return this->shape.getGlobalBounds().intersects(bounds);

}

const sf::FloatRect Tile::getGlobalBounds() const {
   return this->shape.getGlobalBounds();
}

