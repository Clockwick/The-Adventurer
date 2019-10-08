
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

    if(!this->backgroundTexture.loadFromFile("resources/images/background/Testbackground.jpg"))
    {
        std::cout << "Failed to load BackgroundImage" << std::endl;


    }
    this->background.setTexture(&this->backgroundTexture);
    std::cout << "Successfully Loaded BackgroundImage" << std::endl;
}

void Mainmenu::initVariables() {


}
void Mainmenu::initFonts() {
    if (!this->font.loadFromFile("fonts/RobotoCondensed-Regular.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }

    std::cout << "Successfully Loaded Fonts" << std::endl;


}

void Mainmenu::initButtons() {

    this->buttons["GAME_STATE"] = new gui::Button(1280.f,798.f-200.f,300.f,150.f,
                                             &this->font, "New Game", 36,
                                             sf::Color(70,70,70,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                             sf::Color(70,70,70,50),sf::Color(150,150,150,50),sf::Color(20,20,20,50)
    );
    this->buttons["SETTINGS_STATE"] = new gui::Button(1280.f,998.f-200.f,300.f,150.f,
                                                &this->font, "Settings", 36,
                                                sf::Color(70,70,70,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                                sf::Color(70,70,70,50 ),sf::Color(150,150,150,50),sf::Color(20,20,20,50)
    );
    this->buttons["EDITOR_STATE"] = new gui::Button(1280.f,1198.f-200.f,300.f,150.f,
                                               &this->font, "Editor", 36,
                                               sf::Color(70,70,70,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                               sf::Color(70,70,70,50 ),sf::Color(150,150,150,50),sf::Color(20,20,20,50)
    );
    this->buttons["EXIT_STATE"] = new gui::Button(1280.f,1398.f-200.f,300.f,150.f,
                                             &this->font, "Exit", 36,
                                             sf::Color(70,70,70,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                             sf::Color(70,70,70,50),sf::Color(150,150,150,50),sf::Color(20,20,20,50)


    );

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
    this->renderButtons(*target);

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




void Mainmenu::updateButtons() {


    for (auto &it : this->buttons){

        it.second->update(this->mousePosView) ;
    }
    if (this->buttons["GAME_STATE"]->isPressed())
    {
        this->states->push(new GameState(this->window, this->states));

    }
    if (this->buttons["SETTINGS_STATE"]->isPressed())
    {
        this->states->push(new SettingsState(this->window, this->states));
    }

    if (this->buttons["EDITOR_STATE"]->isPressed())
    {
        this->states->push(new EditorState(this->window, this->states));

    }

    if (this->buttons["EXIT_STATE"]->isPressed())
    {
        this->endState();
    }


}

void Mainmenu::renderButtons(sf::RenderTarget &target) {
    for (auto &it : this->buttons ){

        it.second->render(target) ;
    }
}


