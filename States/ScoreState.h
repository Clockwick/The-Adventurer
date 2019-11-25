//
// Created by Paratthakorn Sribunyong on 23/11/2019 AD.
//

#ifndef GUJARUNSFML_SCORESTATE_H
#define GUJARUNSFML_SCORESTATE_H

#include "State.h"
#include "../Precom.h"
#include "../GUI.h"

class ScoreState : public State {
public:
    ScoreState(StateData *state_data);

    virtual ~ScoreState();

    void update(const float &dt);

    void render(sf::RenderTarget *target = nullptr);

    void updateInput(const float &dt);

    void loadFromFile(const std::string file_name);


private:
    void initVariables();
    void initGui();
    sf::Font font;
    sf::RectangleShape background;
    std::map <std::string, gui::Button*> buttons;
    std::map <std::string, gui::DropDownList*> dropDownLists;
    sf::Texture backgroundTexture;

};

#endif //GUJARUNSFML_SCORESTATE_H
