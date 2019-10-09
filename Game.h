//
// Created by Paratthakorn Sribunyong on 31/8/2019 AD.
//

#ifndef GUJARUNSFML_GAME_H
#define GUJARUNSFML_GAME_H
#include "States/mainmenuState.h"
#include "States/GameState.h"
class Game{
public:

    //Constructor, DeConstructor
    Game();
    ~Game();
    //Function

    //Regular
    void endApps();
    //Render
    void render();
    //Core
    void run();
    //update
    void updateDt();
    void update();
    void updateSFMLEvent();



private:


    class GraphicsSettings
    {
    public:

        GraphicsSettings()
        {
            this->title = "Fail";
            this->resolution = sf::VideoMode::getDesktopMode();
            this->fullscreen = false;
            this->vsync = false;
            this->framerateLimit = 120;
            this->contextSettings.antialiasingLevel = 0;
            this->videoModes = sf::VideoMode::getFullscreenModes();

        }


        //Variables
        sf::VideoMode resolution;
        bool vsync;
        bool fullscreen;
        unsigned framerateLimit;
        sf::ContextSettings contextSettings;
        std::vector <sf::VideoMode> videoModes;
        std::string title;



        //Functions


        void saveToFile(const std::string path)
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

                std::cout << "Import file from config/window.ini" << std::endl;



            }

            ofs.close();


        }

        void loadFromFile(const std::string path)
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

                std::cout << "Import file from config/window.ini" << std::endl;



            }

            ifs.close();

        }
    };
    std::stack <State*> states;
    //INITIALIZATION
    void initWindow();
    void initstates();
    void initVariables();
    void initGraphicsSettings();
    //Variables
    sf::Clock dtClock;
    sf::Event event;
    sf::RenderWindow* window;
    GraphicsSettings gfxSettings;

    float deltaTime;



};



#endif //GUJARUNSFML_GAME_H
