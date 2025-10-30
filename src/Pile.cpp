#include "Pile.h"
#include <iostream>

// Constructor - Aloca memoria en heap
Pile::Pile() {
    maxSize = 3;
    currentSize = 0;
    taken = false;
    
    // MEMORIA DINÁMICA: Crear array de 3 punteros
    cards = new Card*[maxSize];
    
    // Inicializar todos los punteros en nullptr
    for (int i = 0; i < maxSize; i++) {
        cards[i] = nullptr;
    }
}

// Destructor - Libera memoria del heap
Pile::~Pile() {
    // NO eliminamos las cartas aquí porque pertenecen al Deck
    // Solo eliminamos el array de punteros
    delete[] cards;
}

bool Pile::addCard(Card* card) {
    // Validación 1: Pila llena
    if (isFull()) {
        std::cout << "[ADVERTENCIA] La pila esta llena. No se puede agregar mas cartas.\n";
        return false;
    }
    
    // Validación 2: Pila ya tomada
    if (taken) {
        std::cout << "[ADVERTENCIA] Esta pila ya fue tomada. No se pueden agregar cartas.\n";
        return false;
    }
    
    // Agregar carta
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
    // Nueva ronda: vaciar pila y marcarla como disponible
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
