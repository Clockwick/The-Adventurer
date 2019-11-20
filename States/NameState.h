//
// Created by Paratthakorn Sribunyong on 19/11/2019 AD.
//

#ifndef GUJARUNSFML_NAMESTATE_H
#define GUJARUNSFML_NAMESTATE_H
#include "../Precom.h"
#include "GameState.h"
class NameState : public State
{
private:
    sf::RectangleShape box;
    sf::RectangleShape inputBox;
    sf::RectangleShape cursorText;
    sf::Text textIntro;

    sf::Clock clock;




public:
    NameState(StateData* state_data);
    virtual ~NameState();

    void initBox();
    void update(const float& dt);
    void render(sf::RenderTarget* target);
    void updateInput(const float& dt);

    const bool& getQuit();
    bool quit;

};



#endif //GUJARUNSFML_NAMESTATE_H
