//
// Created by Paratthakorn Sribunyong on 12/11/2019 AD.
//

#include "SkillComponent.h"

SkillComponent::SkillComponent()
{
    this->skills.push_back(Skill(SKILLS::BOOM));
    this->skills.push_back(Skill(SKILLS::BANG));
    this->skills.push_back(Skill(SKILLS::WALA));
    this->skills.push_back(Skill(SKILLS::ENDURANCE));
}

SkillComponent::~SkillComponent()
{

}

const int SkillComponent::getSkill(const int skill) const
{
    if (skills.empty() || skill < 0 || skill >= this->skills.size())
        std::cout << "ERROR::SKILLCOMPONENT::GETSKILL::SKILL DOES NOT EXIST: " + skill;
    else
        return this->skills[skill].getLevel();
}

const void SkillComponent::gainExp(const int skill, const int exp)
{
    if (skills.empty() || skill < 0 || skill >= this->skills.size())
        std::cout << "ERROR::SKILLCOMPONENT::GAINEXP::SKILL DOES NOT EXIST: " + skill;
    else
    {
        this->skills[skill].gainExp(exp);
    }
}