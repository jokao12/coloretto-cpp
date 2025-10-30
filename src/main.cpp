#include <iostream>
#include "Card.h"
#include "Pile.h"
#include "Player.h"
#include "Deck.h"
#include "FileManager.h"

int main() {
    std::cout << "=== PRUEBA DECK Y FILEMANAGER ===\n\n";
    
    // Prueba 1: Crear deck para 3 jugadores
    std::cout << "1. Creando mazo para 3 jugadores...\n";
    Deck deck(3);
    std::cout << "Cartas en el mazo: " << deck.getRemainingCards() << "\n\n";
    
    // Prueba 2: Robar algunas cartas
    std::cout << "2. Robando 5 cartas:\n";
    for (int i = 0; i < 5; i++) {
        Card* card = deck.drawCard();
        if (card) {
            std::cout << "  Carta " << (i+1) << ": " << card->toString() << "\n";
        }
    }
    std::cout << "Cartas restantes: " << deck.getRemainingCards() << "\n\n";
    
    // Prueba 3: FileManager
    std::cout << "3. Probando FileManager...\n";
    FileManager fm;
    
    std::cout << "Validando nombres de archivo:\n";
    std::cout << "  'partida1' es valido? " << (FileManager::isValidFilename("partida1") ? "Si" : "No") << "\n";
    std::cout << "  'partida/2' es valido? " << (FileManager::isValidFilename("partida/2") ? "Si" : "No") << "\n\n";
    
    std::cout << "Partidas guardadas:\n";
    auto games = fm.listSavedGames();
    if (games.empty()) {
        std::cout << "  No hay partidas guardadas aun.\n";
    } else {
        for (const auto& game : games) {
            std::cout << "  - " << game << "\n";
        }
    }
    
    return 0;
}