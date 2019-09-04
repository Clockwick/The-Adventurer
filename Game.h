//
// Created by Paratthakorn Sribunyong on 31/8/2019 AD.
//

#ifndef GUJARUNSFML_GAME_H
#define GUJARUNSFML_GAME_H
#include "States/mainmenuState.h"

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

    //Variables
    sf::Clock dtClock;
    sf::Event event;
    sf::RenderWindow* window;

    float deltaTime;


};



#endif //GUJARUNSFML_GAME_H
