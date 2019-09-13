#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& animation_sheet)
: sprite(sprite), animation_sheet(animation_sheet)
{


}
AnimationComponent::~AnimationComponent()
{

}
/*------------------Functions--------------------*/
void AnimationComponent::update(const float &dt) {

}

void AnimationComponent::startAnimation(std::string animation) {

}

void AnimationComponent::resetAnimation(const std::string animation) {

}

void AnimationComponent::addAnimation(const std::string key) {

}


