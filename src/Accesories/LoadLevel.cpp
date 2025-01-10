#include "LoadLevel.hpp"
#include <iostream>

LoadLevel& LoadLevel::getInstance() {
    static LoadLevel instance;
    return instance;
}

LoadLevel::LoadLevel() {
    currentLevel = 1;
}

LevelData LoadLevel::loadLevel(int levelId) {
    std::ifstream file(levelFilePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open " + levelFilePath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonContent = buffer.str();

    LevelData levelData;
    std::size_t pos = jsonContent.find("\"id\": " + std::to_string(levelId));
    if (pos == std::string::npos) {
        throw std::runtime_error("Level ID not found in JSON");
    }

    // Move to the specific level's data by finding the opening '{' after "id"
    pos = jsonContent.rfind("{", pos);
    if (pos == std::string::npos) {
        throw std::runtime_error("Malformed JSON: No opening brace found for level ID");
    }

    // Parse background
    std::size_t backgroundPos = jsonContent.find("\"background\":", pos);
    if (backgroundPos == std::string::npos || backgroundPos > jsonContent.find("}", pos)) {
        throw std::runtime_error("Background not found in JSON for level ID");
    }
    std::size_t start = jsonContent.find("\"", backgroundPos + 13) + 1;
    std::size_t end = jsonContent.find("\"", start);
    levelData.backgroundPath = jsonContent.substr(start, end - start);

    // Parse timer
    pos = jsonContent.find("\"timer\":", pos);
    levelData.timer = std::stoi(jsonContent.substr(pos + 8, jsonContent.find(",", pos) - pos - 8));

    // Parse requiredScore
    pos = jsonContent.find("\"requiredScore\":", pos);
    levelData.requiredScore = std::stoi(jsonContent.substr(pos + 16, jsonContent.find(",", pos) - pos - 16));

    // Parse numberOfMoves
    pos = jsonContent.find("\"numberOfMoves\":", pos);
    levelData.numberOfMoves = std::stoi(jsonContent.substr(pos + 16, jsonContent.find(",", pos) - pos - 16));

    // Parse bombs
    pos = jsonContent.find("\"bombs\":", pos);
    levelData.bombs = std::stoi(jsonContent.substr(pos + 8, jsonContent.find(",", pos) - pos - 8));

    // Parse colorBombs
    pos = jsonContent.find("\"colorBombs\":", pos);
    levelData.colorBombs = std::stoi(jsonContent.substr(pos + 13, jsonContent.find("}", pos) - pos - 13));

    return levelData;
}

