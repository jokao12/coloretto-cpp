#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <string>
#include <map>
#include <vector>

class Player {
private:
    std::string name;
    std::map<std::string, int> colorCards;
    int plusTwoCards;
    int score;
    
public:
    Player(const std::string& playerName);
    
    void addCard(Card* card);
    void addCardsFromPile(Card** cards, int size);
    
    int calculateScore();
    
    std::string getName() const;
    int getScore() const;
    int getColorCount(const std::string& color) const;
    int getPlusTwoCount() const;
    
    void displayCards() const;
    void displayScore() const;
};

#endif