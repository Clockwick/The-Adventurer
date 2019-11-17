//
// Created by Paratthakorn Sribunyong on 17/11/2019 AD.
//

#include "Inventory.h"

void Inventory::init(const unsigned from)
{
    for (size_t i = from; i < this->cap; ++i)
    {
        this->items[i] = nullptr;
    }
}

void Inventory::expand()
{
    this->cap *= 2;

    Item** temp = new Item*[this->cap];

    for (size_t i = 0; i < nrOfItems; ++i)
    {
        temp[i] = this->items[i];
    }

    delete [] this->items;

    this->items = temp;

    this->init(this->nrOfItems);
}

Inventory::Inventory(unsigned cap)
{

    this->nrOfItems = 0;
    this->cap = cap;

    this->items = new Item*[cap];

    this->init();

}


Inventory::Inventory(const Inventory &other)
{
    this->cap = other.cap;
    this->nrOfItems = other.nrOfItems;

    this->items = new Item*[this->cap];

    this->init();

    for (size_t i = 0; i < this->nrOfItems; ++i)
    {
        this->items[i] = new Item(*other.items[i]);
    }
}


Inventory::~Inventory()
{
    for (size_t i = 0; i < this->nrOfItems ; ++i)
    {
        delete this->items[i];
    }

    delete[] this->items;
}


//Operators
void Inventory::operator=(const Inventory& other) {
    if (this != &other)
    {
        for (size_t i = 0; i < this->nrOfItems; ++i) {
            delete this->items[i];
        }
        delete[] this->items;

        this->cap = other.cap;
        this->nrOfItems = other.nrOfItems;

        this->items = new Item*[this->cap];

        this->init();

        for (size_t i = 0; i < this->nrOfItems; ++i)
        {
            this->items[i] = new Item(*other.items[i]);
        }
    }

}

//Functions
Item &Inventory::operator[](const unsigned index) {
    if (index < 0 || index >= this->nrOfItems)
    {
        std::cout << "ERROR::TYPE::OUT_OF_BOUND!!" << "\n";
    }
    return *this->items[index];
}

void Inventory::add(const Item &item) {
    if (this->nrOfItems >= this->cap)
        this->expand();
    this->items[this->nrOfItems++] = new Item(item);
}

void Inventory::remove(const unsigned index) {

}

const unsigned &Inventory::size() const {
    return this->nrOfItems;
}

const unsigned &Inventory::capacity() const {
    return this->cap;
}

Item &Inventory::at(const unsigned index) {
    return *this->items[0];
}




