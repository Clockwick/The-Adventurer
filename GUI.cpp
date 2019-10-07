
#include "GUI.h"



gui::Button::Button(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned character_size,
                 sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, sf::Color idle_color,
                 sf::Color hover_color, sf::Color active_color)
        {
    this->buttonStates = BTN_IDLE;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(this->idleColor);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
            (this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.0f) - this->text.getGlobalBounds().width / 2.0f,
            (this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.0f) - this->text.getGlobalBounds().height / 2.0f
            );

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;
    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;



}

gui::Button::~Button()
{


}

//Accessories




//Functions

void gui::Button::render(sf::RenderTarget &target) {
    target.draw(this->shape);
    target.draw(this->text);
}

void gui::Button::update(const sf::Vector2f mousePos) {
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
           this->text.setFillColor(this->textIdleColor);
           break;

       case BTN_HOVER:
           this->shape.setFillColor(this->hoverColor);
           this->text.setFillColor(this->textHoverColor);
           break;

       case BTN_ACTIVE:
           this->shape.setFillColor(this->activeColor);
           this->text.setFillColor(this->textActiveColor);
           break;
       default:
           this->shape.setFillColor(sf::Color::Red);
           this->text.setFillColor(sf::Color::Blue);
           break;

   }
}

//Accessor

const std::string &gui::Button::getText() const
{
    return this->text.getString();
}

const bool gui::Button::isPressed() const
{
    if (this->buttonStates == BTN_ACTIVE)
    {
        return 1;
    }
    return 0;

}


//Modifiers
void gui::Button::setText(const std::string text)
{
    this->text.setString(text);

}

/*===============================================================*/
//                      Drop Down List                           //


void gui::DropDownList::update(const float &dt)
{

}

void gui::DropDownList::render(sf::RenderTarget &target)
{

}

gui::DropDownList::DropDownList(sf::Font& font, std::string list[],unsigned numofElements, const unsigned default_index)
: font(font)
{
    for (size_t i = 0; i< numofElements; i++)
    {
        this->list.push_back(new gui::Button(1280.f,798.f,300.f,150.f,
                                             &this->font, list[i], 36,
                                             sf::Color(70,70,70,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                             sf::Color(70,70,70,50),sf::Color(150,150,150,50),sf::Color(20,20,20,50)
                             )
        );
    }
    //unsigned numofElements = sizeof(list) / sizeof(std::string);

    this->activeElement = new Button(*this->list[default_index]);
}

gui::DropDownList::~DropDownList()
{
    delete this->activeElement;
    for (auto *&i : this->list)
        delete i;
}
