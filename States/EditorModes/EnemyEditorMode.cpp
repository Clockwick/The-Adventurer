//
// Created by Paratthakorn Sribunyong on 13/11/2019 AD.
//

#include "EnemyEditorMode.h"

EnemyEditorMode::EnemyEditorMode(StateData *state_data, TileMap *tile_map, EditorStateData *editor_state_data)
: EditorMode(state_data, tile_map, editor_state_data)
{
    this->initVariables();
    this->initGui();

}

EnemyEditorMode::~EnemyEditorMode() {

}

void EnemyEditorMode::initGui() {
    cursorText.setFont(*this->editorStateData->font);
    cursorText.setCharacterSize(16);
    cursorText.setFillColor(sf::Color::White);
    cursorText.setPosition(this->editorStateData->mousePosView->x + 50.f, this->editorStateData->mousePosView->y - 50.f);

    //General Gui
    this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
    this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
    this->sidebar.setOutlineThickness(1.f);

    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::White);



}

void EnemyEditorMode::initVariables() {
    type = 0;
    amount = 1;
    timeToSpawn = 60;
    maxDistance = 1000.f;
}


//FUNCTIONS
void EnemyEditorMode::update(const float &dt) {
    this->updateInput(dt);
    this->updateGui(dt);
}

void EnemyEditorMode::updateInput(const float &dt) {
    //Add tile
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime()) {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow))) {
                        this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect,
                                               true, TileTypes::ENEMYSPAWNER);
        }
    }
        //Remove tile
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime()) {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow))) {
                this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, TileTypes::ENEMYSPAWNER);

        }
    }

}

void EnemyEditorMode::updateGui(const float &dt) {
    this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize,
                                   this->editorStateData->mousePosGrid->y * this->stateData->gridSize);
    this->cursorText.setPosition(this->editorStateData->mousePosView->x + 100.f,  this->editorStateData->mousePosView->y - 50.f);
    std::stringstream ss;
    ss << "\n"
        << "Enemy type: " << this->type << "\n"
       << "Enemy amount: " << this->amount <<"\n"
       << "Time to Spawn: " << this->timeToSpawn << "\n"
       << "maxDistance: " << this->maxDistance;

    cursorText.setString(ss.str());

}

void EnemyEditorMode::renderGui(sf::RenderTarget &target) {
    target.setView(*this->editorStateData->view);
    target.draw(this->selectorRect);
    target.draw(this->cursorText);

    target.setView(target.getDefaultView());
    target.draw(this->sidebar);
}

void EnemyEditorMode::render(sf::RenderTarget &target) {
    this->renderGui(target);
}


