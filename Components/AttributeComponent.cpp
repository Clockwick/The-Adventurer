//
// Created by Paratthakorn Sribunyong on 29/10/2019 AD.
//

#include "AttributeComponent.h"


AttributeComponent::AttributeComponent() {
    this->level = level;
    this->exp = 0;
    this->expNext = 0;
    this->attributePoints = 3;


    this->Vit = 1;
    this->Str = 1;
    this->Int = 1;
    this->Dex = 1;
    this->Agi = 1;

    this->updateStats();
}

AttributeComponent::~AttributeComponent() {

}

//Functions

void AttributeComponent::updateStats() {

}

void AttributeComponent::calculateExpNext() {

}

void AttributeComponent::update() {

}

void AttributeComponent::levelUp() {

}

