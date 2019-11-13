//
// Created by Paratthakorn Sribunyong on 2/10/2019 AD.
//

#include "EditorState.h"

EditorState::EditorState(StateData *state_data)
        : State(state_data) {
    this->initVariables();
    this->initEditorStateData();
    this->initView();
    this->initFonts();
    this->initPauseMenu();
    this->initTileMap();
    this->initModes();
}

EditorState::~EditorState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;


    }
    delete this->pmenu;
    delete this->tileMap;

    for (size_t i = 0; i < this->modes.size(); i++)
    {
        delete this->modes[i];
    }
}

//Initializer
void EditorState::initFonts() {
    if (!this->font.loadFromFile("fonts/RobotoCondensed-Regular.ttf")) {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }
}



void EditorState::initTileMap() {
    this->tileMap = new TileMap(this->state_data->gridSize, 100, 100,
                                "resources/images/Assets/Map/16x16/Tile/TerrainSet.png");
}

void EditorState::initPauseMenu() {
    const sf::VideoMode &vm = this->state_data->gfxSettings->resolution;
    this->pmenu = new PauseMenu(this->state_data->gfxSettings->resolution, this->font);
    this->pmenu->addButton("QUIT", gui::p2pY(77.77f, vm), gui::p2pX(6.94f, vm), gui::p2pY(3.61f, vm),
                           gui::calcCharSize(vm), "Quit");
    this->pmenu->addButton("SAVE", gui::p2pY(61.11f, vm), gui::p2pX(6.94f, vm), gui::p2pY(3.61f, vm),
                           gui::calcCharSize(vm), "Save");
    this->pmenu->addButton("LOAD", gui::p2pY(69.44f, vm), gui::p2pX(6.94f, vm), gui::p2pY(3.61f, vm),
                           gui::calcCharSize(vm), "Load");

}



void EditorState::initView() {
    this->view.setSize(sf::Vector2f(this->state_data->gfxSettings->resolution.width,
                                    this->state_data->gfxSettings->resolution.height));
    this->view.setCenter(this->state_data->gfxSettings->resolution.width / 2.f,
                         this->state_data->gfxSettings->resolution.height / 2.f);
}

void EditorState::initModes() {
    this->modes.push_back(new DefaultMode(this->state_data, this->tileMap, &this->editorStateData));
    this->modes.push_back(new EnemyEditorMode(this->state_data, this->tileMap, &this->editorStateData));

    this->activeMode = EditorModes::DEFAULT_MODE;
}

void EditorState::initVariables() {

    this->cameraSpeed = 400.f;

}

void EditorState::initEditorStateData() {
    this->editorStateData.view = &this->view;
    this->editorStateData.font = &this->font;
    this->editorStateData.keyTime = &this->keyTime;
    this->editorStateData.keyTimeMax = &this->keyTimeMax;

    this->editorStateData.mousePosGrid = &this->mousePosGrid;
    this->editorStateData.mousePosWindow = &this->mousePosWindow;
    this->editorStateData.mousePosScreen = &this->mousePosScreen;
    this->editorStateData.mousePosView = &this->mousePosView;
}

//Update
void EditorState::update(const float &dt) {

    this->updateMousePos(&this->view);
    this->updateKeytime(dt);
    this->updateInput(dt);

    if (!this->paused)//Unpaused
    {
        this->updateButtons();
        this->updateEditorInput(dt);
        this->updateModes(dt);
    } else //Paused
    {
        this->pmenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();
    }


}

void EditorState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->getKeyTime()) {

        if (!this->paused)
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->view.move(0, -this->cameraSpeed * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->view.move(-this->cameraSpeed * dt, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->view.move(0, this->cameraSpeed * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->view.move(this->cameraSpeed * dt, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (this->activeMode < this->modes.size() - 1)
        {
            this->activeMode++;
        }
        else
        {
            std::cout << "ERROR::EDITIORSTATE::CANNOT CHANGE MODE UP" << std::endl;
        }
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (this->activeMode > 0)
        {
            this->activeMode--;
        }
        else
        {
            std::cout << "ERROR::EDITIORSTATE::CANNOT CHANGE MODE DOWN" << std::endl;
        }
    }


}


void EditorState::updatePauseMenuButtons() {
    if (this->pmenu->isButtonPressed(("QUIT")) && this->getKeyTime())
        this->endState();
    if (this->pmenu->isButtonPressed(("SAVE")) && this->getKeyTime())
        this->tileMap->saveToFile("text.slmp");
    if (this->pmenu->isButtonPressed(("LOAD")) && this->getKeyTime())
        this->tileMap->loadFromFile("text.slmp");


}
void EditorState::updateModes(const float &dt) {
    this->modes[this->activeMode]->update(dt);
    std::cout << this->activeMode << std::endl;

}


//Render
void EditorState::render(sf::RenderTarget *target) {

    if (!target)
        target = this->window;

    target->setView(this->view);
    this->tileMap->render(*target, this->mousePosGrid, true);
    target->setView(this->window->getDefaultView());
    this->renderButtons(*target);
    this->renderGui(*target);
    this->renderModes(*target);


    if (this->paused) {
        //Pause Menu Render
        target->setView(this->window->getDefaultView());
        this->pmenu->render(*target);
    }
}


void EditorState::renderGui(sf::RenderTarget &target) {

}

void EditorState::renderButtons(sf::RenderTarget &target) {
    for (auto &it : this->buttons) {
        it.second->render(target);
    }
}

void EditorState::renderModes(sf::RenderTarget &target) {
    this->modes[this->activeMode]->render(target);

}















