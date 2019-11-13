
#ifndef GUJARUNSFML_ENEMYEDITORMODE_H
#define GUJARUNSFML_ENEMYEDITORMODE_H

#include "EditorMode.h"
#include "../../EnemySpawner.h"

class EnemyEditorMode : public EditorMode
{
private:
    sf::RectangleShape selectorRect;
    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::IntRect textureRect;//

    int type;
    int amount;
    int timeToSpawn;
    float maxDistance;

    void initGui();
    void initVariables();
public:
    EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~EnemyEditorMode();

    //FUNCTIONS
    void update(const float &dt);

    void updateInput(const float &dt);

    void updateGui(const float &dt);

    void renderGui(sf::RenderTarget &target);

    void render(sf::RenderTarget& target);

};

#endif //GUJARUNSFML_ENEMYEDITORMODE_H
