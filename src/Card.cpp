#include "Card.h"

// Constructor para carta de color
Card::Card(const std::string& cardColor) {
    type = COLOR_CARD;
    color = cardColor;
}

// Constructor para carta +2
Card::Card() {
    type = PLUS_TWO;
    color = "";  // +2 no tiene color
}

CardType Card::getType() const {
    return type;
}

std::string Card::getColor() const {
    return color;
}

bool Card::isPlusTwo() const {
    return type == PLUS_TWO;
}

std::string Card::toString() const {
    if (type == PLUS_TWO) {
        return "+2";
    }
    return color;
}