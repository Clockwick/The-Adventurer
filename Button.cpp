
#include "Button.h"



Button::Button(float x, float y, float width, float height, sf::Font *font, std::string text, sf::Color idleColor,
               sf::Color hoverColor, sf::Color activeColor)
               {
    this->buttonStates = BTN_IDLE;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(36);
    this->text.setPosition(
            (this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.0f) - this->text.getGlobalBounds().width / 2.0f,
            (this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.0f) - this->text.getGlobalBounds().height / 2.0f
            );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

}

Button::~Button()
{


}

//Accessories




//Functions

void Button::render(sf::RenderTarget *target) {
    target->draw(this->shape);
    target->draw(this->text);
}

void Button::update(const sf::Vector2f mousePos) {
    /* Update the bool for Hover and Pressed */
    //Idle
    this->buttonStates = BTN_IDLE;
    //Hover
    if (this->shape.getGlobalBounds().contains(mousePos)) {
        this->buttonStates = BTN_HOVER;
        //Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->buttonStates = BTN_ACTIVE;

        }
    }

   switch (this->buttonStates)
   {
       case BTN_IDLE:
           this->shape.setFillColor(this->idleColor);
           break;

       case BTN_HOVER:
           this->shape.setFillColor(this->hoverColor);
           break;

       case BTN_ACTIVE:
           this->shape.setFillColor(this->activeColor);
           break;
       default:
           this->shape.setFillColor(sf::Color::Red);
           break;

   }
}

const bool Button::isPressed() const {
    if (this->buttonStates == BTN_ACTIVE)
    {
        return 1;
    }
    return 0;

}

