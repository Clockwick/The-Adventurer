//IMPORT EVERYTHINGS

#ifndef GUJARUNSFML_STATE_H
#define GUJARUNSFML_STATE_H
#include "../Entities/Player.h"
#include "../GraphicsSettings.h"



class Player;
class GraphicsSettings;
class State;


class StateData
{
public:
    StateData() {}

    //Variables
    sf::RenderWindow* window;
    std::stack <State *>* states;
    GraphicsSettings* gfxSettings;
    float gridSize;


};

class State
{
public:
    State(StateData* state_data);
    virtual ~State();
    //Virtual Functions
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
    virtual void update(const float& dt) = 0;
    virtual void updateInput(const float& dt) = 0;
    virtual void updateMousePos(sf::View* view = NULL);
    virtual void updateKeytime(const float& dt);

    //Functions
    void endState();
    void pauseState();
    void unpauseState();

    //Accessor
    const bool& getQuit() const;
    const bool getKeyTime();



public:


protected:
    StateData* state_data;
    std::map <std::string, sf::Texture> textures;
    std::stack <State*>* states;
    sf::RenderWindow* window;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;

    bool quit;
    bool paused;
    float keyTime;
    float keyTimeMax;
    float gridSize;
private:

};



#endif //GUJARUNSFML_STATE_H
