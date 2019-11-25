//
// Created by Paratthakorn Sribunyong on 31/10/2019 AD.
//

#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(Player *player, sf::VideoMode& vm, int& hp_bar, int& exp_bar, int& level_bar)
: vm(vm)
{
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

    float width = gui::p2pX(10.41f, vm);
    float height = gui::p2pY(2.7f, vm);
    float x = gui::p2pX(0.6f, vm);
    float y = gui::p2pY(9.4f, vm);

    this->hpBarMaxWidth = width;
    this->hpBarText.setFont(this->font);

    this->hpBarBack.setSize(sf::Vector2f(width, height));
    this->hpBarBack.setFillColor(sf::Color(50,50,50,200));
    this->hpBarBack.setPosition(x, y);

    this->hpBarInner.setSize(sf::Vector2f(width, height));
    this->hpBarInner.setFillColor(sf::Color(240,20,20,230));
    this->hpBarInner.setPosition(this->hpBarBack.getPosition());

    this->hpBarText.setPosition(this->hpBarText.getPosition().x + gui::p2pX(1.2f, vm), this->hpBarText.getPosition().y + gui::p2pY(9.4f, vm));
}


void PlayerGUI::update(const float &dt){
    this->updateHpbar();
    this->updateExpbar();
    this->updateLevelBar();
}

void PlayerGUI::updateHpbar() {
    std::cout << "Player HP{GUI}: " << this->player->getAttributeComponents()->hp << std::endl;
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
    float width = gui::p2pX(10.41f, vm);
    float height = gui::p2pY(2.7f, vm);
    float x = gui::p2pX(0.7f, vm);
    float y = gui::p2pY(5.5, vm);

    this->expBarMaxWidth = width;
    this->expBarText.setFont(this->font);

    this->expBarBack.setSize(sf::Vector2f(width, height));
    this->expBarBack.setFillColor(sf::Color(50,50,50,200));
    this->expBarBack.setPosition(x, y);

    this->expBarInner.setSize(sf::Vector2f(width, height));
    this->expBarInner.setFillColor(sf::Color(20,20,250,200));
    this->expBarInner.setPosition(this->expBarBack.getPosition());

    this->expBarText.setPosition(this->expBarText.getPosition().x + gui::p2pX(1.2f, vm), this->expBarText.getPosition().y + gui::p2pY(5.5, vm));
}

void PlayerGUI::initLevelBar() {
    float width = gui::p2pX(1.4f,vm);
    float height = gui::p2pY(2.2f,vm);
    float x = gui::p2pX(0.7f, vm);
    float y = gui::p2pY(1.7f,vm);


    this->levelBarBack.setSize(sf::Vector2f(width, height));
    this->levelBarBack.setFillColor(sf::Color(50,50,50,200));
    this->levelBarBack.setPosition(x, y);

    this->levelBarText.setFont(this->font);
    this->levelBarText.setCharacterSize(gui::calcCharSize(vm));
    this->levelBarText.setPosition(this->levelBarText.getPosition().x + gui::p2pX(1.2f ,vm), this->levelBarText.getPosition().y + gui::p2pY(1.7f ,vm));

}

void PlayerGUI::updateLevelBar() {
    this->levelBarString = std::to_string(this->player->getAttributeComponents()->level);
    this->levelBarText.setString(this->levelBarString);

}
void PlayerGUI::renderLevelBar(sf::RenderTarget &target) {
    target.draw(this->levelBarBack);
    target.draw(this->levelBarText);
}




