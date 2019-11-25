//
// Created by Paratthakorn Sribunyong on 29/10/2019 AD.
//
//#include <vector>
//std::vector <int> firstVec;
//[[hp],[lvl],[exp],[expNext],[attr],[str],[vit],[agi],[dex],[int],[luck]]
//std::vector <int> secondVec;
#include "AttributeComponent.h"


AttributeComponent::AttributeComponent(int level, int hp) {
//    static bool initialized;
//    if (!initialized) {
//        initialized = true;
        this->hp = hp;
        this->level = level;
        this->exp = 0;
        this->expNext = static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1,2) + ((this->level + 1) * 17) - 12));
        this->attributePoints = 6;


        this->Vit = 1;
        this->Str = 1;
        this->Int = 1;
        this->Dex = 1;
        this->Agi = 1;
        this->luck = 1;

        this->updateLevel();
        if (hp != 500)
            this->updateStats(true);

//        std::cout << "If" << std::endl;
//    }
//    else {
//        //[[hp],[lvl],[exp],[expNext],[attr],[str],[vit],[agi],[dex],[int],[luck]]
//        this->hp = secondVec[0];
//        this->level = secondVec[1];
//        this->exp = secondVec[2];
//        this->expNext = secondVec[3];
//        this->attributePoints = secondVec[3];
//        this->Str = secondVec[4];
//        this->Vit = secondVec[5];
//        this->Agi = secondVec[6];
//        this->Dex = secondVec[7];
//        this->Int = secondVec[8];
//        this->luck = secondVec[9];
//        std::cout << "else" << std::endl;
//
//    }



}

AttributeComponent::~AttributeComponent() {

}

//Functions

void AttributeComponent::updateStats(const bool reset) {
    //DAMAGE
    this->damageMax = this->Str + 2  + this->Str / 2 + this->Int / 5 + this->Agi / 2 + this->Agi / 4 + this->luck * 2;
    this->damageMin = this->Str + this->Str / 8 + this->Int / 5 + this->Agi / 3 + this->Agi / 4 + this->luck / 4;

    //HP
//    this->hpMax = 100.f;
    this->hpMax = this->Vit * 8 + this->Vit + this->Str/2 + this->Int / 5;

    //ACCURACY
    this->accuracy = this->Dex * 3 + this->Dex / 3 + this->Int / 5 + this->Agi/3 + this->Agi;
    this->defence = this->Str/2 + this->Str/6 + this->Vit/2 + this->Agi / 4 + this->Int / 5;

    if (reset)
    {
        this->hp = this->hpMax;
    }


}




void AttributeComponent::update() {
    this->updateStats(false);
    this->updateLevel();
    //[[hp],[lvl],[exp],[expNext],[attr],[str],[vit],[agi],[dex],[int],[luck]]
//    firstVec.push_back(this->hp);
//    firstVec.push_back(this->level);
//    firstVec.push_back(this->exp);
//    firstVec.push_back(this->expNext);
//    firstVec.push_back(this->attributePoints);
//    firstVec.push_back(this->Str);
//    firstVec.push_back(this->Vit);
//    firstVec.push_back(this->Agi);
//    firstVec.push_back(this->Dex);
//    firstVec.push_back(this->Int);
//    firstVec.push_back(this->luck);
//    if (!firstVec.empty()) {
//        for (int k = 0; k < firstVec.size(); k++) {
//            secondVec.push_back(firstVec[k]);
//        }
//        for (int u = 0; u < firstVec.size(); u++)
//        {
//            firstVec.pop_back();
//        }
//    }
//    if (firstVec.empty())
//    {
//        for (int k = 0; k < secondVec.size(); k++)
//        {
//            secondVec.pop_back();
//        }
//    }


}

void AttributeComponent::updateLevel() {
    while (this->exp >= this->expNext)
    {
        ++this->level;
        this->exp -= this->expNext;
        this->expNext = static_cast<int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level,2) + (this->level * 17) - 12));
        ++this->attributePoints;

    }

}
std::string AttributeComponent::debugPrint() const
{
    std::stringstream ss;

    ss << "Level: " << this->level << "\n"
       << "Exp: " << this->exp << "\n"
       << "Exp Next: " << this->expNext << "\n"
       << "Attp: " << this->attributePoints << "\n";

    return ss.str();
}

void AttributeComponent::gainExp(const int exp) {
    this->exp += exp;
    this->updateLevel();

}



