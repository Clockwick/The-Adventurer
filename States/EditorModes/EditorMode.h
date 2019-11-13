#ifndef GUJARUNSFML_EDITORMODE_H
#define GUJARUNSFML_EDITORMODE_H

#include "../State.h"
#include "../../Map/TileMap.h"
#include "../../GUI.h"

class EditorStateData
{
public:
    EditorStateData() {}

    //Variables
    sf::Vector2i* mousePosScreen;
    sf::Vector2i* mousePosWindow;
    sf::Vector2f* mousePosView;
    sf::Vector2i* mousePosGrid;

    float* keyTime;
    float* keyTimeMax;

    sf::View* view;
    sf::Font* font;

};
class EditorMode
{
private:


protected:
    StateData* stateData;
    TileMap* tileMap;
    sf::Font* font;
    EditorStateData* editorStateData;

public:
    EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~EditorMode();

    //FUNCTIONS
    virtual void update(const float& dt) = 0;
    virtual void updateInput(const float& dt) = 0;
    virtual void updateGui(const float &dt) = 0;

    virtual void renderGui(sf::RenderTarget& target) = 0;
    virtual void render(sf::RenderTarget& target) = 0;

    const bool getKeyTime();



};
#endif
