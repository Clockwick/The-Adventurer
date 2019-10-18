//
// Created by Paratthakorn Sribunyong on 2/10/2019 AD.
//

#include "EditorState.h"

EditorState::EditorState(StateData* state_data)
        : State(state_data)
{
    this->initVariables();
    this->initView();
    this->initBackground();
    this->initFonts();
    this->initText();
    this->initButtons();
    this->initPauseMenu();
    this->initTileMap();
    this->initGui();


}

EditorState::~EditorState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end();++it){
        delete it->second;


    }
    delete this->pmenu;
    delete this->tileMap;
    delete this->textureSelector;
}
//Initializer
void EditorState::initFonts() {
    if (!this->font.loadFromFile("fonts/RobotoCondensed-Regular.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }
}

void EditorState::initButtons() {


}

void EditorState::initText() {

    cursorText.setPosition(this->mousePosView.x+100.f, this->mousePosView.y - 50);
    cursorText.setFont(this->font);
    cursorText.setCharacterSize(16);
    cursorText.setFillColor(sf::Color::White);


}

void EditorState::initGui() {
    this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->state_data->gfxSettings->resolution.height)));
    this->sidebar.setFillColor(sf::Color(50,50,50,100));
    this->sidebar.setOutlineColor(sf::Color(200,200,200,150));
    this->sidebar.setOutlineThickness(1.f);

    this->selectorRect.setSize(sf::Vector2f(this->state_data->gridSize, this->state_data->gridSize));
    this->selectorRect.setFillColor(sf::Color(255,255,255,150));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::White);

    this->selectorRect.setTexture(this->tileMap->getTileSheet());
    this->selectorRect.setTextureRect(this->textureRect);

    this->textureSelector = new gui::TextureSelector(10.f, 10.f, 500.f, 500.f,
            this->state_data->gridSize, this->tileMap->getTileSheet(),
            this->font, "Edit"
            );
}

void EditorState::initTileMap() {
    this->tileMap = new TileMap(this->state_data->gridSize, 10, 10, "resources/images/Assets/Map/16x16/Tile/TerrainSet.png");
}

void EditorState::initPauseMenu() {
    this->pmenu = new PauseMenu(*this->window, this->font);

    this->pmenu->addButton("QUIT", 1400.f, "Quit");
    this->pmenu->addButton("SAVE", 1100.f, "Save");
    this->pmenu->addButton("LOAD", 1250.f, "Load");

}


void EditorState::initBackground() {

}

void EditorState::initVariables() {
    this->textureRect = sf::IntRect(0,0, static_cast<int>(this->state_data->gridSize) * 0.45, static_cast<int>(this->state_data->gridSize) * 0.45);
    this->collision = false;
    this->type = TileTypes::DEFAULT;
}

//Update
void EditorState::update(const float &dt) {

    this->updateMousePos();
    this->updateKeytime(dt);
    this->updateInput(dt);

    if (!this->paused)//Unpaused
    {
        this->updateButtons();
        this->updateGui(dt);
        this->updateEditorInput(dt);
    }
    else //Paused
    {

        this->pmenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();

    }



}
void EditorState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->getKeyTime())
    {

        if(!this->paused)
            this->pauseState();
        else
            this->unpauseState();
    }

}

void EditorState::updateButtons() {

    for (auto &it : this->buttons) {
        it.second->update(this->mousePosWindow);

    }

}

void EditorState::updateEditorInput(const float &dt) {

    //Add tile
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime()) {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))) {
            if (!this->textureSelector->getActive())
            {
                this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);

            } else {
                this->textureRect = this->textureSelector->getTextureRect();
            }
        }
    }
    //Remove tile
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime()) {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))) {
            if (!this->textureSelector->getActive())
            {
                this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);

            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && this->getKeyTime())
    {
        if(this->collision)
            this->collision = false;
        else
            this->collision = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->getKeyTime())
    {
        //Increase type
        ++this->type;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->getKeyTime())
    {
        //Decrease type
        if (this->type > 0)
            --this->type;
    }



}
void EditorState::updateGui(const float& dt) {
    this->textureSelector->update(this->mousePosWindow, dt);
    if (!this->textureSelector->getActive()) {
        this->selectorRect.setPosition(this->mousePosGrid.x * this->state_data->gridSize,
                                       this->mousePosGrid.y * this->state_data->gridSize);
        this->selectorRect.setTextureRect(this->textureRect);
    }

    cursorText.setPosition(this->mousePosView.x + 50, this->mousePosView.y - 50);
    std::stringstream ss;
    ss << "(" <<this->mousePosView.x << "," << this->mousePosView.y << ")" << std::endl
            << "(" <<this->mousePosGrid.x << "," << this->mousePosGrid.y << ")" << std::endl
            << "(" <<this->textureRect.left << "," << this->textureRect.top << ")" << std::endl
            << "Collision: " << this->collision << "\n" << "Type: " << this->type;
    cursorText.setString(ss.str());


}

void EditorState::updatePauseMenuButtons() {
    if (this->pmenu->isButtonPressed(("QUIT")) && this->getKeyTime())
        this->endState();
    if (this->pmenu->isButtonPressed(("SAVE")) && this->getKeyTime())
        this->tileMap->saveToFile("text.slmp");
    if (this->pmenu->isButtonPressed(("LOAD")) && this->getKeyTime())
        this->tileMap->loadFromFile("text.slmp");


}
//Render
void EditorState::render(sf::RenderTarget *target) {

    if(!target)
    {
        target = this->window;
    }
    target->setView(this->view);
    this->tileMap->render(*target);
    target->setView(this->window->getDefaultView());
    this->renderButtons(*target);
    this->renderGui(*target);



    if (this->paused)
    {
        //Pause Menu Render
        this->pmenu->render(*target);

    }



}


void EditorState::renderGui(sf::RenderTarget& target) {
    if (this->textureSelector->getActive())
        target.draw(this->selectorRect);

    this->textureSelector->render(target);
    target.draw(this->cursorText);
    target.draw(this->sidebar);
}

void EditorState::renderButtons(sf::RenderTarget &target) {
    for (auto &it : this->buttons ){

        it.second->render(target) ;
    }
}

void EditorState::initView() {
    this->view.setSize(sf::Vector2f(this->state_data->gfxSettings->resolution.width,this->state_data->gfxSettings->resolution.height));
    this->view.setCenter(this->state_data->gfxSettings->resolution.width / 2.f, this->state_data->gfxSettings->resolution.height / 2.f);
}












