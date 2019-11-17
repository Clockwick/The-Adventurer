#ifndef GUJARUNSFML_INVENTORY_H
#define GUJARUNSFML_INVENTORY_H

#include "Items.h"
class Inventory
{
private:
    Item **items;
    unsigned cap;
    unsigned nrOfItems;

    //Funcs
    void init(const unsigned from = 0);
    void expand();


public:
    Inventory(unsigned cap);
    Inventory(const Inventory& other);
    virtual ~Inventory();

    //Operators
    void operator = (const Inventory& other);
    Item& operator [] (const unsigned index);

    //Accessors
    const unsigned& size() const;
    const unsigned& capacity() const;
    Item& at(const unsigned index);
    //Modifiers

    //Funcs
    void add(const Item& item);
    void remove(const unsigned index);
};
#endif //GUJARUNSFML_INVENTORY_H
