#include "../Precom.h"

#ifndef GUJARUNSFML_ATTRIBUTECOMPONENT_H
#define GUJARUNSFML_ATTRIBUTECOMPONENT_H
class AttributeComponent
{
public:
    AttributeComponent();
    virtual ~AttributeComponent();


    //Levels
    unsigned level;
    unsigned exp;
    unsigned expNext;
    unsigned attributePoints;

    //Attributes
    unsigned Str;
    unsigned Agi;
    unsigned Dex;
    unsigned Int;
    unsigned Vit;

    //Stats
    int hp;
    int hpMax;
    int damageMin;
    int damageMax;
    int accuracy;
    int luck;
    int defence;


    //Functions
    void updateStats();
    void calculateExpNext();
    void levelUp();
    void update();





};

#endif //GUJARUNSFML_ATTRIBUTECOMPONENT_H
