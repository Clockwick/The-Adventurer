//
// Created by Paratthakorn Sribunyong on 29/10/2019 AD.
//

#include "AttributeComponent.h"


AttributeComponent::AttributeComponent() {
    this->level = level;
    this->exp = 0;
    this->expNext = (50 / 3) * (pow(this->level, 3) - 6 * pow(this->level,2) + (this->level * 17) - 12);
    this->attributePoints = 3;


    this->Vit = 1;
    this->Str = 1;
    this->Int = 1;
    this->Dex = 1;
    this->Agi = 1;

    this->updateStats(true);
}

AttributeComponent::~AttributeComponent() {

}

//Functions

void AttributeComponent::updateStats(const bool reset) {
    //DAMAGE
    this->damageMax = this->Str * 2 + this->Str / 4 + this->Int / 5;
    this->damageMin = this->Str * 2 + this->Str / 2 + this->Int / 5;

    //HP
    this->hpMax = this->Vit * 8 + this->Vit +   this->Str/2 + this->Int / 5;

    //ACCURACY
    this->accuracy = this->Dex * 4 + this->Dex / 3 + this->Int / 5;
    this->defence = this->Agi * 2 + this->Agi / 4 + this->Int / 5;

    //LUCK
    this->luck = this->Int * 2 + this->Int / 5;
    if (reset)
    {
        this->hp = this->hpMax;
    }

}


void AttributeComponent::update() {
    this->updateLevel();
    this->updateStats();
}

void AttributeComponent::updateLevel() {
    while (this->exp >= this->expNext)
    {
        ++this->level;
        this->exp -= this->expNext;
        this->expNext = (50 / 3) * (pow(this->level, 3) - 6 * pow(this->level,2) + (this->level * 17) - 12);
        ++this->attributePoints;

    }

}

