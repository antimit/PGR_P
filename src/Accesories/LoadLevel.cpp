#include "LoadLevel.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

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

    // Find the specific level by ID
    std::size_t pos = jsonContent.find("\"id\": " + std::to_string(levelId));
    if (pos == std::string::npos) {
        throw std::runtime_error("Level ID not found in JSON");
    }

    // Locate the opening brace for this level
    pos = jsonContent.rfind("{", pos);
    if (pos == std::string::npos) {
        throw std::runtime_error("Malformed JSON: No opening brace found for level ID");
    }

    // Parse levelbackground
    std::size_t backgroundPos = jsonContent.find("\"levelbackground\":", pos);
    if (backgroundPos == std::string::npos || backgroundPos > jsonContent.find("}", pos)) {
        throw std::runtime_error("Levelbackground not found in JSON for level ID");
    }
    std::size_t start = jsonContent.find("\"", backgroundPos + 19) + 1;
    std::size_t end = jsonContent.find("\"", start);
    levelData.backgroundPath = jsonContent.substr(start, end - start);

    // Parse levelsjewels
    std::size_t jewelsPos = jsonContent.find("\"levelsjewels\":", pos);
    if (jewelsPos == std::string::npos || jewelsPos > jsonContent.find("}", pos)) {
        throw std::runtime_error("Levelsjewels not found in JSON for level ID");
    }
    start = jsonContent.find("\"", jewelsPos + 16) + 1;
    end = jsonContent.find("\"", start);
    levelData.jewelsPath = jsonContent.substr(start, end - start);

    // Parse timer
    pos = jsonContent.find("\"timer\":", pos);
    levelData.timer = std::stoi(jsonContent.substr(pos + 8, jsonContent.find(",", pos) - pos - 8));

    // Parse requiredScore
    pos = jsonContent.find("\"requiredScore\":", pos);
    levelData.requiredScore = std::stoi(jsonContent.substr(pos + 16, jsonContent.find(",", pos) - pos - 16));

    // Parse numberOfMoves
    pos = jsonContent.find("\"numberOfMoves\":", pos);
    levelData.numberOfMoves = std::stoi(jsonContent.substr(pos + 16, jsonContent.find(",", pos) - pos - 16));

    // Parse specialItems.bombs
    std::size_t specialItemsPos = jsonContent.find("\"specialItems\":", pos);
    if (specialItemsPos == std::string::npos) {
        throw std::runtime_error("SpecialItems not found in JSON for level ID");
    }
    pos = jsonContent.find("\"bombs\":", specialItemsPos);
    levelData.bombs = std::stoi(jsonContent.substr(pos + 8, jsonContent.find(",", pos) - pos - 8));

    // Parse specialItems.colorBombs
    pos = jsonContent.find("\"colorBombs\":", specialItemsPos);
    levelData.colorBombs = std::stoi(jsonContent.substr(pos + 13, jsonContent.find("}", pos) - pos - 13));

    return levelData;
}
