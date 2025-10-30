#ifndef CARD_H
#define CARD_H

#include <string>

enum CardType {
    COLOR_CARD,    // Carta de color
    PLUS_TWO       // Carta +2
};

class Card {
private:
    CardType type;
    std::string color;  // Solo para COLOR_CARD
    
public:
    // Constructor para carta de color
    Card(const std::string& cardColor);
    
    // Constructor para carta +2
    Card();
    
    // Getters
    CardType getType() const;
    std::string getColor() const;
    bool isPlusTwo() const;
    
    // Para mostrar
    std::string toString() const;
};

#endif