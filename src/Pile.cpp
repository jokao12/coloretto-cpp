#include "Pile.h"
#include <iostream>

Pile::Pile() {
    maxSize = 3;
    currentSize = 0;
    taken = false;
    
    cards = new Card*[maxSize];
    
    for (int i = 0; i < maxSize; i++) {
        cards[i] = nullptr;
    }
}

Pile::~Pile() {
    delete[] cards;
}

bool Pile::addCard(Card* card) {
    if (isFull()) {
        std::cout << "[ADVERTENCIA] La pila esta llena. No se puede agregar mas cartas.\n";
        return false;
    }
    
    if (taken) {
        std::cout << "[ADVERTENCIA] Esta pila ya fue tomada. No se pueden agregar cartas.\n";
        return false;
    }
    
    cards[currentSize] = card;
    currentSize++;
    return true;
}

bool Pile::isFull() const {
    return currentSize >= maxSize;
}

bool Pile::isEmpty() const {
    return currentSize == 0;
}

bool Pile::isTaken() const {
    return taken;
}

void Pile::markAsTaken() {
    taken = true;
}

void Pile::reset() {
    for (int i = 0; i < maxSize; i++) {
        cards[i] = nullptr;
    }
    currentSize = 0;
    taken = false;
}

int Pile::getSize() const {
    return currentSize;
}

Card* Pile::getCard(int index) const {
    if (index >= 0 && index < currentSize) {
        return cards[index];
    }
    return nullptr;
}

void Pile::display() const {
    if (taken) {
        std::cout << "[TOMADA]";
        return;
    }
    
    if (isEmpty()) {
        std::cout << "[VACIA]";
        return;
    }
    
    std::cout << "[";
    for (int i = 0; i < currentSize; i++) {
        std::cout << cards[i]->toString();
        if (i < currentSize - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}
