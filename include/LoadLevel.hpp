#ifndef LOADLEVEL_HPP
#define LOADLEVEL_HPP

#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>

// Structure to hold level data
struct LevelData {
    std::string backgroundPath;
    std::string jewelsPath;
    int timer;
    int requiredScore;
    int numberOfMoves;
    int bombs;
    int colorBombs;
};

// Singleton class to handle loading level data
class LoadLevel {
public:
    // Public static method to get the singleton instance
    static LoadLevel& getInstance();

    // Method to load level data by level ID
    LevelData loadLevel(int levelId);
    int currentLevel;

private:
    // Private constructor to prevent instantiation
    LoadLevel();

    // Deleted copy constructor and assignment operator to prevent copying
    LoadLevel(const LoadLevel&) = delete;
    LoadLevel& operator=(const LoadLevel&) = delete;

    // Path to the JSON file
    const std::string levelFilePath = "levels.json";
};

#endif // LOADLEVEL_HPP
