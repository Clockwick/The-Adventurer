#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& animation_sheet)
: sprite(sprite), animation_sheet(animation_sheet), lastAnimation(NULL), priorityAnimation(NULL)
{


}
AnimationComponent::~AnimationComponent()
{
    for (auto &i : this->animations)
    {
        delete i.second;

    }

}
/*------------------Functions--------------------*/
void AnimationComponent::play(const std::string key, const float &dt, const bool priority) {
    //Reset Last animation

    if (priority)
    {
        this->priorityAnimation = this->animations[key];
    }
    if (this->priorityAnimation)
    {
        if (this->priorityAnimation == this->animations[key])
        {
            if (this->lastAnimation != this->animations[key])
            {

                if (this->lastAnimation == NULL)
                {
                    this->lastAnimation = this->animations[key];
                }
                else
                {
                    this->lastAnimation->reset();
                    this->lastAnimation = this->animations[key];

                }
            }

            //If the priorityAnimatioh is done, Remove it
            if(this->animations[key]->play(dt))
            {
                this->priorityAnimation = NULL;
            }
        }
    }


// Play if no priority
    else {

        if (priority)
        {
            this->priorityAnimation = this->animations[key];
        }
        if (this->lastAnimation != this->animations[key]) {
            if (this->lastAnimation == NULL) {
                this->lastAnimation = this->animations[key];
            } else {
                this->lastAnimation->reset();
                this->lastAnimation = this->animations[key];

            }
        }

        if(this->animations[key]->play(dt))
        {
            this->priorityAnimation = NULL;
        }
    }
}
void AnimationComponent::play(const std::string key, const float &dt, const float& modifier, const float& max_modifier, const bool priority) {
    //Reset Last animation

    if (this->priorityAnimation)
    {
        if (this->priorityAnimation == this->animations[key])
        {
            if (this->lastAnimation != this->animations[key])
            {

                if (this->lastAnimation == NULL)
                {
                    this->lastAnimation = this->animations[key];
                }
                else
                {
                    this->lastAnimation->reset();
                    this->lastAnimation = this->animations[key];

                }
            }

            if(this->animations[key]->play(dt, abs(modifier/max_modifier)))
            {
                this->priorityAnimation = NULL;
            }
        }
    }


// Play if no priority
    else
    if (priority)//If priority animation, set it
    {
        this->priorityAnimation = this->animations[key];
    }
        {
    if(this->lastAnimation!= this->animations[key])
    {
        if (this->lastAnimation == NULL)
        {
            this->lastAnimation = this->animations[key];
        }
        else
        {
            this->lastAnimation->reset();
            this->lastAnimation = this->animations[key];

        }
    }


            if(this->animations[key]->play(dt, abs(modifier/max_modifier)))
            {
                this->priorityAnimation = NULL;
            }

}
}

void AnimationComponent::addAnimation(const std::string key,
        float animation_timer, int start_x, int start_y, int frames_x, int frames_y,
        int width, int height)

        {
    this->animations[key] = new Animation(this->sprite, this->animation_sheet,
            animation_timer, start_x, start_y, frames_x, frames_y , width, height);

}



