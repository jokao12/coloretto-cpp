#include "Player.h"
#include <iostream>
#include <algorithm>

Player::Player(const std::string& playerName) {
    name = playerName;
    plusTwoCards = 0;
    score = 0;
}

void Player::addCard(Card* card) {
    if (card->isPlusTwo()) {
        plusTwoCards++;
    } else {
        std::string color = card->getColor();
        colorCards[color]++;  // Incrementa contador de ese color
    }
}

void Player::addCardsFromPile(Card** cards, int size) {
    std::cout << name << " toma la pila con " << size << " cartas.\n";
    
    for (int i = 0; i < size; i++) {
        addCard(cards[i]);
    }
}

int Player::calculateScore() {
    score = 0;
    
    // Crear vector con las cantidades de cada color
    std::vector<int> colorCounts;
    for (auto& pair : colorCards) {
        colorCounts.push_back(pair.second);
    }
    
    // Ordenar de mayor a menor
    std::sort(colorCounts.begin(), colorCounts.end(), std::greater<int>());
    
    // Tabla de puntos por cantidad de cartas
    int pointTable[] = {0, 1, 3, 6, 10, 15, 21};
    
    // Los primeros 3 colores suman puntos
    for (int i = 0; i < 3 && i < colorCounts.size(); i++) {
        int count = colorCounts[i];
        if (count < 7) {
            score += pointTable[count];
        } else {
            score += 21 + (count - 6) * 7;  // Más de 6 cartas
        }
    }
    
    // Los demás colores restan puntos
    for (int i = 3; i < colorCounts.size(); i++) {
        int count = colorCounts[i];
        if (count < 7) {
            score -= pointTable[count];
        } else {
            score -= (21 + (count - 6) * 7);
        }
    }
    
    // Cartas +2 siempre suman
    score += plusTwoCards * 2;
    
    return score;
}

std::string Player::getName() const {
    return name;
}

int Player::getScore() const {
    return score;
}

int Player::getColorCount(const std::string& color) const {
    auto it = colorCards.find(color);
    if (it != colorCards.end()) {
        return it->second;
    }
    return 0;
}

int Player::getPlusTwoCount() const {
    return plusTwoCards;
}

void Player::displayCards() const {
    std::cout << "\n=== Cartas de " << name << " ===\n";
    
    if (colorCards.empty() && plusTwoCards == 0) {
        std::cout << "No tiene cartas aun.\n";
        return;
    }
    
    // Mostrar cartas de colores
    for (const auto& pair : colorCards) {
        std::cout << pair.first << ": " << pair.second << " cartas\n";
    }
    
    // Mostrar cartas +2
    if (plusTwoCards > 0) {
        std::cout << "+2: " << plusTwoCards << " cartas\n";
    }
}

void Player::displayScore() const {
    std::cout << name << " - Puntuacion: " << score << " puntos\n";
}