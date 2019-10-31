//
// Created by Paratthakorn Sribunyong on 31/10/2019 AD.
//

#ifndef GUJARUNSFML_PLAYERGUI_H
#define GUJARUNSFML_PLAYERGUI_H
#include "Entities/Player.h"
#include "Gui.h"

class Player;


class PlayerGUI {
public:
    PlayerGUI(Player* player);
    virtual ~PlayerGUI();

    //Functions
    void update(const float &dt);
    void updateHpbar();


    void render(sf::RenderTarget &target);
    void renderHpbar(sf::RenderTarget &target);

private:
    Player* player;

    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarInner;
    sf::Font font;

    //Functions
    void initFonts();
    void initHpbar();

};
#endif GUJ ARUNSFML_PLAYERGUI_H

