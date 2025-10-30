#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

class Deck {
private:
    Card** cards;
    int totalCards;
    int currentIndex;
    bool lastRoundRevealed;
    
    std::vector<std::string> availableColors;
    
    void createCards(int numPlayers);
    void shuffle();
    void insertLastRoundCard();
    
public:
    Deck(int numPlayers);
    ~Deck();
    
    Card* drawCard();
    bool isEmpty() const;
    bool isLastRoundRevealed() const;
    int getRemainingCards() const;
};

#endif