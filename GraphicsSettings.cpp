//
// Created by Paratthakorn Sribunyong on 9/10/2019 AD.
//

#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
    this->title = "Fail";
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->vsync = false;
    this->framerateLimit = 120;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();

}

//Functions
void GraphicsSettings::saveToFile(const std::string path)
{
    std::ofstream ofs(path);
    /* IMPORT FROM "graphics.ini" FILE*/



    if (ofs.is_open())
    {
        ofs << this->title;
        ofs << this->resolution.width << " " << this->resolution.height;
        ofs << this->fullscreen;
        ofs << this->framerateLimit;
        ofs << this->vsync;
        ofs << this->contextSettings.antialiasingLevel;

    }

    ofs.close();


}

void GraphicsSettings::loadFromFile(const std::string path)
{
    std::ifstream ifs(path);
    /* IMPORT FROM "graphics.ini" FILE*/



    if (ifs.is_open())
    {
        std::getline(ifs, this->title);
        ifs >> this->resolution.width >> this->resolution.height;
        ifs >> this->fullscreen;
        ifs >> this->framerateLimit;
        ifs >> this->vsync;
        ifs >> this->contextSettings.antialiasingLevel;

    }

    ifs.close();

}
