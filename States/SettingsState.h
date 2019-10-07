//
// Created by Paratthakorn Sribunyong on 7/10/2019 AD.
//
#include "State.h"
#include "../GUI.h"
#ifndef GUJARUNSFML_SETTINGSSTATE_H
#define GUJARUNSFML_SETTINGSSTATE_H
class SettingsState : public State
{

public://Functions
    SettingsState(sf::RenderWindow* window, std::stack <State*>* states);
    virtual ~SettingsState();

    //Update && Render
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void renderGui(sf::RenderTarget& target);


public://Variables


private://Functions
    void initFonts();
    void initGui();
    void initBackground();
    void initVariables();

private://Variables


    sf::Font font;
    sf::RectangleShape background;
    gui::Button* gamestates_btn;
    std::map <std::string, gui::Button*> buttons;
    std::map <std::string, gui::DropDownList*> dropDownLists;
    sf::Texture backgroundTexture;

    //Functions



};
#endif //GUJARUNSFML_SETTINGSSTATE_H
