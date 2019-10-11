//
// Created by Paratthakorn Sribunyong on 2/10/2019 AD.
//
#include "State.h"
#include "../GUI.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"

#ifndef GUJARUNSFML_EDITORSTATE_H
#define GUJARUNSFML_EDITORSTATE_H

class GUI;
class TileMap;
class PauseMenu;
class State;

class EditorState : public State
{
public:
    EditorState(StateData* state_data);
    virtual ~EditorState();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void updateInput(const float& dt);
    void updateGui();
    void renderGui(sf::RenderTarget& target);
    void updateButtons();
    void renderButtons(sf::RenderTarget& target);



private:
    //Variables
    PauseMenu* pmenu;
    TileMap* tileMap;
    sf::Font font;
    gui::Button* gamestates_btn;
    std::map <std::string, gui::Button*> buttons;
    sf::RectangleShape selectorRect;
    //Functions
    //Init
    void initFonts();
    void initPauseMenu();
    void initTileMap();
    void initBackground();
    void initVariables();
    void initButtons();
    void initGui();

    //Update
    void updatePauseMenuButtons();


private:

};
#endif //GUJARUNSFML_EDITORSTATE_H
