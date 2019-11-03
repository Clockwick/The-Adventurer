//
// Created by Paratthakorn Sribunyong on 31/10/2019 AD.
//

#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(Player *player) {
    this->player = player;

    this->initFonts();
    this->initHpbar();
    this->initExpBar();
    this->initLevelBar();

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
    float y = 170.f;

    this->hpBarMaxWidth = width;
    this->hpBarText.setFont(this->font);

    this->hpBarBack.setSize(sf::Vector2f(width, height));
    this->hpBarBack.setFillColor(sf::Color(50,50,50,200));
    this->hpBarBack.setPosition(x, y);

    this->hpBarInner.setSize(sf::Vector2f(width, height));
    this->hpBarInner.setFillColor(sf::Color(240,20,20,230));
    this->hpBarInner.setPosition(this->hpBarBack.getPosition());

    this->hpBarText.setPosition(this->hpBarText.getPosition().x + 35.f, this->hpBarText.getPosition().y + 170.f);
}


void PlayerGUI::update(const float &dt){
    this->updateHpbar();
    this->updateExpbar();
    this->updateLevelBar();
}

void PlayerGUI::updateHpbar() {
    float percent = static_cast<float>(this->player->getAttributeComponents()->hp) / static_cast<float>(this->player->getAttributeComponents()->hpMax);
    this->hpBarInner.setSize(sf::Vector2f(static_cast<float>(std::floor(this->hpBarMaxWidth * percent)), this->hpBarInner.getSize().y));

    this->hpBarString = std::to_string(this->player->getAttributeComponents()->hp) + " / " + std::to_string(this->player->getAttributeComponents()->hpMax);

    this->hpBarText.setString(this->hpBarString);
}


void PlayerGUI::render(sf::RenderTarget &target) {
    this->renderHpbar(target);
    this->renderExpbar(target);
    this->renderLevelBar(target);
}


void PlayerGUI::renderHpbar(sf::RenderTarget &target) {
    target.draw(this->hpBarBack);
    target.draw(this->hpBarInner);
    target.draw(this->hpBarText);
}

void PlayerGUI::updateExpbar() {
    float percent = static_cast<float>(this->player->getAttributeComponents()->exp) / static_cast<float>(this->player->getAttributeComponents()->expNext);
    this->expBarInner.setSize(sf::Vector2f(static_cast<float>(std::floor(this->expBarMaxWidth * percent)), this->expBarInner.getSize().y));

    this->expBarString = std::to_string(this->player->getAttributeComponents()->exp) + " / " + std::to_string(this->player->getAttributeComponents()->expNext);

    this->expBarText.setString(this->expBarString);
}


void PlayerGUI::renderExpbar(sf::RenderTarget &target) {
    target.draw(this->expBarBack);
    target.draw(this->expBarInner);
    target.draw(this->expBarText);
}

void PlayerGUI::initExpBar() {
    float width = 300.f;
    float height = 50.f;
    float x = 20.f;
    float y = 100.f;

    this->expBarMaxWidth = width;
    this->expBarText.setFont(this->font);

    this->expBarBack.setSize(sf::Vector2f(width, height));
    this->expBarBack.setFillColor(sf::Color(50,50,50,200));
    this->expBarBack.setPosition(x, y);

    this->expBarInner.setSize(sf::Vector2f(width, height));
    this->expBarInner.setFillColor(sf::Color(20,20,250,200));
    this->expBarInner.setPosition(this->expBarBack.getPosition());

    this->expBarText.setPosition(this->expBarText.getPosition().x + 35.f, this->expBarText.getPosition().y + 100.f);
}

void PlayerGUI::initLevelBar() {
    float width = 40.f;
    float height = 40.f;
    float x = 20.f;
    float y = 30.f;


    this->levelBarBack.setSize(sf::Vector2f(width, height));
    this->levelBarBack.setFillColor(sf::Color(50,50,50,200));
    this->levelBarBack.setPosition(x, y);

    this->levelBarText.setFont(this->font);
    this->levelBarText.setCharacterSize(26);
    this->levelBarText.setPosition(this->levelBarText.getPosition().x + 35.f, this->levelBarText.getPosition().y + 30.f);

}

void PlayerGUI::updateLevelBar() {
    this->levelBarString = std::to_string(this->player->getAttributeComponents()->level);
    this->levelBarText.setString(this->levelBarString);

}
void PlayerGUI::renderLevelBar(sf::RenderTarget &target) {
    target.draw(this->levelBarBack);
    target.draw(this->levelBarText);
}




