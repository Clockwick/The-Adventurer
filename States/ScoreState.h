//
// Created by Paratthakorn Sribunyong on 23/11/2019 AD.
//

#ifndef GUJARUNSFML_SCORESTATE_H
#define GUJARUNSFML_SCORESTATE_H

#include "State.h"
#include "../Precom.h"

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

};

#endif //GUJARUNSFML_SCORESTATE_H
