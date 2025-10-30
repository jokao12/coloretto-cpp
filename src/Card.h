#ifndef CARD_H
#define CARD_H

#include <string>

enum CardType {
    COLOR_CARD,
    PLUS_TWO
};

class Card {
private:
    CardType type;
    std::string color;
    
public:
    Card(const std::string& cardColor);
    Card();
    
    CardType getType() const;
    std::string getColor() const;
    bool isPlusTwo() const;
    std::string toString() const;
};

#endif