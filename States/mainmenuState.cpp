
#include "mainmenuState.h"

Mainmenu::Mainmenu(sf::RenderWindow* window)
: State(window)
{
    this->initFonts();

    this->gamestates_btn = new Button(1440/2 - 150,1080/2 - 300,300,150,
            &this->font, "Start Game",
            sf::Color(70,70,70,200),
            sf::Color(150,150,150,200),sf::Color(20,20,20,200)


            );
    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Red);

}

Mainmenu::~Mainmenu() {
    delete this->gamestates_btn;
}

void Mainmenu::update(const float &dt) {

    this->updateInput(dt);
    this->updateMousePos();


    this->gamestates_btn->update(this->mousePosView);


}

void Mainmenu::render(sf::RenderTarget *target) {

    if(!target)
    {
        target = this->window;
    }

    target->draw(this->background);
    this->gamestates_btn->render(target);
}


void Mainmenu::updateInput(const float &dt) {
    this->checkForQuit();


}

void Mainmenu::endState() {
    //Working!!



}

void Mainmenu::initFonts() {
    if (!this->font.loadFromFile("fonts/RobotoCondensed-Regular.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }
    else
    {
        std::cout << "Successfully Load Fonts" << std::endl;

    }
}
