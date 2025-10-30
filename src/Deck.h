#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

class Deck {
private:
    Card** cards;           // Array dinámico de punteros a cartas
    int totalCards;         // Total de cartas en el mazo
    int currentIndex;       // Índice de la próxima carta a robar
    bool lastRoundRevealed; // ¿Se reveló carta de última ronda?
    
    // Colores disponibles
    std::vector<std::string> availableColors;
    
    // Métodos privados
    void createCards(int numPlayers);
    void shuffle();
    void insertLastRoundCard();
    
public:
    // Constructor con número de jugadores
    Deck(int numPlayers);
    
    // Destructor
    ~Deck();
    
    // Métodos principales
    Card* drawCard();                    // Robar carta del mazo
    bool isEmpty() const;                // ¿Se acabaron las cartas?
    bool isLastRoundRevealed() const;    // ¿Ya salió carta de última ronda?
    int getRemainingCards() const;       // Cartas restantes
};

#endif