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
    //Functions
     const bool& play(const std::string key, const float& dt, const bool priority = false);
     const bool& play(const std::string key, const float& dt, const float& modifier, const float& max_modifier, const bool priority = false);
    void addAnimation(const std::string key,
                      float animation_timer, int start_x, int start_y, int frames_x, int frames_y,
                      int width, int height);
    //Accessor
    const bool& isDone(const std::string key);



private:
    //Class
    class Animation
    {
    public:
        //Constructor
        Animation(sf::Sprite& sprite, sf::Texture& animationSheet, float animation_timer, int start_x, int start_y, int frames_x, int frames_y,int width, int height)
        : animationSheet(animationSheet), height(height), width(width),  animation_timer(animation_timer), sprite(sprite), timer(0.f), done(false)
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
        bool done;
        bool* testptr;

        void getptr(bool* testptr)
        {
            this->testptr = testptr;
//            std::cout << "Setptr in Animation : " << this->testptr<< std::endl;
            std::cout << "Ani.cpp: "<< *this->testptr << std::endl;

        }

        //Accessor
        const bool& isDone() const
        {
            return this->done;
        }
        //Functions
        const bool& play(const float& dt)
        {
            //Update timer
            std::cout << "1" <<*this->testptr << "\n";


            this->done = false;
            this->timer += 100.0f * dt;
            if (this->timer >= this->animation_timer)
            {
                //reset Timer
                this->timer -= this->animation_timer;
                //Animate
                if (this->currentRect != this->endRect) {
                    this->currentRect.left += this->width;
//                    std::cout << this->testptr << std::endl;
                }

                else //reset
                {
                    this->currentRect.left = this->startRect.left;
                    this->done = true;

                }
                this->sprite.setTextureRect(this->currentRect);
            }
            return this->done;

        }
        const bool& play(const float& dt, float mod_percent)
        {

            //Update timer

            std::cout << 2<< *this->testptr << "\n";
            this->done = false;
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
                    this->done = true;

                }
                this->sprite.setTextureRect(this->currentRect);
            }
            return this->done;

        }
        void reset()
        {
            this->timer = this->animation_timer;
            this->currentRect = this->startRect;

        }
        void ii()
        {
            std::cout << "Ani.cpp Update: "<< *this->testptr << std::endl;

        }
    };
    //Variables
    std::map <std::string, Animation*> animations;
    sf::Sprite& sprite;
    sf::Texture& animation_sheet;
    Animation* lastAnimation;
    Animation* priorityAnimation;

    bool* pointer;
public:
    void getptr(bool* testptr)
    {
        this->pointer = testptr;
        std::cout << "AniCom.cpp: "<< *this->pointer << std::endl;

//        std::cout << "Setptr in AnimationCom : " << this->pointer << std::endl;
//        std::cout << "1" << std::endl;
    }




    //Functions
};
#endif //GUJARUNSFML_ANIMATIONCOMPONENT_H
