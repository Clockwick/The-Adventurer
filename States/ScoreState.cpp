//
// Created by Paratthakorn Sribunyong on 23/11/2019 AD.
//

#include "ScoreState.h"

ScoreState::ScoreState(StateData *state_data) : State(state_data) {
    this->initVariables();
    this->initFonts();
    this->initGui();
    this->loadFromFile1("score.txt");
    this->loadFromFile("kit.txt");
    this->createTexts();


}

ScoreState::~ScoreState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end();++it){
        delete it->second;

    }
    auto it2 = this->dropDownLists.begin();
    for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end();++it2){
        delete it2->second;


    }
    auto it3 = this->texts.begin();
    for (it3 = this->texts.begin(); it3 != this->texts.end();++it3)
    {
        delete it3->second;
    }
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
//    for (int i = 0; i < 5;i++)
//    {
//        target->draw(this->playerText[i]);
//        target->draw(this->scoreText[i]);
//    }
    target->draw(this->playerList);
    target->draw(this->scoreList);
    target->draw(this->playerList1);
    target->draw(this->scoreList1);
    target->draw(this->playerList2);
    target->draw(this->scoreList2);
    target->draw(this->playerList3);
    target->draw(this->scoreList3);
    target->draw(this->playerList4);
    target->draw(this->scoreList4);
    target->draw(this->playerList5);
    target->draw(this->scoreList5);


    this->renderGui(*target);


}

void ScoreState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->endState();

}

void ScoreState::loadFromFile(const std::string file_name) {

    std::fstream myFile;

    myFile.open(file_name,std::ios::in);
    std::string temp;
    std::string tempString;
    int tempInt,p=1;
    bool S_state =false;
    while(getline(myFile,temp))
    {
        if(!S_state)
        {
            tempString = temp;
        }
        else
        {
            p=1;
            tempInt = 0;
            for(int i=temp.length()-1;i>=0;i--)
            {
                tempInt += (temp[i]-'0')*p;
                p*=10;
            }
            list.push_back(std::make_pair(tempInt,tempString));
        }
        S_state = !S_state;
    }
    myFile.close();

    //
    list.push_back(std::make_pair(score,playerName));
    std::sort(list.begin(),list.end());

    myFile.open(file_name,std::ios::out);
    for(int i=5;i>=1;i--)
    {
        myFile << list[i].second << std::endl << list[i].first << std::endl;
    }
    myFile.close();

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


    //1
    this->playerList1.setFont(this->font);
    this->playerList1.setPosition(gui::p2pX(30.f, vm), gui::p2pY(20.f, vm));
    this->playerList1.setCharacterSize(gui::calcCharSize(vm));
    this->playerList1.setFillColor(sf::Color::Black);
    this->playerList1.setString(this->list[4].second);
    this->scoreList1.setFont(this->font);
    this->scoreList1.setPosition(gui::p2pX(60.f, vm), gui::p2pY(20.f, vm));
    this->scoreList1.setCharacterSize(gui::calcCharSize(vm));
    this->scoreList1.setFillColor(sf::Color::Black);
    this->scoreList1.setString(std::to_string(this->list[4].first));

    //2
    this->playerList2.setFont(this->font);
    this->playerList2.setPosition(gui::p2pX(30.f, vm), gui::p2pY(30.f, vm));
    this->playerList2.setCharacterSize(gui::calcCharSize(vm));
    this->playerList2.setFillColor(sf::Color::Black);
    this->playerList2.setString(this->list[3].second);
    this->scoreList2.setFont(this->font);
    this->scoreList2.setPosition(gui::p2pX(60.f, vm), gui::p2pY(30.f, vm));
    this->scoreList2.setCharacterSize(gui::calcCharSize(vm));
    this->scoreList2.setFillColor(sf::Color::Black);
    this->scoreList2.setString(std::to_string(this->list[3].first));



    //3
    this->playerList3.setFont(this->font);
    this->playerList3.setPosition(gui::p2pX(30.f, vm), gui::p2pY(40.f, vm));
    this->playerList3.setCharacterSize(gui::calcCharSize(vm));
    this->playerList3.setFillColor(sf::Color::Black);
    this->playerList3.setString(this->list[2].second);
    this->scoreList3.setFont(this->font);
    this->scoreList3.setPosition(gui::p2pX(60.f, vm), gui::p2pY(40.f, vm));
    this->scoreList3.setCharacterSize(gui::calcCharSize(vm));
    this->scoreList3.setFillColor(sf::Color::Black);
    this->scoreList3.setString(std::to_string(this->list[2].first));



    //4
    this->playerList4.setFont(this->font);
    this->playerList4.setPosition(gui::p2pX(30.f, vm), gui::p2pY(50.f, vm));
    this->playerList4.setCharacterSize(gui::calcCharSize(vm));
    this->playerList4.setFillColor(sf::Color::Black);
    this->playerList4.setString(this->list[1].second);
    this->scoreList4.setFont(this->font);
    this->scoreList4.setPosition(gui::p2pX(60.f, vm), gui::p2pY(50.f, vm));
    this->scoreList4.setCharacterSize(gui::calcCharSize(vm));
    this->scoreList4.setFillColor(sf::Color::Black);
    this->scoreList4.setString(std::to_string(this->list[1].first));



    //5
    this->playerList5.setFont(this->font);
    this->playerList5.setPosition(gui::p2pX(30.f, vm), gui::p2pY(60.f, vm));
    this->playerList5.setCharacterSize(gui::calcCharSize(vm));
    this->playerList5.setFillColor(sf::Color::Black);
    this->playerList5.setString(this->list[0].second);
    this->scoreList5.setFont(this->font);
    this->scoreList5.setPosition(gui::p2pX(60.f, vm), gui::p2pY(60.f, vm));
    this->scoreList5.setCharacterSize(gui::calcCharSize(vm));
    this->scoreList5.setFillColor(sf::Color::Black);
    this->scoreList5.setString(std::to_string(this->list[0].first));




//    for (int i = 0; i < 5;i++)
//    {
//        this->scoreText[i].setFont(*this->font);
//        this->scoreText[i].setPosition(gui::p2pX(60.f, vm), gui::p2pY(20.f + (i * 10), vm));
//        this->scoreText[i].setCharacterSize(gui::calcCharSize(vm));
//        this->scoreText[i].setFillColor(sf::Color::Black);
//        this->scoreText[i].setString(std::to_string(this->list[i].first));
//
//        this->playerText[i].setFont(*this->font);
//        this->playerText[i].setPosition(gui::p2pX(30.f, vm), gui::p2pY(20.f + (i * 10), vm));
//        this->playerText[i].setCharacterSize(gui::calcCharSize(vm));
//        this->playerText[i].setFillColor(sf::Color::Black);
//        this->playerText[i].setString(this->list[i].second);
////        std::cout  << this->list[i].first << " " << this->list[i].second << std::endl;
//    }




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

void ScoreState::loadFromFile1(const std::string file_name) {
    std::fstream in_file;
    in_file.open(file_name);
    if (in_file.is_open())
    {
        in_file >> this->playerName >> this->score;
    }
    in_file.close();

}
