//
// Created by Paratthakorn Sribunyong on 7/10/2019 AD.
//

#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window, std::stack <State*>* states)
: State(window, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initGui();

}

SettingsState::~SettingsState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end();++it){
        delete it->second;


    }
    auto it2 = this->dropDownLists.begin();
    for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end();++it2){
        delete it2->second;


    }

}
//Accessors

//Functions
void SettingsState::initBackground() {
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

void SettingsState::initVariables() {


}
void SettingsState::initFonts() {
    if (!this->font.loadFromFile("fonts/RobotoCondensed-Regular.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }

    std::cout << "Successfully Loaded Fonts" << std::endl;


}

void SettingsState::initGui() {


    this->buttons["BACK"] = new gui::Button(550.f, 1520.f, 300.f, 150.f,
                                             &this->font, "Back", 36,
                                            sf::Color(255,255,255,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                            sf::Color(250,250,250,100),sf::Color(150,150,150,50),sf::Color(150,150,150,50)
    );
    this->buttons["APPLY"] = new gui::Button(134.f, 1520.f, 300.f, 150.f,
                                            &this->font, "Apply", 36,
                                             sf::Color(255,255,255,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                             sf::Color(250,250,250,100),sf::Color(150,150,150,50),sf::Color(150,150,150,50)
    );
    std::string li[] = {"1920x1080","  800x600","  640x480"};
    this->dropDownLists["RESOLUTION"] = new gui::DropDownList(100, 100, 300, 100, font, li, 3);

}
void SettingsState::update(const float &dt) {

    this->updateInput(dt);
    this->updateMousePos();
    this->updateGui(dt);





}

void SettingsState::render(sf::RenderTarget *target) {

    if(!target)
    {
        target = this->window;
    }

    target->draw(this->background);
    this->renderGui(*target);


    //For Checking (x,y) from Mouse

    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(16);
    mouseText.setFillColor(sf::Color::Black);
    std::stringstream ss;
    ss << "(" <<this->mousePosView.x << "," << this->mousePosView.y << ")" <<std::endl;
    mouseText.setString(ss.str());

    target->draw(mouseText);


}


void SettingsState::updateInput(const float &dt) {



}




void SettingsState::updateGui(const float& dt) {


    //Buttons
    for (auto &it : this->buttons){

        it.second->update(this->mousePosView) ;
    }

    //Buttons Functionality

    //Quit game
    if (this->buttons["BACK"]->isPressed())
    {
        this->endState();
    }

    if (this->buttons["APPLY"]->isPressed())
    {

    }
    //Drop Down Lists
    for (auto &it : this->dropDownLists){

        it.second->update(this->mousePosView, dt) ;
    }

    //Drop Down Lists




}

void SettingsState::renderGui(sf::RenderTarget &target) {
    for (auto &it : this->buttons){

        it.second->render(target) ;
    }
    for (auto &it2 : this->dropDownLists){

        it2.second->render(target) ;
    }
}


