#ifndef GAME_H
#define GAME_H

#include "Card.h"
#include "Pile.h"
#include "Player.h"
#include "Deck.h"
#include <vector>

class Game {
private:
    Player** players;
    Pile** piles;
    Deck* deck;
    
    int numPlayers;
    int numPiles;
    int currentPlayerIndex;
    bool gameEnded;
    bool lastRoundActive;
    int pilesAvailable;
    
    void initializePlayers();
    void initializePiles();
    void resetPilesForNewRound();
    bool allPilesTakenOrFull();
    void endRound();
    void endGame();
    int getWinnerIndex();
    
    bool isValidPileIndex(int index) const;
    bool isValidPlayerInput(const std::string& input, int& value, int min, int max);
    
public:
    Game(int numberOfPlayers);
    ~Game();
    
    void play();
    void playTurn();
    
    bool placeCardInPile(int pileIndex);
    bool takePile(int pileIndex);
    
    void displayGameState() const;
    void displayPiles() const;
    void displayFinalScores() const;
    
    int getNumPlayers() const;
    int getCurrentPlayerIndex() const;
    bool isGameEnded() const;
    bool isLastRoundActive() const;
    Player* getPlayer(int index) const;
    Pile* getPile(int index) const;
    
    void pauseAndSave();
    void quitAndSave();
    bool loadFromFile(const std::string& filename);
    
    friend class FileManager;
};

#endif