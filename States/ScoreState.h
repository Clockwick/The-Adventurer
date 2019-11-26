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
    void loadFromFile1(const std::string file_name);

    void updateGui(const float& dt);

    void renderGui(sf::RenderTarget& target);

private:
    void initVariables();
    void initGui();
    void initFonts();
    void createTexts();
    sf::Font font;
    sf::RectangleShape background;
    std::map <std::string, gui::Button*> buttons;
    std::map <std::string, gui::DropDownList*> dropDownLists;
    std::map <std::string, gui::TextGui*> texts;
    sf::Texture backgroundTexture;
    std::string playerName;
    std::string playerName1;
    std::string playerName2;
    std::string playerName3;
    std::string playerName4;
    int score;
    int score1;
    int score2;
    int score3;
    int score4;

    const sf::VideoMode& vm = this->state_data->gfxSettings->resolution;

    sf::Text playerText;
    sf::Text scoreText;

    sf::Text scoreList;
    sf::Text playerList;



};

#endif //GUJARUNSFML_SCORESTATE_H
