
#include "mainmenuState.h"

Mainmenu::Mainmenu(StateData* state_data)
: State(state_data)
{
    this->initVariables();
    this->initAudio();
    this->initFonts();
    this->initGui();
    this->resetGui();


}

Mainmenu::~Mainmenu() {
    for (auto it = this->buttons.begin(); it != this->buttons.end();++it){
        delete it->second;
    }
    delete this->nameState;
}
//Initializer
void Mainmenu::initVariables() {
    this->showBox = false;
}
void Mainmenu::initFonts() {
    if (!this->font.loadFromFile("fonts/RobotoCondensed-Regular.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }

}

void Mainmenu::initGui() {
    const sf::VideoMode& vm = this->state_data->gfxSettings->resolution;
    this->background.setSize(
            sf::Vector2f(
                    static_cast<float>(vm.width),
                    static_cast<float>(vm.height)
            )
    );

    if(!this->backgroundTexture.loadFromFile("resources/images/background/Testbackground.jpg"))
    {
        std::cout << "Failed to load BackgroundImage" << std::endl;
    }
    this->background.setTexture(&this->backgroundTexture);


    this->buttons["GAME_STATE"] = new gui::Button(gui::p2pX(44.44f, vm),gui::p2pY(33.22f, vm),gui::p2pX(6.94f, vm),gui::p2pY(3.61f, vm),
                                             &this->font, "New Game", gui::calcCharSize(vm),
                                             sf::Color(70,70,70,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                             sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0)
    );
    this->buttons["SETTINGS_STATE"] = new gui::Button(gui::p2pX(44.44f, vm),gui::p2pY(44.33, vm),gui::p2pX(6.94f, vm),gui::p2pY(3.61f, vm),
                                                &this->font, "Settings", gui::calcCharSize(vm),
                                                sf::Color(70,70,70,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                                sf::Color(70,70,70,0 ),sf::Color(150,150,150,0),sf::Color(20,20,20,0)
    );
    this->buttons["EDITOR_STATE"] = new gui::Button(gui::p2pX(44.44f, vm),gui::p2pY(55.44, vm),gui::p2pX(6.94f, vm),gui::p2pY(3.61f, vm),
                                               &this->font, "Editor", gui::calcCharSize(vm),
                                               sf::Color(70,70,70,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                               sf::Color(70,70,70,0 ),sf::Color(150,150,150,0),sf::Color(20,20,20,0)
    );
    this->buttons["EXIT_STATE"] = new gui::Button(gui::p2pX(44.44f, vm),gui::p2pY(66.55f, vm),gui::p2pX(6.94f, vm),gui::p2pY(3.61f, vm),
                                             &this->font, "Exit", gui::calcCharSize(vm),
                                             sf::Color(70,70,70,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                             sf::Color(70,70,70,0),sf::Color(150,150,150,0),sf::Color(20,20,20,0)


    );

}
void Mainmenu::update(const float &dt) {

    this->updateInput(dt);
    this->updateMousePos();
    this->updateButtons();

    if (this->showBox && !this->getQuit())
    {
        this->nameState->update(dt);
        this->getQuit();
    }



}

void Mainmenu::render(sf::RenderTarget *target) {

    if(!target)
        target = this->window;

    target->draw(this->background);
    target->draw(this->btnBackground);
    this->renderButtons(*target);

    if (this->showBox && !this->getQuit())
    {
        this->getQuit();
        this->nameState->render(target);
    }
    std::cout << this->getQuit() << std::endl;
//    std::cout << this->getQuit() << "\n";



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
        this->nameState = new NameState(this->state_data);

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
//    this->musicBG.play();

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


