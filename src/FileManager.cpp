#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>

FileManager::FileManager() {
    // MEMORIA DINÁMICA: Alocar string en heap
    saveDirectory = new std::string("saves");
    createDirectoryIfNotExists(*saveDirectory);
}

FileManager::~FileManager() {
    // Liberar memoria
    delete saveDirectory;
}

bool FileManager::createDirectoryIfNotExists(const std::string& path) {
    try {
        if (!std::filesystem::exists(path)) {
            std::filesystem::create_directories(path);
            return true;
        }
        return true;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "[ERROR] No se pudo crear directorio: " << e.what() << std::endl;
        return false;
    }
}

bool FileManager::saveGame(const Game* game, const std::string& filename) {
    // Implementación completa en siguiente paso con clase Game
    std::cout << "[INFO] Guardando partida: " << filename << "\n";
    return true;
}

bool FileManager::loadGame(Game* game, const std::string& filename) {
    // Implementación completa en siguiente paso con clase Game
    std::cout << "[INFO] Cargando partida: " << filename << "\n";
    return true;
}

std::vector<std::string> FileManager::listSavedGames() const {
    std::vector<std::string> gameFiles;
    
    try {
        for (const auto& entry : std::filesystem::directory_iterator(*saveDirectory)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                if (filename.length() > 10 && 
                    filename.substr(filename.length() - 10) == ".coloretto") {
                    gameFiles.push_back(filename);
                }
            }
        }
        std::sort(gameFiles.begin(), gameFiles.end());
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "[ERROR] Error accediendo al directorio: " << e.what() << std::endl;
    }
    
    return gameFiles;
}

bool FileManager::fileExists(const std::string& filename) const {
    std::string fullPath = *saveDirectory + "/" + filename;
    return std::filesystem::exists(fullPath);
}

bool FileManager::deleteGame(const std::string& filename) {
    if (!fileExists(filename)) {
        std::cout << "[ADVERTENCIA] Archivo no existe: " << filename << std::endl;
        return false;
    }
    
    try {
        std::string fullPath = *saveDirectory + "/" + filename;
        std::filesystem::remove(fullPath);
        std::cout << "[INFO] Archivo eliminado: " << filename << std::endl;
        return true;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "[ERROR] No se pudo eliminar: " << e.what() << std::endl;
        return false;
    }
}

bool FileManager::isValidFilename(const std::string& filename) {
    if (filename.empty() || filename.length() > 100) {
        return false;
    }
    
    const std::string invalidChars = "\\/:*?\"<>|";
    for (char c : filename) {
        if (invalidChars.find(c) != std::string::npos) {
            return false;
        }
    }
    
    return true;
}