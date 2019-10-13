//
// Created by Paratthakorn Sribunyong on 7/10/2019 AD.
//

#include "SettingsState.h"

SettingsState::SettingsState(StateData* state_data)
: State(state_data)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initGui();
    this->initText();

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
    this->modes = sf::VideoMode::getFullscreenModes();

}
void SettingsState::initText()
{
    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(sf::Vector2f(100.f,100.f));
    this->optionsText.setCharacterSize(45);
    this->optionsText.setFillColor(sf::Color(255,255,255,200));


    this->optionsText.setString(
            "Resolution \n\n\n"
            "FullScreen \n\n\n"
            "AntiAliasing \n\n\n"
            "VSync \n\n\n"
            );
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
    std::vector <std::string> modes_str;
    for(auto &i : this->modes)
    {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }
    std::string li[] = {"1920x1080","  800x600","  640x480"};
    this->dropDownLists["RESOLUTION"] = new gui::DropDownList(450, 70, 300, 100, font, modes_str.data(), modes_str.size());

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

    target->draw(this->optionsText);
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

        it.second->update(this->mousePosWindow) ;
    }

    //Buttons Functionality

    //Quit game
    if (this->buttons["BACK"]->isPressed())
    {
        this->endState();
    }
    //Test Remove later!!
    if (this->buttons["APPLY"]->isPressed())
    {
        this->state_data->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
        this->window->create(this->state_data->gfxSettings->resolution, this->state_data->gfxSettings->title, sf::Style::Default);
    }
    //Drop Down Lists
    for (auto &it : this->dropDownLists){

        it.second->update(this->mousePosWindow, dt) ;
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




