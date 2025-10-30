#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <string>
#include <map>
#include <vector>

class Player {
private:
    std::string name;
    std::map<std::string, int> colorCards;  // Color -> cantidad de cartas
    int plusTwoCards;                        // Cantidad de cartas +2
    int score;                               // Puntuación final
    
public:
    // Constructor
    Player(const std::string& playerName);
    
    // Métodos principales
    void addCard(Card* card);                // Agregar carta recolectada
    void addCardsFromPile(Card** cards, int size);  // Tomar pila completa
    
    // Cálculo de puntuación
    int calculateScore();                    // Calcular puntos al final
    
    // Getters
    std::string getName() const;
    int getScore() const;
    int getColorCount(const std::string& color) const;
    int getPlusTwoCount() const;
    
    // Para mostrar
    void displayCards() const;
    void displayScore() const;
};

#endif