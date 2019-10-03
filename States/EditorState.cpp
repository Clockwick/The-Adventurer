//
// Created by Paratthakorn Sribunyong on 2/10/2019 AD.
//

#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow* window, std::stack <State*>* states)
        : State(window, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initButtons();


}

EditorState::~EditorState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end();++it){
        delete it->second;


    }
}
//Initializer
void EditorState::initBackground() {

}

void EditorState::initVariables() {


}

void EditorState::update(const float &dt) {

    this->updateInput(dt);
    this->updateMousePos();
    this->updateButtons();





}

void EditorState::render(sf::RenderTarget *target) {

    if(!target)
    {
        target = this->window;
    }

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


void EditorState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->quit = true;
    }

}


void EditorState::initFonts() {
    if (!this->font.loadFromFile("fonts/RobotoCondensed-Regular.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }
    else
    {
        std::cout << "Successfully Loaded Fonts" << std::endl;

    }
}

void EditorState::initButtons() {



}

void EditorState::updateButtons() {


    for (auto &it : this->buttons){

        it.second->update(this->mousePosView) ;
    }


}

void EditorState::renderButtons(sf::RenderTarget &target) {
    for (auto &it : this->buttons ){

        it.second->render(target) ;
    }
}

