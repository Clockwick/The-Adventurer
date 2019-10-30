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
    int Str;
    int Agi;
    int Dex;
    int Int;
    int Vit;

    //Stats
    int hp;
    int hpMax;
    int damageMin;
    int damageMax;
    int accuracy;
    int luck;
    int defence;


    //Functions
    void updateStats(const bool reset);
    void updateLevel();
    void update();





};

#endif //GUJARUNSFML_ATTRIBUTECOMPONENT_H
