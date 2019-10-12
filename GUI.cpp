
#include "GUI.h"



gui::Button::Button(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned character_size,
                 sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, sf::Color idle_color,
                 sf::Color hover_color, sf::Color active_color,sf::Color outline_idle_color,
                    sf::Color outline_hover_color,
                    sf::Color outline_active_color,
                    unsigned short id)
        {
    this->buttonStates = BTN_IDLE;
    this->id = id;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(this->idleColor);
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(outline_idle_color);

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

    this->outlineActiveColor = outline_active_color;
    this->outlineidleColor = outline_idle_color;
    this->outlineHoverColor = outline_hover_color;

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
           this->shape.setFillColor(this->outlineidleColor);
           this->text.setFillColor(this->textIdleColor);
           break;

       case BTN_HOVER:
           this->shape.setFillColor(this->hoverColor);
           this->shape.setFillColor(this->outlineHoverColor);
           this->text.setFillColor(this->textHoverColor);
           break;

       case BTN_ACTIVE:
           this->shape.setFillColor(this->activeColor);
           this->shape.setFillColor(this->outlineActiveColor);
           this->text.setFillColor(this->textActiveColor);
           break;
       default:
           this->shape.setFillColor(sf::Color::Red);
           this->text.setFillColor(sf::Color::Blue);
           this->text.setFillColor(sf::Color::Red);
           break;

   }
}

//Accessor

const std::string gui::Button::getText() const
{
    return this->text.getString();
}
const unsigned short &gui::Button::getId() const
{
    return  this->id;

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

void gui::Button::setId(const unsigned short id)
{
    this->id = id;
}



/*===============================================================*/
//                      Drop Down List                           //


void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{
    this->updateKeytime(dt);
    this->activeElement->update(mousePos);

    if (this->activeElement->isPressed() && this->getKeytime())
    {
        if (this->showList)
            this->showList = false;
        else
            this->showList = true;


    }


    if (this->showList)
    {
        for (auto &i : this->list)
        {
            i->update(mousePos);
        }
    }


}

void gui::DropDownList::render(sf::RenderTarget &target)
{
    this->activeElement->render(target);

    //Show and Hide the List
    if(this->activeElement->isPressed())
    {
        if (this->showList)
            this->showList = false;
        else
            this->showList = true;
    }

    if (this->showList)
    {
        for (auto &i : this->list)
        {
            i->render(target);

            if (i->isPressed() && this->getKeytime()) {
                this->showList = false;
                this->activeElement->setText(i->getText());
                this->activeElement->setId(i->getId());
            }
        }
    }

}


void gui::DropDownList::updateKeytime(const float& dt)
{
    if (this->keytime < this->keytimeMax)
        this->keytime += 10.f * dt;

}

//Accessors
const bool gui::DropDownList::getKeytime()
{
    if (this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;

    }

    return false;
}

const unsigned short &gui::DropDownList::getActiveElementId() const
{
    return this->activeElement->getId();
}

gui::DropDownList::DropDownList(float x, float y, float width, float height,
        sf::Font& font,std::string list[],unsigned numofElements, const unsigned default_index)
: font(font), showList(false), keytime(0.f), keytimeMax(1.f)
{


}
gui::DropDownList::~DropDownList() {
    delete this->activeElement;
    for (size_t i = 0; i < this->list.size(); i++)
    {
        delete this->list[i];
    }


}


/*=================================================================*/
//                      Texture Selector                          //
gui::TextureSelector::TextureSelector(float x, float y, float width, float height,float gridSize, const sf::Texture* texture_sheet)
{

    this->active = false;
    this->gridSize = gridSize;
    this->bounds.setSize(sf::Vector2f(width, height));
    this->bounds.setPosition(x, y);
    this->bounds.setFillColor(sf::Color(50,50,50,100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255,255,255,200));

    this->sheet.setTexture(*texture_sheet);
    this->sheet.setPosition(x, y);
    if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
    {
       this->sheet.setTextureRect(sf::IntRect(0,0, this->sheet.getGlobalBounds().width, this->sheet.getGlobalBounds().width));
    }
    if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
    {
        this->sheet.setTextureRect(sf::IntRect(0,0, this->sheet.getGlobalBounds().height, this->sheet.getGlobalBounds().height));

    }

    this->selector.setPosition(x, y);
    this->selector.setSize(sf::Vector2f(gridSize, gridSize));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::Red);

}

gui::TextureSelector::~TextureSelector() {


}

//Accessor
const bool &gui::TextureSelector::getActive() {
    return this->active;
}

//Functions
void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow) {

    if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
        this->active = true;
    else
        this->active = false;

    if (this->active)
    {
        this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
        this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);
        this->selector.setPosition(this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
                this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);
    }
}

void gui::TextureSelector::render(sf::RenderTarget &target) {
    target.draw(this->bounds);
    target.draw(this->sheet);
    target.draw(this->selector);
}




