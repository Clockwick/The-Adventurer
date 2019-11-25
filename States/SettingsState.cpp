//
// Created by Paratthakorn Sribunyong on 7/10/2019 AD.
//

#include "SettingsState.h"

SettingsState::SettingsState(StateData* state_data)
: State(state_data)
{
    this->initVariables();
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


void SettingsState::initVariables() {
    this->modes = sf::VideoMode::getFullscreenModes();

}

void SettingsState::initFonts() {
    if (!this->font.loadFromFile("fonts/karma.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }

    std::cout << "Successfully Loaded Fonts" << std::endl;


}

void SettingsState::initGui() {
    const sf::VideoMode& vm = this->state_data->gfxSettings->resolution;

    //Background

    this->background.setSize(
            sf::Vector2f(
                    static_cast<float>(vm.width),
                    static_cast<float>(vm.height)
            )
    );

    if(!this->backgroundTexture.loadFromFile("resources/images/background/MainmenuBg.jpg"))
    {
        std::cout << "Failed to load BackgroundImage" << std::endl;


    }
    this->background.setTexture(&this->backgroundTexture);
    std::cout << "Successfully Loaded BackgroundImage" << std::endl;

    //Buttons
    this->buttons["BACK"] = new gui::Button(gui::p2pX(19.1f, vm), gui::p2pY(84.44, vm), gui::p2pX(10.416f, vm), gui::p2pY(8.33f, vm),
                                             &this->font, "Back", gui::calcCharSize(vm),
                                            sf::Color(0,0,0,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                            sf::Color(250,250,250,100),sf::Color(150,150,150,50),sf::Color(150,150,150,50)
    );
    this->buttons["APPLY"] = new gui::Button(gui::p2pX(4.65f, vm), gui::p2pY(84.44f, vm), gui::p2pX(10.416f, vm), gui::p2pY(8.33f, vm),
                                            &this->font, "Apply", gui::calcCharSize(vm),
                                             sf::Color(0,0,0,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                             sf::Color(250,250,250,100),sf::Color(150,150,150,50),sf::Color(150,150,150,50)
    );
    //Modes
    std::vector <std::string> modes_str;
    for(auto &i : this->modes)
    {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }

    //DropDownList
    this->dropDownLists["RESOLUTION"] = new gui::DropDownList(gui::p2pX(15.625f, vm), gui::p2pY(5.55f, vm), gui::p2pX(10.416f, vm), gui::p2pY(3.05f, vm), font, modes_str.data(), modes_str.size());
    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(sf::Vector2f(gui::p2pX(3.5f, vm),gui::p2pY(5.5f, vm)));
    this->optionsText.setCharacterSize(gui::calcCharSize(vm));
    this->optionsText.setFillColor(sf::Color(0,0,0,200));


    this->optionsText.setString(
            "Resolution \n\n\n"
            "FullScreen \n\n\n"
            "AntiAliasing \n\n\n"
            "VSync \n\n\n"
    );

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
        this->resetGui();
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

void SettingsState::resetGui() {
    /*
     *
     * Clear Gui element and re-initialize the GUI
     *
     * @return void
     *
     */
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
    this->buttons.clear();

    auto it2 = this->dropDownLists.begin();
    for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
    {
        delete it2->second;
    }
    this->dropDownLists.clear();

    this->initGui();

}




