
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
    this->shape.setFillColor(outline_idle_color);
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
gui::TextureSelector::TextureSelector(float x, float y, float width, float height,float* gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string text)
: keytimeMax(1.f), keytime(0.f)
{

    this->gridSize = *gridSize;
    this->active = false;
    this->hidden = false;

    float offset = *gridSize;
    this->ptr = gridSize;

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
    this->selector.setSize(sf::Vector2f(*this->ptr, *this->ptr));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::Red);

    this->textureRect.width = static_cast<int>(*this->ptr);
    this->textureRect.height = static_cast<int>(*this->ptr);

    this->hide_button = new gui::Button(x,y,50.f,50.f,
            &font, text, 24,
            sf::Color(255,255,255,200),sf::Color(255,255,255,250),sf::Color(255,255,255,50),
            sf::Color(70,70,70,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50)
    );

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
        this->hidden = !this->hidden;
    }
    if (!this->hidden)
    {
        this->active = false;

        if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
        {
            this->active = true;

            this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(*this->ptr);
            this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(*this->ptr);
            this->selector.setPosition(this->bounds.getPosition().x + this->mousePosGrid.x * *this->ptr,
                                       this->bounds.getPosition().y + this->mousePosGrid.y * *this->ptr);
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
        this->hidden = !this->hidden;
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

gui::Status::Status(Player* player,float x, float y, float width, float height,float gridSize, sf::Font& font, std::string text, const std::string player_name)
        : keytimeMax(1.f), keytime(0.f)
{
    this->playerName = player_name;

    this->player = player;
    this->initVariables();
    this->gridSize = gridSize;
    this->active = false;
    this->statusActive = false;
    this->hidden = true;
    this->statusFont = &font;

    float offset = gridSize;

    this->bounds.setSize(sf::Vector2f(width, height));
    this->bounds.setPosition(908, y - 925);
    this->bounds.setFillColor(sf::Color(50,50,50, 100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255,255,255,200));


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
    this->firstCol = this->bounds.getPosition().x + this->bounds.getGlobalBounds().width/2.f;
    this->secondCol = this->bounds.getPosition().x + 100.f;
    this->thirdCol = this->firstCol + 50.f;
    this->initProfile();
    this->initText();
    this->initButtons();



}

gui::Status::~Status() {
    delete this->hide_button;
    delete this-> vitText;
    delete this-> strText;
    delete this-> dexText;
    delete this-> agiText;
    delete this-> luckText;
    delete this-> intText;
//
    delete this-> name;
    delete this-> levelText;
    delete this-> statPoints;
    delete this-> hpText;

    delete this-> dmgText;
    delete this-> levelNextText;


    for (auto it = this->buttons.begin(); it != this->buttons.end();++it){
        delete it->second;
    }



}
void gui::Status::initVariables() {
    this->spaceY = 75.f;
    this->activeButtons = false;
}
void gui::Status::initProfile() {
    this->profileShape.setSize(sf::Vector2f(275.f, 255.f));
    this->profileShape.setFillColor(sf::Color::White);
    this->profileShape.setPosition(sf::Vector2f(this->bounds.getPosition().x + 100.f, this->bounds.getPosition().y + 100.f));
}


void gui::Status::initText()
{
    this->name = new gui::TextGui(this->firstCol,this->bounds.getPosition().y + 125.f, this->statusFont, 36, sf::Color::White, sf::Color::Black, "Name: ", this->playerName);
    this->levelText = new gui::TextGui(this->firstCol, this->bounds.getPosition().y + 125.f + this->spaceY, this->statusFont, 36
            , sf::Color::White, sf::Color::Black, "Level: ", std::to_string(this->player->getAttributeComponents()->level));
    this->hpText = new gui::TextGui(this->firstCol, this->bounds.getPosition().y + 125.f + (2 * this->spaceY), this->statusFont, 36
            , sf::Color::White, sf::Color::Black, "HP: ", std::to_string(this->player->getAttributeComponents()->hp));
    this->statPoints = new gui::TextGui(this->secondCol, this->bounds.getPosition().y + 150.f + (3 * this->spaceY), this->statusFont, 40
            , sf::Color::White, sf::Color::Black, "Stat Points Left: ", std::to_string(this->player->getAttributeComponents()->attributePoints), 1);
    this->strText = new gui::TextGui(this->secondCol, this->bounds.getPosition().y + 150.f + (4 * this->spaceY), this->statusFont, 36
            , sf::Color::White, sf::Color::Black, "Str: ", std::to_string(this->player->getAttributeComponents()->Str));
    this->vitText = new gui::TextGui(this->secondCol, this->bounds.getPosition().y + 150.f + (5 * this->spaceY), this->statusFont, 36
            , sf::Color::White, sf::Color::Black, "Vit: ", std::to_string(this->player->getAttributeComponents()->Vit));
    this->agiText = new gui::TextGui(this->secondCol, this->bounds.getPosition().y + 150.f + (6 * this->spaceY), this->statusFont, 36
            , sf::Color::White, sf::Color::Black, "Agi: ", std::to_string(this->player->getAttributeComponents()->Agi));
    this->dexText = new gui::TextGui(this->secondCol, this->bounds.getPosition().y + 150.f + (7 * this->spaceY), this->statusFont, 36
            , sf::Color::White, sf::Color::Black, "Dex: ", std::to_string(this->player->getAttributeComponents()->Dex));
    this->intText = new gui::TextGui(this->secondCol, this->bounds.getPosition().y + 150.f + (8 * this->spaceY), this->statusFont, 36
            , sf::Color::White, sf::Color::Black, "Int: ", std::to_string(this->player->getAttributeComponents()->Int));
    this->luckText = new gui::TextGui(this->secondCol, this->bounds.getPosition().y + 150.f + (9 * this->spaceY), this->statusFont, 36
            , sf::Color::White, sf::Color::Black, "Luck: ", std::to_string(this->player->getAttributeComponents()->luck));
    this->dmgText = new gui::TextGui(this->thirdCol, this->bounds.getPosition().y + 150.f + (4 * this->spaceY), this->statusFont, 36
            , sf::Color::White, sf::Color::Black, "Dmg: ", std::to_string(this->player->getAttributeComponents()->damageMin));
    this->levelNextText = new gui::TextGui(this->thirdCol, this->bounds.getPosition().y + 150.f + (5 * this->spaceY), this->statusFont, 36
            , sf::Color::White, sf::Color::Black, "ExpNext: ", std::to_string(this->player->getAttributeComponents()->expNext), 3);


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
//    std::cout << this->player << "\n";
    this->updateKeytime(dt);
    this->hide_button->update(mousePosWindow);
    if (this->hide_button->isPressed() && this->getKeytime())
    {
        this->hidden = !this->hidden;

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
        }
        if (this->statusTag.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
        {
            this->statusActive = true;

        }

    }
    //Update value
    this->vitText->update(std::to_string(this->player->getAttributeComponents()->Vit));
    this->strText->update(std::to_string(this->player->getAttributeComponents()->Str));
    this->dexText->update(std::to_string(this->player->getAttributeComponents()->Dex));
    this->agiText->update(std::to_string(this->player->getAttributeComponents()->Agi));
    this->luckText->update(std::to_string(this->player->getAttributeComponents()->luck));
    this->intText->update(std::to_string(this->player->getAttributeComponents()->Int));

    this->levelText->update(std::to_string(this->player->getAttributeComponents()->level));
    this->statPoints->update(std::to_string(this->player->getAttributeComponents()->attributePoints));
    this->hpText->update(std::to_string(this->player->getAttributeComponents()->hp));

    this->dmgText->update(std::to_string(this->player->getAttributeComponents()->damageMin));
    this->levelNextText->update(std::to_string(this->player->getAttributeComponents()->expNext));

    this->updateButtons(mousePosWindow);

}

void gui::Status::updateKeytime(const float& dt)
{
    if (this->keytime < this->keytimeMax)
        this->keytime += 10.f * dt;

}


void gui::Status::render(sf::RenderTarget &target) {
    this->hide_button->render(target);

    if (!this->hidden) {
        this->statusStorage.push_back(this->player->getAttributeComponents()->Str);
        this->statusStorage.push_back(this->player->getAttributeComponents()->Vit);
        this->statusStorage.push_back(this->player->getAttributeComponents()->Agi);
        this->statusStorage.push_back(this->player->getAttributeComponents()->Dex);
        this->statusStorage.push_back(this->player->getAttributeComponents()->Int);
        this->statusStorage.push_back(this->player->getAttributeComponents()->luck);
        this->statusStorage.push_back(this->player->getAttributeComponents()->attributePoints);
        target.draw(this->bounds);
        target.draw(this->statusTag);
        target.draw(this->statusText);
        target.draw(this->profileShape);
        this->name->render(target);
        this->levelText->render(target);
        this->hpText->render(target);
        this->statPoints->render(target);
        this->strText->render(target);
        this->vitText->render(target);
        this->agiText->render(target);
        this->dexText->render(target);
        this->intText->render(target);
        this->luckText->render(target);
        this->dmgText->render(target);
        this->levelNextText->render(target);
        this->renderButtons(target);
    }

    if (!this->statusStorage.empty() && this->hidden)
        this->statusStorage.pop_back();
}

void gui::Status::allText() {

}

void gui::Status::initButtons() {
    this->buttons["PLUS_STR"] = new gui::Button(this->secondCol + 200.f,this->bounds.getPosition().y + 145.f + (4 * this->spaceY),40.f, 40.f, this->statusFont, "+",
                                                40.f, sf::Color(255,255,255,200),sf::Color(150,150,150,250),sf::Color(150,150,150,50),sf::Color(250,250,250,250 ),
                                                sf::Color(250,250,250,200),sf::Color(250,250,250,200));
    this->buttons["PLUS_VIT"] = new gui::Button(this->secondCol + 200.f,this->bounds.getPosition().y + 145.f + (5 * this->spaceY),40.f, 40.f, this->statusFont, "+",
                                                40.f, sf::Color(255,255,255,200),sf::Color(150,150,150,250),sf::Color(150,150,150,50),sf::Color(250,250,250,250 ),
                                                sf::Color(250,250,250,200),sf::Color(250,250,250,200));
    this->buttons["PLUS_AGI"] = new gui::Button(this->secondCol + 200.f,this->bounds.getPosition().y + 145.f + (6 * this->spaceY),40.f, 40.f, this->statusFont, "+",
                                                40.f, sf::Color(255,255,255,200),sf::Color(150,150,150,250),sf::Color(150,150,150,50),sf::Color(250,250,250,250 ),
                                                sf::Color(250,250,250,200),sf::Color(250,250,250,200));

    this->buttons["PLUS_DEX"] = new gui::Button(this->secondCol + 200.f,this->bounds.getPosition().y + 145.f + (7 * this->spaceY),40.f, 40.f, this->statusFont, "+",
                                                40.f, sf::Color(255,255,255,200),sf::Color(150,150,150,250),sf::Color(150,150,150,50),sf::Color(250,250,250,250 ),
                                                sf::Color(250,250,250,200),sf::Color(250,250,250,200));
    this->buttons["PLUS_INT"] = new gui::Button(this->secondCol + 200.f,this->bounds.getPosition().y + 145.f + (8 * this->spaceY),40.f, 40.f, this->statusFont, "+",
                                                40.f, sf::Color(255,255,255,200),sf::Color(150,150,150,250),sf::Color(150,150,150,50),sf::Color(250,250,250,250 ),
                                                sf::Color(250,250,250,200),sf::Color(250,250,250,200));
    this->buttons["PLUS_LUCK"] = new gui::Button(this->secondCol + 200.f,this->bounds.getPosition().y + 145.f + (9 * this->spaceY),40.f, 40.f, this->statusFont, "+",
                                                 40.f, sf::Color(255,255,255,200),sf::Color(150,150,150,250),sf::Color(150,150,150,50),sf::Color(250,250,250,250 ),
                                                 sf::Color(250,250,250,200),sf::Color(250,250,250,200));
    this->buttons["SAVE"] = new gui::Button(this->thirdCol - 50.f,this->bounds.getPosition().y + 145.f + (9 * this->spaceY),90.f, 60.f, this->statusFont, "Save",
                                            48.f, sf::Color(255,255,255,200),sf::Color(150,150,150,250),sf::Color(150,150,150,50),sf::Color(250,250,250,250 ),
                                            sf::Color(250,250,250,200),sf::Color(250,250,250,200));
    this->buttons["RESET"] = new gui::Button(this->thirdCol + 200.f,this->bounds.getPosition().y + 145.f + (9 * this->spaceY),90.f, 60.f, this->statusFont, "Reset",
                                             48.f, sf::Color(255,255,255,200),sf::Color(150,150,150,250),sf::Color(150,150,150,50),sf::Color(250,250,250,250 ),
                                             sf::Color(250,250,250,200),sf::Color(250,250,250,200));

}

void gui::Status::updateButtons(const sf::Vector2i& mousePosWindow) {
    for (auto &it : this->buttons){
        it.second->update(mousePosWindow);
    }
    if (this->player->getAttributeComponents()->attributePoints > 0)
    {
        this->activeButtons = true;

        if (this->buttons["PLUS_STR"]->isPressed() && this->getKeytime())
        {
            this->player->getAttributeComponents()->Str++;
            this->player->getAttributeComponents()->attributePoints--;
        }
        if (this->buttons["PLUS_VIT"]->isPressed() && this->getKeytime())
        {
            this->player->getAttributeComponents()->Vit++;
            this->player->getAttributeComponents()->attributePoints--;
        }if (this->buttons["PLUS_AGI"]->isPressed() && this->getKeytime())
        {
            this->player->getAttributeComponents()->Agi++;
            this->player->getAttributeComponents()->attributePoints--;
        }
        if (this->buttons["PLUS_DEX"]->isPressed() && this->getKeytime())
        {
            this->player->getAttributeComponents()->Dex++;
            this->player->getAttributeComponents()->attributePoints--;
        }
        if (this->buttons["PLUS_INT"]->isPressed() && this->getKeytime())
        {
            this->player->getAttributeComponents()->Int++;
            this->player->getAttributeComponents()->attributePoints--;
        }
        if (this->buttons["PLUS_LUCK"]->isPressed() && this->getKeytime())
        {
            this->player->getAttributeComponents()->luck++;
            this->player->getAttributeComponents()->attributePoints--;
        }


    }
    if (this->buttons["SAVE"]->isPressed() && this->getKeytime())
    {
        if (!this->statusStorage.empty()) {
            for (int i = 0; i < this->statusStorage.size(); i++) {
                this->statusStorage.pop_back();
            }
        }
        this->saveStatusStorage.push_back(this->player->getAttributeComponents()->Str);
        this->saveStatusStorage.push_back(this->player->getAttributeComponents()->Vit);
        this->saveStatusStorage.push_back(this->player->getAttributeComponents()->Agi);
        this->saveStatusStorage.push_back(this->player->getAttributeComponents()->Dex);
        this->saveStatusStorage.push_back(this->player->getAttributeComponents()->Int);
        this->saveStatusStorage.push_back(this->player->getAttributeComponents()->luck);
        this->saveStatusStorage.push_back(this->player->getAttributeComponents()->attributePoints);

    }
    if (this->buttons["RESET"]->isPressed() && this->getKeytime())
    {
        if (!this->saveStatusStorage.empty()) {
            this->player->getAttributeComponents()->Str = this->saveStatusStorage[0];
            this->player->getAttributeComponents()->Vit = this->saveStatusStorage[1];
            this->player->getAttributeComponents()->Agi = this->saveStatusStorage[2];
            this->player->getAttributeComponents()->Dex = this->saveStatusStorage[3];
            this->player->getAttributeComponents()->Int = this->saveStatusStorage[4];
            this->player->getAttributeComponents()->luck = this->saveStatusStorage[5];
            this->player->getAttributeComponents()->attributePoints = this->saveStatusStorage[6];
        }
        else {
            this->player->getAttributeComponents()->Str = 1;
            this->player->getAttributeComponents()->Vit = 1;
            this->player->getAttributeComponents()->Agi = 1;
            this->player->getAttributeComponents()->Dex = 1;
            this->player->getAttributeComponents()->Int = 1;
            this->player->getAttributeComponents()->luck = 1;
            this->player->getAttributeComponents()->attributePoints = 3;
        }
    }

    else
    {
        this->activeButtons = false;
    }



}

void gui::Status::renderButtons(sf::RenderTarget &target) {
    for (auto &it : this->buttons){

        it.second->render(target) ;
    }
}


/*=================================================================*/
//                          Text Gui                               //

gui::TextGui::TextGui(float x, float y, sf::Font *font, unsigned char_size, sf::Color text_color,
                      sf::Color outline_color, std::string text, std::string value, const short type) {
    this->textFont = font;

    this->text.setFont(*this->textFont);
    this->text.setFillColor(text_color);
    this->text.setOutlineThickness(0.5f);
    this->text.setOutlineColor(outline_color);
    this->text.setCharacterSize(char_size);
    this->text.setPosition(x, y);
    this->text.setString(text);

    this->value.setFont(*this->textFont);
    this->value.setFillColor(text_color);
    this->value.setOutlineThickness(0.5f);
    this->value.setOutlineColor(outline_color);
    this->value.setCharacterSize(char_size);
    if (type == 0)
        this->value.setPosition(x + 125,y);
    if (type == 1)
        this->value.setPosition(x + 290,y);
    if (type == 3)
        this->value.setPosition(x + 160, y);
    this->value.setString(value);


}

gui::TextGui::~TextGui() {
}




void gui::TextGui::render(sf::RenderTarget& target)
{
    target.draw(this->text);
    target.draw(this->value);
}

void gui::TextGui::update(const std::string value) {
    this->value.setString(value);
}
