
#include "mainmenuState.h"

Mainmenu::Mainmenu(StateData* state_data, sf::Event* event)
: State(state_data)
{
    this->initVariables();
    this->initLogo();
    this->initAudio();
    this->initFonts();
    this->initGui();
    this->resetGui();
    this->event = event;


}

Mainmenu::~Mainmenu() {
    for (auto it = this->buttons.begin(); it != this->buttons.end();++it){
        delete it->second;
    }
}
//Initializer
void Mainmenu::initVariables() {
    this->showBox = false;
}
void Mainmenu::initFonts() {
    if (!this->fonts["NORMAL"].loadFromFile("fonts/RobotoCondensed-Regular.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }
    if (!this->fonts["LOGO"].loadFromFile("fonts/karma.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD LOGO FONT" << std::endl;
    }

}

void Mainmenu::initGui() {
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


    this->buttons["GAME_STATE"] = new gui::Button(gui::p2pX(44.44f, vm),gui::p2pY(36.22f, vm),gui::p2pX(6.94f, vm),gui::p2pY(3.61f, vm),
                                             &this->fonts["LOGO"], "New Game", gui::calcCharSize(vm),
                                             sf::Color(0,0,0),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                             sf::Color(70,70,70,100),sf::Color(150,150,150,0),sf::Color(20,20,20,0)
    );
    this->buttons["SETTINGS_STATE"] = new gui::Button(gui::p2pX(44.44f, vm),gui::p2pY(47.33, vm),gui::p2pX(6.94f, vm),gui::p2pY(3.61f, vm),
                                                      &this->fonts["LOGO"], "Settings", gui::calcCharSize(vm),
                                                sf::Color(0,0,0),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                                sf::Color(70,70,70,100 ),sf::Color(150,150,150,0),sf::Color(20,20,20,0)
    );
    this->buttons["EDITOR_STATE"] = new gui::Button(gui::p2pX(44.44f, vm),gui::p2pY(58.44, vm),gui::p2pX(6.94f, vm),gui::p2pY(3.61f, vm),
                                                    &this->fonts["LOGO"], "Editor", gui::calcCharSize(vm),
                                               sf::Color(0,0,0),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                               sf::Color(70,70,70,100 ),sf::Color(150,150,150,0),sf::Color(20,20,20,0)
    );
    this->buttons["SCORE_STATE"] = new gui::Button(gui::p2pX(44.44f, vm),gui::p2pY(69.55, vm),gui::p2pX(6.94f, vm),gui::p2pY(3.61f, vm),
                                                   &this->fonts["LOGO"], "Score", gui::calcCharSize(vm),
                                                    sf::Color(0,0,0),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                                    sf::Color(70,70,70,100 ),sf::Color(150,150,150,0),sf::Color(20,20,20,0)
    );
    this->buttons["EXIT_STATE"] = new gui::Button(gui::p2pX(44.44f, vm),gui::p2pY(80.66f, vm),gui::p2pX(6.94f, vm),gui::p2pY(3.61f, vm),
                                                  &this->fonts["LOGO"], "Exit", gui::calcCharSize(vm),
                                             sf::Color(0,0,0),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                             sf::Color(70,70,70,100),sf::Color(150,150,150,0),sf::Color(20,20,20,0)


    );
    this->myName.setFont(this->fonts["LOGO"]);
    this->myName.setFillColor(sf::Color(50,50,50,100));
    this->myName.setPosition(gui::p2pX(60,vm), gui::p2pY(90,vm));
    this->myName.setCharacterSize(gui::calcCharSize(vm, 80));
    this->myName.setString("Paratthakorn Sribunyong 62010535");



}
void Mainmenu::update(const float &dt) {

    this->updateInput(dt);
    this->updateMousePos();
    this->updateButtons();

    if (this->showBox && !this->nameState->getQuit())
    {
        this->nameState->update(dt);
        this->nameState->getQuit();
    }



}

void Mainmenu::render(sf::RenderTarget *target) {

    if(!target)
        target = this->window;

    target->draw(this->background);
    target->draw(this->backgroundLogo);
    target->draw(this->logoText);
    target->draw(this->btnBackground);
    target->draw(this->myName);
    this->renderButtons(*target);

    if (this->showBox && !this->nameState->getQuit())
    {
        this->nameState->render(target);
    }




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

        it.second->update(this->mousePosWindow) ;
    }
    if (this->buttons["GAME_STATE"]->isPressed())
    {
        this->soundBt.play();
        this->musicBG.stop();
        this->showBox = true;
        this->nameState = new NameState(this->state_data, this->event, this->soundBt);

    }
    if (this->buttons["SETTINGS_STATE"]->isPressed())
    {
        this->soundBt.play();
        this->states->push(new SettingsState(this->state_data));
    }

    if (this->buttons["EDITOR_STATE"]->isPressed())
    {
        this->soundBt.play();
        this->states->push(new EditorState(this->state_data));


    }
    if (this->buttons["SCORE_STATE"]->isPressed())
    {
        this->soundBt.play();
        this->states->push(new ScoreState(this->state_data));
    }

    if (this->buttons["EXIT_STATE"]->isPressed())
    {
        this->soundBt.play();
        this->endState();
    }


}

void Mainmenu::renderButtons(sf::RenderTarget &target) {
    for (auto &it : this->buttons ){

        it.second->render(target) ;
    }

}

void Mainmenu::initAudio() {
    this->soundBufferBt.loadFromFile("resources/Audio/buttonclick.wav");
    this->soundBt.setBuffer(soundBufferBt);

    //Init Background Audio
    this->musicBG.openFromFile("resources/Audio/Theforestawake.ogg");
    this->musicBG.play();

}

void Mainmenu::resetGui() {

    /*
     *
     * Clear Gui element and re-initialize the GUI
     *
     * @return void
     *
     */
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end();++it){
        delete it->second;
    }
    this->buttons.clear();
    this->initGui();

}

void Mainmenu::initLogo() {
    this->logoText.setPosition(gui::p2pX(29.f, vm), gui::p2pY(16.f,vm));
    this->logoText.setCharacterSize(gui::calcCharSize(vm, 30));
    this->logoText.setFont(this->fonts["LOGO"]);
    this->logoText.setString("The Adventurer");

    this->backgroundLogo.setSize(sf::Vector2f(gui::p2pX(44.f, vm), gui::p2pY(15.f ,vm)));
    this->backgroundLogo.setPosition(this->logoText.getPosition().x - gui::p2pX(3.f, vm), this->logoText.getPosition().y);
    this->backgroundLogo.setFillColor(sf::Color(0,0,0,200));


}


