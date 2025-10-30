#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

// Forward declarations
class Game;

class FileManager {
private:
    std::string* saveDirectory;  // Puntero dinámico al directorio
    
    bool createDirectoryIfNotExists(const std::string& path);
    
public:
    // Constructor y destructor
    FileManager();
    ~FileManager();
    
    // Métodos principales
    bool saveGame(const Game* game, const std::string& filename);
    bool loadGame(Game* game, const std::string& filename);
    
    // Gestión de archivos
    std::vector<std::string> listSavedGames() const;
    bool fileExists(const std::string& filename) const;
    bool deleteGame(const std::string& filename);
    
    // Validación
    static bool isValidFilename(const std::string& filename);
};

#endif