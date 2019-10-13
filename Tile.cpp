//
// Created by Paratthakorn Sribunyong on 6/10/2019 AD.
//

#include "Tile.h"

Tile::Tile()
{
    this->collision = false;
    this->type = 0;
}

Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, sf::Texture& texture, const sf::IntRect& texture_rect ,
        bool collision , short type)
{
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setFillColor(sf::Color(255, 153, 204));
    //this->shape.setOutlineColor(sf::Color::Black);
    //this->shape.setOutlineThickness(1.f);
    this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float> (grid_y) * gridSizeF);
    this->shape.setTexture(&texture);
    this->shape.setTextureRect(texture_rect);

    this->collision = false;
    this->type = 0;

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

const std::string Tile::getAsString() const {
    std::stringstream ss;
    ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;

    return ss.str();
}

