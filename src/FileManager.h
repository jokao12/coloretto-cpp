#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

class Game;

class FileManager {
private:
    std::string* saveDirectory;
    
    bool createDirectoryIfNotExists(const std::string& path);
    
public:
    FileManager();
    ~FileManager();
    
    bool saveGame(const Game* game, const std::string& filename);
    bool loadGame(Game* game, const std::string& filename);
    
    std::vector<std::string> listSavedGames() const;
    bool fileExists(const std::string& filename) const;
    bool deleteGame(const std::string& filename);
    
    static bool isValidFilename(const std::string& filename);
};

#endif