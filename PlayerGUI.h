//
// Created by Paratthakorn Sribunyong on 31/10/2019 AD.
//

#ifndef GUJARUNSFML_PLAYERGUI_H
#define GUJARUNSFML_PLAYERGUI_H
#include "Entities/Player.h"
#include "GUI.h"

class Player;


class PlayerGUI {
public:
    PlayerGUI(Player* player);
    virtual ~PlayerGUI();

    //Functions
    void update(const float &dt);
    void updateHpbar();
    void updateExpbar();
    void updateLevelBar();

    void render(sf::RenderTarget &target);
    void renderHpbar(sf::RenderTarget &target);
    void renderExpbar(sf::RenderTarget &target);
    void renderLevelBar(sf::RenderTarget& target);


private:
    Player* player;

    //Level
    std::string levelBarString;
    sf::Text levelBarText;
    sf::RectangleShape levelBarBack;
    //Exp bar
    std::string expBarString;
    sf::Text expBarText;
    sf::RectangleShape expBarBack;
    sf::RectangleShape expBarInner;
    float expBarMaxWidth;
    //HP bar
    std::string hpBarString;
    sf::Text hpBarText;
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarInner;
    float hpBarMaxWidth;
    sf::Font font;

    //Functions
    void initFonts();
    void initHpbar();
    void initExpBar();
    void initLevelBar();

};
#endif //GUJARUNSFML_PLAYERGUI_H

