#include "../Precom.h"

#ifndef GUJARUNSFML_ATTRIBUTECOMPONENT_H
#define GUJARUNSFML_ATTRIBUTECOMPONENT_H
class AttributeComponent
{
public:
    AttributeComponent(int level, int hp = 9);
    virtual ~AttributeComponent();


    //Levels
    int level;
    int exp;
    int expNext;
    int attributePoints;

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
    std::string debugPrint() const;
    void gainExp(const int exp);
    void loseExp(const int exp);





};

#endif //GUJARUNSFML_ATTRIBUTECOMPONENT_H
