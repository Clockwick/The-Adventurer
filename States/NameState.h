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
    sf::RectangleShape bg;
    sf::RectangleShape box;
    sf::RectangleShape inputBox;
    sf::RectangleShape cursorText;
    sf::Text textIntro;

    sf::Clock clock;
    sf::Font font;
    float totalTime;
    bool blink;
    float blinkq;

    bool quit;
    char last_char;
    std::string input;
    sf::Text inputText;

    const sf::VideoMode& vm = this->state_data->gfxSettings->resolution;

    void initBox();
    void initVariables();



public:
    NameState(StateData* state_data);
    virtual ~NameState();


    void update(const float& dt);
    void render(sf::RenderTarget* target);
    void updateInput(const float& dt);
    void updateCursor();

    const bool& getQuit();

};



#endif //GUJARUNSFML_NAMESTATE_H
