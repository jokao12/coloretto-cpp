#ifndef PILE_H
#define PILE_H

#include "Card.h"
#include <vector>

class Pile {
private:
    Card** cards;           // Array dinámico de punteros a cartas
    int currentSize;        // Cuántas cartas tiene actualmente
    int maxSize;            // Máximo 3 cartas
    bool taken;             // ¿Fue tomada por un jugador?
    
public:
    // Constructor
    Pile();
    
    // Destructor
    ~Pile();
    
    // Métodos principales
    bool addCard(Card* card);           // Agregar carta a la pila
    bool isFull() const;                // ¿Tiene 3 cartas?
    bool isEmpty() const;               // ¿Está vacía?
    bool isTaken() const;               // ¿Ya fue tomada?
    
    // Tomar la pila
    void markAsTaken();
    void reset();                       // Para nueva ronda
    
    // Obtener información
    int getSize() const;
    Card* getCard(int index) const;     // Obtener carta en posición
    
    // Para mostrar
    void display() const;
};

#endif