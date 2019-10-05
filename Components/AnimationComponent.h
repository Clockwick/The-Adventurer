#ifndef GUJARUNSFML_ANIMATIONCOMPONENT_H
#define GUJARUNSFML_ANIMATIONCOMPONENT_H

#include <map>
#include <cstring>
#include <cmath>
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
    void play(const std::string key, const float& dt, const bool priority = false);
    void play(const std::string key, const float& dt, const float& modifier, const float& max_modifier, const bool priority = false);
    void addAnimation(const std::string key,
                      float animation_timer, int start_x, int start_y, int frames_x, int frames_y,
                      int width, int height);

    //Functions
private:
    //Class
    class Animation
    {
    public:
        //Constructor
        Animation(sf::Sprite& sprite, sf::Texture& animationSheet, float animation_timer, int start_x, int start_y, int frames_x, int frames_y,int width, int height)
        : animationSheet(animationSheet), height(height), width(width),  animation_timer(animation_timer), sprite(sprite)
        {
            this->timer = 0.0f;
            this->startRect = sf::IntRect(start_x*width, start_y*height, width, height);
            this->currentRect = this->startRect;
            this->endRect = sf::IntRect(frames_x*width, frames_y*height, width, height);
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
        bool play(const float& dt)
        {
            //Update timer
            bool done = false;
            this->timer += 100.0f * dt;
            if (this->timer >= this->animation_timer)
            {
                //reset Timer
                this->timer -= this->animation_timer;
                //Animate
                if (this->currentRect != this->endRect) {
                    this->currentRect.left += this->width;
                }

                else //reset
                {
                    this->currentRect.left = this->startRect.left;
                    done = true;

                }
                this->sprite.setTextureRect(this->currentRect);
            }
            return done;

        }
        bool play(const float& dt, float mod_percent)
        {
            //Update timer
            bool done = false;
            if (mod_percent < 0.5f)
            {
                mod_percent = 0.5f;
            }
            this->timer += (mod_percent) * 100.0f * dt;
            if (this->timer >= this->animation_timer)
            {
                //reset Timer
                this->timer -= this->animation_timer;
                //Animate
                if (this->currentRect != this->endRect) {
                    this->currentRect.left += this->width;
                }

                else //reset
                {
                    this->currentRect.left = this->startRect.left;
                    done = true;

                }
                this->sprite.setTextureRect(this->currentRect);
            }
            return done;

        }
        void reset()
        {
            this->timer = this->animation_timer;
            this->currentRect = this->startRect;

        }
    };
    //Variables
    std::map <std::string, Animation*> animations;
    sf::Sprite& sprite;
    sf::Texture& animation_sheet;
    Animation* lastAnimation;
    Animation* priorityAnimation;
    //Functions
};
#endif //GUJARUNSFML_ANIMATIONCOMPONENT_H
