//
// Created by Paratthakorn Sribunyong on 12/11/2019 AD.
//

#include "DefaultMode.h"

DefaultMode::DefaultMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
: EditorMode(state_data, tile_map, editor_state_data)
{
    this->initVariables();
    this->initGui();
}

DefaultMode::~DefaultMode()
{
    delete this->textureSelector;
}

void DefaultMode::initVariables() {
    this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize) * 0.45,
                                    static_cast<int>(this->stateData->gridSize) * 0.45);
    this->collision = false;
    this->type = TileTypes::DEFAULT;
    this->layer = 0;
    this->tileAddLock = false;
}

void DefaultMode::initGui() {
    cursorText.setFont(*this->editorStateData->font);
    cursorText.setCharacterSize(16);
    cursorText.setFillColor(sf::Color::White);
    cursorText.setPosition(this->editorStateData->mousePosView->x + 100.f, this->editorStateData->mousePosView->y - 50);

    //General Gui
    this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
    this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
    this->sidebar.setOutlineThickness(1.f);

    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::White);

    this->selectorRect.setTexture(this->tileMap->getTileSheet());
    this->selectorRect.setTextureRect(this->textureRect);

    this->textureSelector = new gui::TextureSelector(10.f, 10.f, 2250.f, 2250.f,
                                                     this->stateData->gridSize, this->tileMap->getTileSheet(),
                                                     *this->editorStateData->font, "Edit"
    );
    //Buttons
}
void DefaultMode::update(const float &dt) {
    this->updateInput(dt);
    this->updateGui(dt);
}

void DefaultMode::updateInput(const float &dt) {
//Add tile
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime()) {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow))) {
            if (!this->textureSelector->getActive()) {
                if (this->tileAddLock) {
                    if (this->tileMap->tileEmpty(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0)) {
                        this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect,
                                               this->collision, this->type);
                    }
                }
                else {
                    this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect,
                                           this->collision, this->type);
                }


            } else {
                this->textureRect = this->textureSelector->getTextureRect();
            }
        }
    }
        //Remove tile
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime()) {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow))) {
            if (!this->textureSelector->getActive()) {
                this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0);

            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && this->getKeyTime()) {
        this->collision = !this->collision;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->getKeyTime()) {
        //Increase type
        ++this->type;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->getKeyTime()) {
        //Decrease type
        if (this->type > 0)
            --this->type;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && this->getKeyTime()) {
        this->tileAddLock = !this->tileAddLock;
    }
}

void DefaultMode::updateGui(const float &dt) {
    this->textureSelector->update(*this->editorStateData->mousePosWindow, dt);
    if (!this->textureSelector->getActive()) {
        this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize,
                                       this->editorStateData->mousePosGrid->y * this->stateData->gridSize);
        this->selectorRect.setTextureRect(this->textureRect);
    }

    cursorText.setPosition(this->editorStateData->mousePosView->x + 50, this->editorStateData->mousePosView->y - 50);
    std::stringstream ss;
    ss << "(" << static_cast<int>(this->editorStateData->mousePosView->x) << "," << static_cast<int>(this->editorStateData->mousePosView->y) << ")"
       << std::endl
       << "(" << this->editorStateData->mousePosGrid->x << "," << this->editorStateData->mousePosGrid->y << ")" << std::endl
       << "(" << this->textureRect.left << "," << this->textureRect.top << ")" << std::endl
       << "Collision: " << this->collision << "\n" << "Type: " << this->type << std::endl
       << "Tile: " << this->tileMap->getLayerSize(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, this->layer) << std::endl
       << "Tile Lock: " << this->tileAddLock;

    cursorText.setString(ss.str());

}

void DefaultMode::renderGui(sf::RenderTarget &target) {
    if (!this->textureSelector->getActive()) {
        target.setView(*this->editorStateData->view);
        target.draw(this->selectorRect);
    }
    target.setView(this->stateData->window->getDefaultView());
    this->textureSelector->render(target);
    target.draw(this->sidebar);

    target.setView(*this->editorStateData->view);
    target.draw(this->cursorText);
}

void DefaultMode::render(sf::RenderTarget *target) {
    this->renderGui(*target);
}




