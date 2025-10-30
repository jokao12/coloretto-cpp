#ifndef PILE_H
#define PILE_H

#include "Card.h"

class Pile {
private:
    Card** cards;
    int currentSize;
    int maxSize;
    bool taken;
    
public:
    Pile();
    ~Pile();
    
    bool addCard(Card* card);
    bool isFull() const;
    bool isEmpty() const;
    bool isTaken() const;
    
    void markAsTaken();
    void reset();
    
    int getSize() const;
    Card* getCard(int index) const;
    
    void display() const;
};

#endif