#ifndef GUJARUNSFML_ANIMATIONCOMPONENT_H
#define GUJARUNSFML_ANIMATIONCOMPONENT_H

#include <map>
#include <cstring>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class AnimationComponent
{
public:
    AnimationComponent();
    virtual ~AnimationComponent();



    //Functions
private:
    //Class
    class Animation
    {
    public:
        //Variables
        Animation(sf::Texture& animationSheet,float speed, int start_x, int start_y, int end_x, int end_y,int width, int height)
        : animationSheet(animationSheet), height(height), width(width), speed(speed)
        {
            this->startRect = sf::IntRect(start_x, start_y, width, height);
            this->endRect = sf::IntRect(end_x, end_y, width, height);

        }
        sf::Texture& animationSheet;
        sf::IntRect startRect;
        sf::IntRect endRect;

        float speed;
        int width;
        int height;
        //Functions
        void update(const float& dt)
        {


        }
        void pause();
        void reset();
    };
    //Variables
    std::map <std::string, Animation> animations;

    //Functions
};
#endif //GUJARUNSFML_ANIMATIONCOMPONENT_H
