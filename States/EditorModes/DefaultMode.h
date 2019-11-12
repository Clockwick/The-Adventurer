//
// Created by Paratthakorn Sribunyong on 12/11/2019 AD.
//
#include "EditorMode.h"

#ifndef GUJARUNSFML_DEFAULTMODE_H
#define GUJARUNSFML_DEFAULTMODE_H

class DefaultMode : public EditorMode {
private:
    void initVariables();
    void initGui();

    sf::RectangleShape selectorRect;
    sf::IntRect textureRect;
    sf::Text cursorText;
    gui::TextureSelector* textureSelector;
    sf::RectangleShape sidebar;

    short type;
    bool collision;
    int layer;
    bool tileAddLock;


public:
    DefaultMode(StateData *state_data, TileMap* tile_map, EditorStateData* editor_state_data);

    virtual ~DefaultMode();

    //FUNCTIONS
    void update(const float &dt);

    void updateInput(const float &dt);

    void updateGui(const float &dt);

    void renderGui(sf::RenderTarget &target);

    void render(sf::RenderTarget *target = nullptr);

};

#endif //GUJARUNSFML_DEFAULTMODE_H
