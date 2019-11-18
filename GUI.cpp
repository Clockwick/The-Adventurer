
#include "GUI.h"



const float gui::p2pX(const float perc, const sf::VideoMode& vm){

    return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

const float gui::p2pY(const float perc, const sf::VideoMode& vm){

    return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

const unsigned gui::calcCharSize(const sf::VideoMode& vm, const unsigned modifier){

    return static_cast<unsigned>((vm.width + vm.height) / modifier);
}


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
            this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.0f) - this->text.getGlobalBounds().width / 2.0f,
            this->shape.getPosition().y
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



//Functions

void gui::Button::render(sf::RenderTarget &target) {
    target.draw(this->shape);
    target.draw(this->text);
}

void gui::Button::update(const sf::Vector2i& mousePosWindow) {
    /* Update the bool for Hover and Pressed */
    //Idle
    this->buttonStates = BTN_IDLE;
    //Hover
    if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
    {
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
    return this->id;

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


void gui::DropDownList::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
    this->updateKeytime(dt);
    this->activeElement->update(mousePosWindow);

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
            i->update(mousePosWindow);
        }
    }


}

void gui::DropDownList::render(sf::RenderTarget &target)
{
    this->activeElement->render(target);

    //Show and Hide the List
    if(this->activeElement->isPressed() && this->getKeytime())
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
    this->activeElement = new gui::Button(x,y, width,height,
                                          &this->font, list[default_index], 36,
                                          sf::Color(30,30,30,250),sf::Color(20,20,20,200),sf::Color(20,20,20,50),
                                          sf::Color(150,150,150,150),sf::Color(150,150,150,200),sf::Color(20,20,20,200),
                                          sf::Color(255,255,255,200),sf::Color(255,255,255,255),sf::Color(20,20,20,50)
    );

    for (size_t i = 0; i< numofElements; i++)
    {
        this->list.push_back(new gui::Button(x,y + ((i+1) * height),width,height,
                                             &this->font, list[i], 36,
                                             sf::Color(30,30,30,250),sf::Color(20,20,20,50),sf::Color(20,20,20,50),
                                             sf::Color(150,150,150,150),sf::Color(150,150,150,200),sf::Color(20,20,20,200),
                                             sf::Color(150,150,150,200),sf::Color(255,255,255,200),sf::Color(20,20,20,200),
                                             i

                             )
        );
    }
    //unsigned numofElements = sizeof(list) / sizeof(std::string);


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
gui::TextureSelector::TextureSelector(float x, float y, float width, float height,float gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string text)
: keytimeMax(1.f), keytime(0.f)
{

    this->gridSize = gridSize;
    this->active = false;
    this->hidden = false;

    float offset = gridSize;

    this->bounds.setSize(sf::Vector2f(width, height));
    this->bounds.setPosition(x + offset, y);
    this->bounds.setFillColor(sf::Color(50,50,50,100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255,255,255,200));

    this->sheet.setTexture(*texture_sheet);
    this->sheet.setPosition(x + offset, y);
    if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
    {
       this->sheet.setTextureRect(sf::IntRect(0,0, static_cast<int>(this->sheet.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
    }
    if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
    {
        this->sheet.setTextureRect(sf::IntRect(0,0, static_cast<int>(this->sheet.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));

    }

    this->selector.setPosition(x, y);
    this->selector.setSize(sf::Vector2f(gridSize, gridSize));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::Red);

    this->textureRect.width = static_cast<int>(gridSize);
    this->textureRect.height = static_cast<int>(gridSize);

    this->hide_button = new gui::Button(x,y,50.f,50.f,
            &font, text, 24,
            sf::Color(255,255,255,200),sf::Color(255,255,255,250),sf::Color(255,255,255,50),
            sf::Color(70,70,70,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50)
    );;


}

gui::TextureSelector::~TextureSelector() {
    delete this->hide_button;

}

//Accessor
const bool &gui::TextureSelector::getActive() {
    return this->active;
}

const sf::IntRect &gui::TextureSelector::getTextureRect() const {
    return this->textureRect;
}


const bool gui::TextureSelector::getKeytime()
{
    if (this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;

    }

    return false;
}


//Functions
void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float &dt) {

    this->updateKeytime(dt);
    this->hide_button->update(mousePosWindow);
    if (this->hide_button->isPressed() && this->getKeytime())
    {
        if(this->hidden)
        {
            this->hidden = false;
        }
        else
        {
            this->hidden = true;
        }
    }
    if (!this->hidden)
    {
        this->active = false;

        if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
        {
            this->active = true;

            this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
            this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);
            this->selector.setPosition(this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
                                       this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);
            //Update TextureRect
            this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
            this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
        }
    }

}

void gui::TextureSelector::updateKeytime(const float& dt)
{
    if (this->keytime < this->keytimeMax)
        this->keytime += 10.f * dt;

}


void gui::TextureSelector::render(sf::RenderTarget &target) {
    this->hide_button->render(target);

    if (!this->hidden) {
        target.draw(this->bounds);
        target.draw(this->sheet);

        if (this->active)
            target.draw(this->selector);
    }

    this->hide_button->render(target);
}

/*=================================================================*/
//                      InventorySelector                          //
gui::InventorySelector::InventorySelector(float x, float y, float width, float height,float gridSize, sf::Font& font, std::string text)
        : keytimeMax(1.f), keytime(0.f)
{



    this->gridSize = gridSize;
    this->active = false;
    this->inventoryActive = false;
    this->hidden = true;

    float offset = gridSize;

    this->bounds.setSize(sf::Vector2f(width, height));
    this->bounds.setPosition(8, y - 925);
    this->bounds.setFillColor(sf::Color(50,50,50, 100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255,255,255,200));

    this->selector.setPosition(x, y);
    this->selector.setSize(sf::Vector2f(gridSize, gridSize));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::White);

    this->textureRect.width = static_cast<int>(gridSize);
    this->textureRect.height = static_cast<int>(gridSize);

    this->hide_button = new gui::Button(x,y,175.f,50.f,
                                        &font, text, 24,
                                        sf::Color(255,255,255,200),sf::Color(255,255,255,250),sf::Color(255,255,255,50),
                                        sf::Color(70,70,70,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50)
    );
    this->inventoryTag.setSize(sf::Vector2f(width, gridSize));
    this->inventoryTag.setOrigin(sf::Vector2f(this->bounds.getPosition().x + this->bounds.getSize().x / 2.f, 0.f));
    this->inventoryTag.setPosition(sf::Vector2f(this->bounds.getPosition().x + this->bounds.getGlobalBounds().width/2.f + 8.f, this->bounds.getPosition().y));
    this->inventoryTag.setFillColor(sf::Color(50, 50, 50, 100));
    this->inventoryTag.setOutlineColor(sf::Color(200, 200, 200, 150));
    this->inventoryTag.setOutlineThickness(1.f);
    this->inventoryText.setFont(font);
    this->inventoryText.setString(text);
    this->inventoryText.setCharacterSize(36.f);
    this->inventoryText.setPosition(this->bounds.getPosition().x + this->bounds.getGlobalBounds().width/2.f - 50.f, this->bounds.getPosition().y + 20.f);


}

gui::InventorySelector::~InventorySelector() {
    delete this->hide_button;

}

//Accessor
const bool &gui::InventorySelector::getActive() {
    return this->active;
}

const sf::IntRect &gui::InventorySelector::getTextureRect() const {
    return this->textureRect;
}
const bool &gui::InventorySelector::getInventoryActive() {
    return this->inventoryActive;
}


const bool gui::InventorySelector::getKeytime()
{
    if (this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;

    }

    return false;
}


//Functions
void gui::InventorySelector::update(const sf::Vector2i& mousePosWindow, const float &dt) {

    this->updateKeytime(dt);
    this->hide_button->update(mousePosWindow);
    if (this->hide_button->isPressed() && this->getKeytime())
    {
        if(this->hidden)
        {
            this->hidden = false;
        }
        else
        {
            this->hidden = true;
        }
    }
    if (!this->hidden)
    {
        this->active = false;
        this->inventoryActive = false;

        if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)) && !this->inventoryActive)
        {
            this->active = true;

            this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
            this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);
            this->selector.setPosition(this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
                                       this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);
            //Update TextureRect
            this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
            this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
        }
        if (this->inventoryTag.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
        {
            this->inventoryActive = true;

        }

    }

}

void gui::InventorySelector::updateKeytime(const float& dt)
{
    if (this->keytime < this->keytimeMax)
        this->keytime += 10.f * dt;

}


void gui::InventorySelector::render(sf::RenderTarget &target) {
    this->hide_button->render(target);

    if (!this->hidden) {
        target.draw(this->bounds);
        target.draw(this->inventoryTag);
        target.draw(this->inventoryText);
        if (this->active && !this->inventoryActive)
            target.draw(this->selector);
    }

    this->hide_button->render(target);
}

/*=================================================================*/
//                          Status                                //

gui::Status::Status(float x, float y, float width, float height,float gridSize, sf::Font& font, std::string text)
        : keytimeMax(1.f), keytime(0.f)
{



    this->gridSize = gridSize;
    this->active = false;
    this->statusActive = false;
    this->hidden = true;

    float offset = gridSize;

    this->bounds.setSize(sf::Vector2f(width, height));
    this->bounds.setPosition(908, y - 925);
    this->bounds.setFillColor(sf::Color(50,50,50, 100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255,255,255,200));

    this->selector.setPosition(x, y);
    this->selector.setSize(sf::Vector2f(gridSize, gridSize));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::White);

    this->textureRect.width = static_cast<int>(gridSize);
    this->textureRect.height = static_cast<int>(gridSize);

    this->hide_button = new gui::Button(x,y,175.f,50.f,
                                        &font, text, 24,
                                        sf::Color(255,255,255,200),sf::Color(255,255,255,250),sf::Color(255,255,255,50),
                                        sf::Color(70,70,70,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50)
    );
    this->statusTag.setSize(sf::Vector2f(width, gridSize));
    this->statusTag.setOrigin(sf::Vector2f(this->bounds.getPosition().x + this->bounds.getSize().x / 2.f, 0.f));
    this->statusTag.setPosition(sf::Vector2f(this->bounds.getPosition().x + this->bounds.getGlobalBounds().width/2.f + 908.f, this->bounds.getPosition().y));
    this->statusTag.setFillColor(sf::Color(50, 50, 50, 100));
    this->statusTag.setOutlineColor(sf::Color(200, 200, 200, 150));
    this->statusTag.setOutlineThickness(1.f);
    this->statusText.setFont(font);
    this->statusText.setString(text);
    this->statusText.setCharacterSize(36.f);
    this->statusText.setPosition(this->bounds.getPosition().x + this->bounds.getGlobalBounds().width/2.f - 50.f, this->bounds.getPosition().y + 20.f);


}

gui::Status::~Status() {
    delete this->hide_button;

}

//Accessor
const bool &gui::Status::getActive() {
    return this->active;
}

const sf::IntRect &gui::Status::getTextureRect() const {
    return this->textureRect;
}
const bool &gui::Status::getInventoryActive() {
    return this->statusActive;
}


const bool gui::Status::getKeytime()
{
    if (this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;

    }

    return false;
}


//Functions
void gui::Status::update(const sf::Vector2i& mousePosWindow, const float &dt) {

    this->updateKeytime(dt);
    this->hide_button->update(mousePosWindow);
    if (this->hide_button->isPressed() && this->getKeytime())
    {
        if(this->hidden)
        {
            this->hidden = false;
        }
        else
        {
            this->hidden = true;
        }
    }
    if (!this->hidden)
    {
        this->active = false;
        this->statusActive = false;

        if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)) && !this->statusActive)
        {
            this->active = true;

            this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
            this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);
            this->selector.setPosition(this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
                                       this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);
            //Update TextureRect
            this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
            this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
        }
        if (this->statusTag.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
        {
            this->statusActive = true;

        }

    }

}

void gui::Status::updateKeytime(const float& dt)
{
    if (this->keytime < this->keytimeMax)
        this->keytime += 10.f * dt;

}


void gui::Status::render(sf::RenderTarget &target) {
    this->hide_button->render(target);

    if (!this->hidden) {
        target.draw(this->bounds);
        target.draw(this->statusTag);
        target.draw(this->statusText);
        if (this->active && !this->statusActive)
            target.draw(this->selector);
    }

    this->hide_button->render(target);
}



