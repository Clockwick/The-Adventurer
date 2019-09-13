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
    AnimationComponent(sf::Sprite& sprite, sf::Texture& animation_sheet);
    virtual ~AnimationComponent();
    void update(const float& dt);
    void startAnimation(const std::string animation);
    void pauseAnimation(const std::string animation);
    void resetAnimation(const std::string animation);
    void addAnimation(const std::string key);

    //Functions
private:
    //Class
    class Animation
    {
    public:
        //Constructor
        Animation(sf::Sprite& sprite, sf::Texture& animationSheet, float animation_timer, int start_x, int start_y, int end_x, int end_y,int width, int height)
        : animationSheet(animationSheet), height(height), width(width),  animation_timer(animation_timer), sprite(sprite)
        {
            this->startRect = sf::IntRect(start_x, start_y, width, height);
            this->currentRect = this->startRect;
            this->endRect = sf::IntRect(end_x, end_y, width, height);
            this->startRect == this->endRect;
            this->sprite.setTexture(this->animationSheet, true);
            this->sprite.setTextureRect(this->startRect);
        }
        //Variables
        sf::Texture& animationSheet;
        sf::IntRect startRect;
        sf::IntRect currentRect;
        sf::IntRect endRect;

        sf::Sprite& sprite;
        float speed;
        float timer;
        float animation_timer;
        int width;
        int height;
        //Functions
        void update(const float& dt)
        {
            //Update timer
            this->timer = 10.0f * dt;
            if (this->timer >= this->animation_timer)
            {
                //reset Timer
                this->timer = 0.0f;
                //Animate
                if (this->currentRect != this->endRect) {
                    this->currentRect.left += this->width;
                }
                else //reset
                {
                    this->currentRect.left = this->startRect.left;

                }
            }

        }
        void pause();
        void reset();
    };
    //Variables
    std::map <std::string, Animation> animations;
    sf::Sprite& sprite;
    sf::Texture& animation_sheet;
    //Functions
};
#endif //GUJARUNSFML_ANIMATIONCOMPONENT_H
