#include <iostream>
#include <limits>
#include "Game.h"
#include "FileManager.h"

void showMainMenu() {
    std::cout << "\n========================================\n";
    std::cout << "         COLORETTO - JUEGO             \n";
    std::cout << "========================================\n";
    std::cout << "1. Nueva partida\n";
    std::cout << "2. Cargar partida\n";
    std::cout << "3. Ver partidas guardadas\n";
    std::cout << "4. Salir\n";
    std::cout << "Selecciona una opcion: ";
}

int getNumberOfPlayers() {
    std::string input;
    int numPlayers;
    
    while (true) {
        std::cout << "Cuantos jugadores van a jugar? (3-5): ";
        std::getline(std::cin, input);
        
        try {
            numPlayers = std::stoi(input);
            if (numPlayers >= 3 && numPlayers <= 5) {
                return numPlayers;
            } else {
                std::cout << "[DATO INVALIDO] Debe ser entre 3 y 5 jugadores.\n";
            }
        } catch (...) {
            std::cout << "[DATO INVALIDO] Por favor ingresa un numero valido.\n";
        }
    }
}

void newGame() {
    int numPlayers = getNumberOfPlayers();
    
    std::cin.clear();
    
    Game game(numPlayers);
    game.play();
    
    if (!game.isGameEnded()) {
        return;
    }
    
    std::cout << "\nDeseas guardar esta partida? (s/n): ";
    std::string save;
    std::getline(std::cin, save);
    
    if (save == "s" || save == "S") {
        std::cout << "Nombre del archivo: ";
        std::string filename;
        std::getline(std::cin, filename);
        
        FileManager fm;
        fm.saveGame(&game, filename);
    }
}

void loadGame() {
    FileManager fm;
    auto games = fm.listSavedGames();
    
    if (games.empty()) {
        std::cout << "\nNo hay partidas guardadas.\n";
        return;
    }
    
    std::cout << "\n=== PARTIDAS GUARDADAS ===\n";
    for (size_t i = 0; i < games.size(); i++) {
        std::cout << (i + 1) << ". " << games[i] << "\n";
    }
    
    std::cout << "\nSelecciona partida (0 para cancelar): ";
    std::string input;
    std::getline(std::cin, input);
    
    try {
        int choice = std::stoi(input);
        if (choice == 0) return;
        if (choice < 1 || choice > static_cast<int>(games.size())) {
            std::cout << "[DATO INVALIDO] Opcion invalida.\n";
            return;
        }
        
        Game game(3);
        
        if (game.loadFromFile(games[choice - 1])) {
            std::cout << "\nRetomando partida...\n";
            std::cout << "Presiona Enter para continuar...";
            std::cin.get();
            
            game.play();
            
            if (game.isGameEnded()) {
                std::cout << "\nPartida finalizada.\n";
            }
        }
        
    } catch (...) {
        std::cout << "[DATO INVALIDO] Entrada invalida.\n";
    }
}

void listSavedGames() {
    FileManager fm;
    auto games = fm.listSavedGames();
    
    std::cout << "\n=== PARTIDAS GUARDADAS ===\n";
    if (games.empty()) {
        std::cout << "No hay partidas guardadas.\n";
    } else {
        for (const auto& game : games) {
            std::cout << "- " << game << "\n";
        }
    }
}

int main() {
    std::cout << "========================================\n";
    std::cout << "    BIENVENIDO A COLORETTO             \n";
    std::cout << "========================================\n";
    std::cout << "Juego de cartas con memoria dinamica\n";
    std::cout << "Desarrollado en C++\n\n";
    
    bool running = true;
    
    while (running) {
        showMainMenu();
        
        std::string input;
        std::getline(std::cin, input);
        
        try {
            int choice = std::stoi(input);
            
            switch (choice) {
                case 1:
                    newGame();
                    break;
                case 2:
                    loadGame();
                    break;
                case 3:
                    listSavedGames();
                    break;
                case 4:
                    std::cout << "\nGracias por jugar!\n";
                    std::cout << "Liberando memoria...\n";
                    running = false;
                    break;
                default:
                    std::cout << "[DATO INVALIDO] Opcion no valida.\n";
            }
            
        } catch (...) {
            std::cout << "[DATO INVALIDO] Por favor ingresa un numero.\n";
        }
        
        if (running) {
            std::cout << "\nPresiona Enter para continuar...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    
    return 0;
}