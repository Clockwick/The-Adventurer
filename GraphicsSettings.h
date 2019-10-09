//
// Created by Paratthakorn Sribunyong on 9/10/2019 AD.
//
#include "Precom.h"
#ifndef GUJARUNSFML_GRAPHICSSETTINGS_H
#define GUJARUNSFML_GRAPHICSSETTINGS_H
class GraphicsSettings
{
public:

    GraphicsSettings();
    void saveToFile(const std::string path);
    void loadFromFile(const std::string path);


    //Variables
    sf::VideoMode resolution;
    bool vsync;
    bool fullscreen;
    unsigned framerateLimit;
    sf::ContextSettings contextSettings;
    std::vector <sf::VideoMode> videoModes;
    std::string title;



    //Functions


private:

};
#endif //GUJARUNSFML_GRAPHICSSETTINGS_H
