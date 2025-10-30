#include "Deck.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>

Deck::Deck(int numPlayers) {
    currentIndex = 0;
    lastRoundRevealed = false;
    
    // Definir colores disponibles según jugadores
    if (numPlayers == 3) {
        availableColors = {"Rojo", "Azul", "Verde", "Amarillo", "Naranja"};
        totalCards = 56;  // 45 color + 10 +2 + 1 última
    } else if (numPlayers == 4) {
        availableColors = {"Rojo", "Azul", "Verde", "Amarillo", "Naranja", "Morado"};
        totalCards = 65;  // 54 color + 10 +2 + 1 última
    } else {  // 5 jugadores
        availableColors = {"Rojo", "Azul", "Verde", "Amarillo", "Naranja", "Morado", "Gris"};
        totalCards = 74;  // 63 color + 10 +2 + 1 última
    }
    
    // MEMORIA DINÁMICA: Alocar array de punteros
    cards = new Card*[totalCards];
    
    createCards(numPlayers);
    shuffle();
    insertLastRoundCard();
}

Deck::~Deck() {
    // Liberar cada carta
    for (int i = 0; i < totalCards; i++) {
        delete cards[i];
    }
    // Liberar array de punteros
    delete[] cards;
}

void Deck::createCards(int numPlayers) {
    int index = 0;
    
    // Crear cartas de color (9 por cada color)
    for (const std::string& color : availableColors) {
        for (int i = 0; i < 9; i++) {
            cards[index] = new Card(color);
            index++;
        }
    }
    
    // Crear 10 cartas +2
    for (int i = 0; i < 10; i++) {
        cards[index] = new Card();  // Constructor sin parámetros = +2
        index++;
    }
    
    // Carta de última ronda (usamos +2 como marcador especial)
    // La trataremos especialmente al robarla
    cards[index] = new Card();  // Última carta +2 será la de "última ronda"
}

void Deck::shuffle() {
    // Generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Mezclar todas las cartas EXCEPTO la última (carta de última ronda)
    for (int i = totalCards - 2; i > 0; i--) {
        std::uniform_int_distribution<> dis(0, i);
        int j = dis(gen);
        
        // Intercambiar cards[i] y cards[j]
        Card* temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

void Deck::insertLastRoundCard() {
    // Carta de última ronda va aproximadamente 15 cartas antes del final
    int lastRoundPosition = totalCards - 15;
    if (lastRoundPosition < 0) lastRoundPosition = totalCards / 2;
    
    // Tomar la última carta (marcador de última ronda)
    Card* lastRoundCard = cards[totalCards - 1];
    
    // Mover cartas para hacer espacio
    for (int i = totalCards - 1; i > lastRoundPosition; i--) {
        cards[i] = cards[i - 1];
    }
    
    // Insertar carta de última ronda
    cards[lastRoundPosition] = lastRoundCard;
}

Card* Deck::drawCard() {
    if (isEmpty()) {
        return nullptr;
    }
    
    Card* drawnCard = cards[currentIndex];
    currentIndex++;
    
    // Verificar si es carta de última ronda (aproximadamente posición correcta)
    if (currentIndex >= totalCards - 20 && !lastRoundRevealed) {
        // La primera +2 en esta zona es la de última ronda
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