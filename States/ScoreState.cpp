//
// Created by Paratthakorn Sribunyong on 23/11/2019 AD.
//

#include "ScoreState.h"

ScoreState::ScoreState(StateData *state_data) : State(state_data) {
    this->initVariables();
    this->initFonts();
    this->initGui();

    this->loadFromFile("kit.txt");
    this->loadFromFile1("score.txt");
    this->createTexts();

}

ScoreState::~ScoreState() {

}

void ScoreState::update(const float &dt) {

    this->updateInput(dt);
    this->updateMousePos();
    this->updateGui(dt);

}

void ScoreState::render(sf::RenderTarget *target) {
    if(!target)
    {
        target = this->window;
    }
    target->draw(this->background);
    target->draw(this->playerList);
    target->draw(this->scoreList);
    target->draw(this->playerText);
    target->draw(this->scoreText);

    this->renderGui(*target);


}

void ScoreState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->endState();

}

void ScoreState::loadFromFile(const std::string file_name) {
        std::ifstream in_file;
        in_file.open(file_name);
        if (in_file.is_open())
        {
            std::string player_name = "TU";
            std::string player_name1 = "";
            std::string player_name2 = "";
            std::string player_name3 = "";
            std::string player_name4 = "";
            //Load
            while (in_file >> player_name >> player_name1 >> player_name2 >> player_name3 >> player_name4)
            {
                this->playerName = player_name;
                this->playerName1 = player_name1;
                this->playerName2 = player_name2;
                this->playerName3 = player_name3;
                this->playerName4 = player_name4;

            }
        }
        in_file.close();
}
void ScoreState::loadFromFile1(const std::string file_name) {
    std::ifstream in_file;
    in_file.open(file_name);
    if (in_file.is_open())
    {
        int score = 0;
        int score1 = 0;
        int score2 = 0;
        int score3 = 0;
        int score4 = 0;

        while(in_file >> score >> score1 >> score2 >> score3 >> score4)
        {
            this->score = score;
            this->score1 = score1;
            this->score2 = score2;
            this->score3 = score3;
            this->score4 = score4;
        }

    }
    in_file.close();
}




void ScoreState::initVariables() {


}

void ScoreState::initGui() {
    if (!this->font.loadFromFile("fonts/karma.ttf"))
    {
        std::cout << "ERROR::MAINMENU::COULD NOT LOAD FONT" << std::endl;
    }

    std::cout << "Successfully Loaded Fonts" << std::endl;

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

    this->buttons["BACK"] = new gui::Button(gui::p2pX(80.f, vm), gui::p2pY(84.44, vm), gui::p2pX(10.416f, vm), gui::p2pY(8.33f, vm),
                                            &this->font, "Back", gui::calcCharSize(vm),
                                            sf::Color(0,0,0,200),sf::Color(150,150,150,250),sf::Color(20,20,20,50),
                                            sf::Color(250,250,250,100),sf::Color(150,150,150,50),sf::Color(150,150,150,50)
    );


}

void ScoreState::initFonts() {
    if (!this->font.loadFromFile("Fonts/ENDEAVOURFOREVER.TTF"))
    {
        std::cout << "can't load font" << std::endl;
    }
}

void ScoreState::createTexts() {
    this->playerList.setFont(this->font);
    this->playerList.setPosition(gui::p2pX(30.f, vm), gui::p2pY(10.f, vm));
    this->playerList.setCharacterSize(gui::calcCharSize(vm));
    this->playerList.setFillColor(sf::Color::Black);
    this->playerList.setString("Player");
    this->scoreList.setFont(this->font);
    this->scoreList.setPosition(gui::p2pX(60.f, vm), gui::p2pY(10.f, vm));
    this->scoreList.setCharacterSize(gui::calcCharSize(vm));
    this->scoreList.setFillColor(sf::Color::Black);
    this->scoreList.setString("Score");

    this->scoreText.setFont(this->font);
    this->scoreText.setPosition(gui::p2pX(60.f, vm), gui::p2pY(20.f, vm));
    this->scoreText.setCharacterSize(gui::calcCharSize(vm));
    this->scoreText.setFillColor(sf::Color::Black);
    this->scoreText.setString(std::to_string(this->score));

    this->playerText.setFont(this->font);
    this->playerText.setPosition(gui::p2pX(30.f, vm), gui::p2pY(20.f, vm));
    this->playerText.setCharacterSize(gui::calcCharSize(vm));
    this->playerText.setFillColor(sf::Color::Black);
    this->playerText.setString(this->playerName);

    this->texts["1"] = new gui::TextGui(gui::p2pX(10.f, vm) , gui::p2pY(20.f, vm), &this->font, gui::calcCharSize(vm), sf::Color::Black, sf::Color::Transparent, "1.");
    this->texts["2"] = new gui::TextGui(gui::p2pX(10.f, vm) , gui::p2pY(30.f, vm), &this->font, gui::calcCharSize(vm), sf::Color::Black, sf::Color::Transparent, "2.");
    this->texts["3"] = new gui::TextGui(gui::p2pX(10.f, vm) , gui::p2pY(40.f, vm), &this->font, gui::calcCharSize(vm), sf::Color::Black, sf::Color::Transparent, "3.");
    this->texts["4"] = new gui::TextGui(gui::p2pX(10.f, vm) , gui::p2pY(50.f, vm), &this->font, gui::calcCharSize(vm), sf::Color::Black, sf::Color::Transparent, "4.");
    this->texts["5"] = new gui::TextGui(gui::p2pX(10.f, vm) , gui::p2pY(60.f, vm), &this->font, gui::calcCharSize(vm), sf::Color::Black, sf::Color::Transparent, "5.");






}

void ScoreState::updateGui(const float &dt) {
    for (auto &it : this->buttons){

        it.second->update(this->mousePosWindow) ;
    }

    //Buttons Functionality

    //Quit game
    if (this->buttons["BACK"]->isPressed())
    {
        this->endState();
    }

}

void ScoreState::renderGui(sf::RenderTarget&target) {
    for (auto &it : this->buttons){
        it.second->render(target) ;
    }
    for (auto &it2 : this->texts){
        it2.second->render(target);
    }
}
