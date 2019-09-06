
#include "mainmenuState.h"

Mainmenu::Mainmenu(sf::RenderWindow* window, std::stack <State*>* states)
: State(window, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initButtons();


}

Mainmenu::~Mainmenu() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end();++it){
        delete it->second;


    }
}
//Initializer
void Mainmenu::initBackground() {
    this->background.setSize(
            sf::Vector2f(
                    static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)
                    )
                    );

    if(!this->backgroundTexture.loadFromFile("resources/images/background/MainmenuBg.jpg"))
    {
        std::cout << "ERROR:MAINMENUSTATE Failed to load BackgroundImage" << std::endl;


    }
    this->background.setTexture(&this->backgroundTexture);
    std::cout << "Successfully Loaded BackgroundImage" << std::endl;
}

void Mainmenu::initVariables() {


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

    //For Checking (x,y) from Mouse
    /*
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(16);
    mouseText.setFillColor(sf::Color::Black);
    std::stringstream ss;
    ss << "(" <<this->mousePosView.x << "," << this->mousePosView.y << ")" <<std::endl;
    mouseText.setString(ss.str());

    target->draw(mouseText);
     */
}


void Mainmenu::updateInput(const float &dt) {



}


void Mainmenu::initFonts() {
    if (!this->font.loadFromFile("fonts/RobotoCondensed-Regular.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }
    else
    {
        std::cout << "Successfully Loaded Fonts" << std::endl;

    }
}

void Mainmenu::initButtons() {

    this->buttons["GAME_STATE"] = new Button(1280,798,300,150,
                                      &this->font, "Start Game",
                                      sf::Color(70,70,70,200),
                                      sf::Color(150,150,150,200),sf::Color(20,20,20,200)
    );
    this->buttons["SETTING_STATE"] = new Button(1280,998,300,150,
                                             &this->font, "Setting",
                                             sf::Color(70,70,70,200),
                                             sf::Color(150,150,150,200),sf::Color(20,20,20,200)
    );
    this->buttons["EXIT_STATE"] = new Button(1280,1198,300,150,
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
        this->endState();
    }

}

void Mainmenu::renderButtons(sf::RenderTarget *target) {
    for (auto &it : this->buttons ){

        it.second->render(target) ;
    }
}


