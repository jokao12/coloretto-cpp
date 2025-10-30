#include "Deck.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>

Deck::Deck(int numPlayers) {
    currentIndex = 0;
    lastRoundRevealed = false;
    
    if (numPlayers == 3) {
        availableColors = {"Rojo", "Azul", "Verde", "Amarillo", "Naranja"};
        totalCards = 56;
    } else if (numPlayers == 4) {
        availableColors = {"Rojo", "Azul", "Verde", "Amarillo", "Naranja", "Morado"};
        totalCards = 65;
    } else {
        availableColors = {"Rojo", "Azul", "Verde", "Amarillo", "Naranja", "Morado", "Gris"};
        totalCards = 74;
    }
    
    cards = new Card*[totalCards];
    
    createCards(numPlayers);
    shuffle();
    insertLastRoundCard();
}

Deck::~Deck() {
    for (int i = 0; i < totalCards; i++) {
        delete cards[i];
    }
    delete[] cards;
}

void Deck::createCards(int numPlayers) {
    int index = 0;
    
    for (const std::string& color : availableColors) {
        for (int i = 0; i < 9; i++) {
            cards[index] = new Card(color);
            index++;
        }
    }
    
    for (int i = 0; i < 10; i++) {
        cards[index] = new Card();
        index++;
    }
    
    cards[index] = new Card();
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = totalCards - 2; i > 0; i--) {
        std::uniform_int_distribution<> dis(0, i);
        int j = dis(gen);
        
        Card* temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

void Deck::insertLastRoundCard() {
    int lastRoundPosition = totalCards - 15;
    if (lastRoundPosition < 0) lastRoundPosition = totalCards / 2;
    
    Card* lastRoundCard = cards[totalCards - 1];
    
    for (int i = totalCards - 1; i > lastRoundPosition; i--) {
        cards[i] = cards[i - 1];
    }
    
    cards[lastRoundPosition] = lastRoundCard;
}

Card* Deck::drawCard() {
    if (isEmpty()) {
        return nullptr;
    }
    
    Card* drawnCard = cards[currentIndex];
    currentIndex++;
    
    if (currentIndex >= totalCards - 20 && !lastRoundRevealed) {
        if (drawnCard->isPlusTwo()) {
            lastRoundRevealed = true;
            std::cout << "\n*** CARTA DE ULTIMA RONDA REVELADA ***\n";
            std::cout << "Esta es la ultima ronda del juego!\n\n";
        }
    }
    
    return drawnCard;
}

bool Deck::isEmpty() const {
    return currentIndex >= totalCards;
}

bool Deck::isLastRoundRevealed() const {
    return lastRoundRevealed;
}

int Deck::getRemainingCards() const {
    return totalCards - currentIndex;
}