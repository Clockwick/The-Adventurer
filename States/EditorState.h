//
// Created by Paratthakorn Sribunyong on 2/10/2019 AD.
//
#include "State.h"
#include "../GUI.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"
#include "EditorModes/EditorMode.h"
#include "EditorModes/DefaultMode.h"

#ifndef GUJARUNSFML_EDITORSTATE_H
#define GUJARUNSFML_EDITORSTATE_H

class GUI;
class TileMap;
class PauseMenu;
class State;
class Tile;

enum EditorModes {DEFAULT_MODE = 0, ENEMY_MODE};

class EditorState : public State
{
public:
    EditorState(StateData* state_data);
    virtual ~EditorState();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void updateInput(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void updateButtons();
    void updateModes(const float& dt);
    void renderModes(sf::RenderTarget& target);
    void renderButtons(sf::RenderTarget& target);
    void updateEditorInput(const float &dt);



private:
    //Variables
    EditorStateData editorStateData;
    PauseMenu* pmenu;
    TileMap* tileMap;
    sf::Font font;
    std::map <std::string, gui::Button*> buttons;

    sf::View view;
    short type;
    float cameraSpeed;


    std::vector<EditorMode*> modes;
    //Functions

    //Init
    void initFonts();
    void initView();
    void initPauseMenu();
    void initTileMap();
    void initVariables();
    void initModes();
    void initEditorStateData();

    //Update
    void updatePauseMenuButtons();


protected:

};
#endif //GUJARUNSFML_EDITORSTATE_H
