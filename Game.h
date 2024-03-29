//
// Created by Paratthakorn Sribunyong on 31/8/2019 AD.
//

#ifndef GUJARUNSFML_GAME_H
#define GUJARUNSFML_GAME_H
#include "States/mainmenuState.h"
#include "States/GameState.h"
#include "States/NameState.h"
class Game{
public:

    //Constructor, DeConstructor
    Game();
    ~Game();
    //Function

    //Regular
    void endApps();
    //Render
    void render();
    //Core
    void run();
    //update
    void updateDt();
    void update();
    void updateSFMLEvent();



private:


    std::stack <State*> states;
    //INITIALIZATION
    void initWindow();
    void initstates();
    void initVariables();
    void initGraphicsSettings();
    void initStateData();
    //Variables
    sf::Clock dtClock;
    sf::Event event;
    sf::RenderWindow* window;
    GraphicsSettings gfxSettings;
    StateData state_data;

    float deltaTime;
    float gridSize;

    NameState* nameState;



};



#endif //GUJARUNSFML_GAME_H
