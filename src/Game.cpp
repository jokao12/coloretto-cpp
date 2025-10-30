#include "Game.h"
#include "FileManager.h"
#include <iostream>
#include <limits>

Game::Game(int numberOfPlayers) {
    if (numberOfPlayers < 3 || numberOfPlayers > 5) {
        std::cout << "[ERROR] Numero de jugadores invalido. Debe ser 3, 4 o 5.\n";
        numPlayers = 3;
    } else {
        numPlayers = numberOfPlayers;
    }
    
    numPiles = numPlayers + 1;
    currentPlayerIndex = 0;
    gameEnded = false;
    lastRoundActive = false;
    pilesAvailable = numPiles;
    
    players = new Player*[numPlayers];
    initializePlayers();
    
    piles = new Pile*[numPiles];
    initializePiles();
    
    deck = new Deck(numPlayers);
    
    std::cout << "\n=== JUEGO COLORETTO INICIADO ===\n";
    std::cout << "Jugadores: " << numPlayers << "\n";
    std::cout << "Pilas: " << numPiles << "\n";
    std::cout << "Cartas en el mazo: " << deck->getRemainingCards() << "\n\n";
}

Game::~Game() {
    for (int i = 0; i < numPlayers; i++) {
        delete players[i];
    }
    delete[] players;
    
    for (int i = 0; i < numPiles; i++) {
        delete piles[i];
    }
    delete[] piles;
    
    delete deck;
}

void Game::initializePlayers() {
    std::cout << "Ingresa los nombres de los jugadores:\n";
    for (int i = 0; i < numPlayers; i++) {
        std::string name;
        std::cout << "Jugador " << (i + 1) << ": ";
        std::getline(std::cin, name);
        
        if (name.empty()) {
            name = "Jugador" + std::to_string(i + 1);
        }
        
        players[i] = new Player(name);
    }
    std::cout << "\n";
}

void Game::initializePiles() {
    for (int i = 0; i < numPiles; i++) {
        piles[i] = new Pile();
    }
}

void Game::resetPilesForNewRound() {
    std::cout << "\n--- NUEVA RONDA ---\n\n";
    for (int i = 0; i < numPiles; i++) {
        piles[i]->reset();
    }
    pilesAvailable = numPiles;
}

bool Game::allPilesTakenOrFull() {
    if (pilesAvailable == 0) {
        return true;
    }
    
    int fullPiles = 0;
    for (int i = 0; i < numPiles; i++) {
        if (!piles[i]->isTaken() && piles[i]->isFull()) {
            fullPiles++;
        }
    }
    
    return (fullPiles == pilesAvailable);
}

void Game::endRound() {
    std::cout << "\n=== FIN DE RONDA ===\n";
    std::cout << "Todos los jugadores han tomado sus pilas.\n\n";
    
    if (deck->isLastRoundRevealed() && lastRoundActive) {
        endGame();
        return;
    }
    
    if (deck->isLastRoundRevealed() && !lastRoundActive) {
        lastRoundActive = true;
        std::cout << "*** La proxima ronda sera la ULTIMA RONDA ***\n\n";
    }
    
    if (!gameEnded) {
        resetPilesForNewRound();
    }
}

void Game::endGame() {
    gameEnded = true;
    
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "       FIN DEL JUEGO COLORETTO         \n";
    std::cout << "========================================\n\n";
    
    std::cout << "Calculando puntuaciones finales...\n\n";
    for (int i = 0; i < numPlayers; i++) {
        players[i]->calculateScore();
    }
    
    displayFinalScores();
    
    int winnerIndex = getWinnerIndex();
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "  GANADOR: " << players[winnerIndex]->getName() << "!\n";
    std::cout << "  Puntuacion: " << players[winnerIndex]->getScore() << " puntos\n";
    std::cout << "========================================\n\n";
}

int Game::getWinnerIndex() {
    int maxScore = players[0]->getScore();
    int winnerIndex = 0;
    
    for (int i = 1; i < numPlayers; i++) {
        if (players[i]->getScore() > maxScore) {
            maxScore = players[i]->getScore();
            winnerIndex = i;
        }
    }
    
    return winnerIndex;
}

bool Game::isValidPileIndex(int index) const {
    return index >= 0 && index < numPiles;
}

bool Game::isValidPlayerInput(const std::string& input, int& value, int min, int max) {
    try {
        value = std::stoi(input);
        if (value < min || value > max) {
            std::cout << "[DATO INVALIDO] El numero debe estar entre " << min << " y " << max << ".\n";
            return false;
        }
        return true;
    } catch (...) {
        std::cout << "[DATO INVALIDO] Por favor ingresa un numero valido.\n";
        return false;
    }
}

void Game::play() {
    while (!gameEnded) {
        if (allPilesTakenOrFull()) {
            endRound();
            if (gameEnded) break;
        }
        
        playTurn();
    }
}

void Game::playTurn() {
    Player* currentPlayer = players[currentPlayerIndex];
    
    displayGameState();
    
    std::cout << "\n--- Turno de " << currentPlayer->getName() << " ---\n";
    std::cout << "Opciones:\n";
    std::cout << "1. Robar carta del mazo y colocarla en una pila\n";
    std::cout << "2. Tomar una pila completa\n";
    std::cout << "3. Guardar y pausar partida\n";
    std::cout << "4. Abandonar partida\n";
    std::cout << "Selecciona una opcion: ";
    
    std::string input;
    std::getline(std::cin, input);
    
    int choice;
    if (!isValidPlayerInput(input, choice, 1, 4)) {
        return;
    }
    
    if (choice == 3) {
        pauseAndSave();
        return;
    } else if (choice == 4) {
        quitAndSave();
        return;
    }
    
    if (choice == 1) {
        bool allFull = true;
        for (int i = 0; i < numPiles; i++) {
            if (!piles[i]->isTaken() && !piles[i]->isFull()) {
                allFull = false;
                break;
            }
        }
        
        if (allFull) {
            std::cout << "[ADVERTENCIA] Todas las pilas disponibles estan llenas.\n";
            std::cout << "Debes tomar una pila en su lugar.\n";
            return;
        }
        
        Card* card = deck->drawCard();
        if (!card) {
            std::cout << "[INFO] No quedan mas cartas en el mazo.\n";
            endGame();
            return;
        }
        
        std::cout << "Carta robada: " << card->toString() << "\n";
        
        bool cardPlaced = false;
        while (!cardPlaced) {
            std::cout << "En que pila quieres colocarla? (1-" << numPiles << "): ";
            std::getline(std::cin, input);
            
            int pileIndex;
            if (!isValidPlayerInput(input, pileIndex, 1, numPiles)) {
                continue;
            }
            
            pileIndex--;
            
            if (!isValidPileIndex(pileIndex)) {
                std::cout << "[DATO INVALIDO] Numero de pila invalido.\n";
                continue;
            }
            
            if (piles[pileIndex]->isTaken()) {
                std::cout << "[ADVERTENCIA] Esa pila ya fue tomada. Elige otra.\n";
                continue;
            }
            
            if (piles[pileIndex]->addCard(card)) {
                cardPlaced = true;
                currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
            }
        }
        
    } else {
        bool pileTaken = false;
        
        while (!pileTaken) {
            std::cout << "Que pila quieres tomar? (1-" << numPiles << "): ";
            std::getline(std::cin, input);
            
            int pileIndex;
            if (!isValidPlayerInput(input, pileIndex, 1, numPiles)) {
                continue;
            }
            
            pileIndex--;
            
            if (!isValidPileIndex(pileIndex)) {
                std::cout << "[DATO INVALIDO] Numero de pila invalido.\n";
                continue;
            }
            
            if (piles[pileIndex]->isTaken()) {
                std::cout << "[ADVERTENCIA] Esa pila ya fue tomada. Elige otra.\n";
                continue;
            }
            
            if (piles[pileIndex]->isEmpty()) {
                std::cout << "[ADVERTENCIA] Esa pila esta vacia. Elige otra.\n";
                continue;
            }
            
            int size = piles[pileIndex]->getSize();
            Card** cards = new Card*[size];
            
            for (int i = 0; i < size; i++) {
                cards[i] = piles[pileIndex]->getCard(i);
            }
            
            currentPlayer->addCardsFromPile(cards, size);
            piles[pileIndex]->markAsTaken();
            pilesAvailable--;
            
            delete[] cards;
            
            pileTaken = true;
            currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
        }
    }
}

void Game::displayGameState() const {
    std::cout << "\n";
    std::cout << "========================================\n";
    if (lastRoundActive) {
        std::cout << "    *** ULTIMA RONDA ***\n";
    }
    std::cout << "Cartas restantes en el mazo: " << deck->getRemainingCards() << "\n";
    std::cout << "========================================\n";
    
    displayPiles();
}

void Game::displayPiles() const {
    std::cout << "\nEstado de las pilas:\n";
    for (int i = 0; i < numPiles; i++) {
        std::cout << "Pila " << (i + 1) << ": ";
        piles[i]->display();
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Game::displayFinalScores() const {
    std::cout << "=== PUNTUACIONES FINALES ===\n\n";
    
    for (int i = 0; i < numPlayers; i++) {
        players[i]->displayCards();
        std::cout << "\n";
        players[i]->displayScore();
        std::cout << "\n";
    }
}

int Game::getNumPlayers() const {
    return numPlayers;
}

int Game::getCurrentPlayerIndex() const {
    return currentPlayerIndex;
}

bool Game::isGameEnded() const {
    return gameEnded;
}

bool Game::isLastRoundActive() const {
    return lastRoundActive;
}

Player* Game::getPlayer(int index) const {
    if (index >= 0 && index < numPlayers) {
        return players[index];
    }
    return nullptr;
}

Pile* Game::getPile(int index) const {
    if (index >= 0 && index < numPiles) {
        return piles[index];
    }
    return nullptr;
}

void Game::pauseAndSave() {
    std::cout << "\n=== GUARDAR PARTIDA ===\n";
    std::cout << "Nombre del archivo: ";
    std::string filename;
    std::getline(std::cin, filename);
    
    FileManager fm;
    if (fm.saveGame(this, filename)) {
        std::cout << "Partida guardada exitosamente.\n";
        std::cout << "Puedes retomarla cuando quieras desde el menu principal.\n";
    }
}

void Game::quitAndSave() {
    std::cout << "\n=== ABANDONAR PARTIDA ===\n";
    std::cout << "Deseas guardar la partida antes de salir? (s/n): ";
    std::string save;
    std::getline(std::cin, save);
    
    if (save == "s" || save == "S") {
        pauseAndSave();
    }
    
    gameEnded = true;
    std::cout << "Saliendo del juego...\n";
}

bool Game::loadFromFile(const std::string& filename) {
    FileManager fm;
    return fm.loadGame(this, filename);
}