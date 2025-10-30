#include "Card.h"

Card::Card(const std::string& cardColor) {
    type = COLOR_CARD;
    color = cardColor;
}

Card::Card() {
    type = PLUS_TWO;
    color = "";
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