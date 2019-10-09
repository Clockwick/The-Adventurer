//
// Created by Paratthakorn Sribunyong on 2/10/2019 AD.
//
#include "State.h"
#include "../GUI.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"

#ifndef GUJARUNSFML_EDITORSTATE_H
#define GUJARUNSFML_EDITORSTATE_H
class EditorState : public State
{
public:
    EditorState(sf::RenderWindow* window, std::stack <State*>* states);
    virtual ~EditorState();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void updateInput(const float& dt);
    void initButtons();
    void initBackground();
    void initVariables();
    void updateButtons();
    void renderButtons(sf::RenderTarget& target);


private:
    //Variables
    PauseMenu* pmenu;
    TileMap map;
    sf::Font font;
    gui::Button* gamestates_btn;
    std::map <std::string, gui::Button*> buttons;
    //Functions
    //Init
    void initFonts();
    void initPauseMenu();
    //Update
    void updatePauseMenuButtons();


private:

};
#endif //GUJARUNSFML_EDITORSTATE_H
