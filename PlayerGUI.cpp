//
// Created by Paratthakorn Sribunyong on 31/10/2019 AD.
//

#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(Player *player) {
    this->player = player;


    this->initFonts();
    this->initHpbar();

}

PlayerGUI::~PlayerGUI() {

}


void PlayerGUI::initFonts(){
    this->font.loadFromFile("fonts/RobotoCondensed-Regular.ttf");
}

void PlayerGUI::initHpbar() {

    float width = 300.f;
    float height = 50.f;
    float x = 20.f;
    float y = 20.f;

    this->hpBarBack.setSize(sf::Vector2f(width, height));
    this->hpBarBack.setFillColor(sf::Color(50,50,50,200));
    this->hpBarBack.setPosition(x, y);

    this->hpBarInner.setSize(sf::Vector2f(width, height));
    this->hpBarInner.setFillColor(sf::Color(240,20,20,230));
    this->hpBarInner.setPosition(this->hpBarBack.getPosition());

}


void PlayerGUI::update(const float &dt) {

}

void PlayerGUI::updateHpbar() {

}


void PlayerGUI::render(sf::RenderTarget &target) {
    this->renderHpbar(target);
}


void PlayerGUI::renderHpbar(sf::RenderTarget &target) {
    target.draw(this->hpBarBack);
    target.draw(this->hpBarInner);
}



