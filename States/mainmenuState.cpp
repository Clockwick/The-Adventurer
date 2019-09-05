
#include "mainmenuState.h"

Mainmenu::Mainmenu(sf::RenderWindow* window, std::stack <State*>* states)
: State(window, states)
{
    this->initFonts();
    this->initButtons();


    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Red);

}

Mainmenu::~Mainmenu() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end();++it){
        delete it->second;


    }
}

void Mainmenu::update(const float &dt) {

    this->updateInput(dt);
    this->updateMousePos();
    this->updateButtons();





}

void Mainmenu::render(sf::RenderTarget *target) {

    if(!target)
    {
        target = this->window;
    }

    target->draw(this->background);
    this->renderButtons(target);
}


void Mainmenu::updateInput(const float &dt) {
    this->checkForQuit();


}

void Mainmenu::endState() {
    //Working!!
     std::cout << "Ending MainMenuState" << std::endl;


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

void Mainmenu::initButtons() {
    this->buttons["GAME_STATE"] = new Button(1440/2 - 150,1080/2 - 300,300,150,
                                      &this->font, "Start Game",
                                      sf::Color(70,70,70,200),
                                      sf::Color(150,150,150,200),sf::Color(20,20,20,200)
    );
    this->buttons["EXIT_STATE"] = new Button(1440/2 - 150,1080/2 - 100,300,150,
                                             &this->font, "Exit",
                                             sf::Color(70,70,70,200),
                                             sf::Color(150,150,150,200),sf::Color(20,20,20,200)

    );

}

void Mainmenu::updateButtons() {


    for (auto &it : this->buttons){

        it.second->update(this->mousePosView) ;
    }
    if (this->buttons["GAME_STATE"]->isPressed())
    {
        this->states->push(new GameState(this->window, this->states));

    }

    if (this->buttons["EXIT_STATE"]->isPressed())
    {
        this->quit = 1;
    }
}

void Mainmenu::renderButtons(sf::RenderTarget *target) {
    for (auto &it : this->buttons ){

        it.second->render(target) ;
    }
}
