#include "States/PlayState.hpp"
#include "Move.hpp"



#include <iostream>
#include <fstream>
#include <unistd.h>
#include <pwd.h>

using namespace std;

struct ChoosenEntity
{
    Jewel *choosenJewel = nullptr;
    Tile *choosenTile = nullptr;
    size_t iPosition;
    size_t jPosition;
};


struct ChoosenEntity first;
struct ChoosenEntity second;



PlayState::PlayState(const LevelData& levelData) : gameScore(levelData.requiredScore), gameTimer(levelData.timer), gameMove(levelData.numberOfMoves),
                         pauseButton(BUTTON_TEXTURE_DIRECTORY + string("pause_button.png")) , particleSource(50, 0.05f, [](float t, Particle &p) {
 float angle = 2 * M_PI * ((float)p.seed / RAND_MAX); // Random angle in radians

// Ensure speed is always non-zero (minimum speed of 50.0f)
float speed = 50.0f + 250.0f * (float)(p.seed2 % 100) / 100.0f; // Speed between 50 and 300

// Compute displacement based on speed and time
float dx = speed * cos(angle) * t; // Distance traveled in x
float dy = speed * sin(angle) * t; // Distance traveled in y

// Update the particle's position
p.position = p.position + sf::Vector2f(dx, dy);

// Gradually fade the particle
uint8_t alpha = static_cast<uint8_t>(255 * std::max(1.0f - t, 0.0f)); // Ensure alpha does not go below 0
p.color = sf::Color(255, 128, 0, alpha); // Bright orange color with fading transparency

// Optional Debugging
if (speed == 0.0f || alpha == 0) {
    std::cout << "Particle debug: Position(" << p.position.x << ", " << p.position.y << "), Speed: " << speed << ", Alpha: " << (int)alpha << std::endl;
}

    }) // Initialize ParticleSource
{
 
    
    backgroundPath = levelData.backgroundPath;
    // std::cout << backgroundPath <<std::endl;
    
    setBackground();
    pauseButton.setButtonPosition(0, 0);
    gameScore.setScoreProgressBarPosition(730, 0);
    gameTimer.setTimerProgressBarPosition(730, 90);
    gameMove.setMoveProgressBarPosition(730, 180);
}

PlayState::~PlayState()
{
    
   
}

GameState *PlayState::eventHandler(sf::RenderWindow &window, StateList &state, sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (handlePauseButtonClick(event))
            return state[PAUSE];

        handleTileSelection(event, window);
    }
    return this;
}

bool PlayState::handlePauseButtonClick(sf::Event &event)
{
    return this->pauseButton.isButtonPressed(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
}

void PlayState::handleTileSelection(sf::Event &event, sf::RenderWindow &window)
{
    for (size_t i = 0; i < gameBoard.getNumberOfRow(); i++)
    {
        for (size_t j = 0; j < gameBoard.getNumberOfColumn(); j++)
        {
            if (gameBoard.getListOfTiles()[i][j]->isTileSelected(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
            {
                if (first.choosenJewel == nullptr)
                {
                    processFirstTileSelection(i, j);
                }
                else if (isAdjacent(first.iPosition, first.jPosition, i, j))
                {
                    processSecondTileSelection(i, j, window);
                }
                else
                {
                    resetFirstTile(i, j);
                }
                break;
            }
        }
    }
}

void PlayState::processFirstTileSelection(size_t i, size_t j)
{
    first.choosenJewel = gameBoard.getListOfJewels()[i][j];
    first.iPosition = i;
    first.jPosition = j;
    first.choosenTile = gameBoard.getListOfTiles()[i][j];
    first.choosenTile->enableTileOutline();
}

void PlayState::processSecondTileSelection(size_t i, size_t j, sf::RenderWindow &window)
{
    second.choosenJewel = gameBoard.getListOfJewels()[i][j];
    second.choosenTile = gameBoard.getListOfTiles()[i][j];
    second.iPosition = i;
    second.jPosition = j;
    second.choosenTile->enableTileOutline();

    if (gameMove.isMoveValid(gameBoard, first.iPosition, first.jPosition, second.iPosition, second.jPosition))
    {
        gameBoard.swapTwoJewels(first.iPosition, first.jPosition, second.iPosition, second.jPosition, window);
        scorePair p = gameBoard.refreshBoard(particleSource);
        for (const auto &item : p)
        {
            gameScore.increaseScore(item.first * item.second);

            // sf::Vector2f matchPosition = gameBoard.getTilePosition(item.second); // Example function
            // particleSystem.addParticle(matchPosition, sf::Color::Yellow); 
        }
        gameMove.decreaseNumberOfMoveByOne();
    }
    first.choosenTile->disableTileOutline();
    first.choosenJewel = nullptr;
    second.choosenTile->disableTileOutline();
    second.choosenJewel = nullptr;
}

void PlayState::resetFirstTile(size_t i, size_t j)
{
    first.choosenTile->disableTileOutline();
    first.choosenJewel = gameBoard.getListOfJewels()[i][j];
    first.iPosition = i;
    first.jPosition = j;
    first.choosenTile = gameBoard.getListOfTiles()[i][j];
    first.choosenTile->enableTileOutline();
}

bool PlayState::isAdjacent(size_t firstI, size_t firstJ, size_t secondI, size_t secondJ)
{
    return (firstI == secondI && std::abs((int)firstJ - (int)secondJ) == 1) ||  
           (firstJ == secondJ && std::abs((int)firstI - (int)secondI) == 1);   
}


GameState *PlayState::update(sf::RenderWindow &window, StateList &state)
{
    pauseButton.HandleHover(window);
    gameTimer.updateTime();
    
    // Check if time is up
    if (gameTimer.getCountDownTime() < 0)
    {
        return state[LOST];
    }

    // Check if score meets or exceeds the required score
    if (gameScore.getCurrentScore() >= gameScore.getRequiredScore())
    {
        // Try to load the next level
        try
        {
            LoadLevel &loader = LoadLevel::getInstance();
            LevelData nextLevelData = loader.loadLevel(loader.currentLevel + 1);

            // If successful, update PlayState with the new level data
            loader.currentLevel++;
            backgroundPath = nextLevelData.backgroundPath;
            gameTimer.setCountDownTime(nextLevelData.timer);
            gameScore.setRequiredScore(nextLevelData.requiredScore);
            gameScore.resetScore(); // Reset the current score for the new level

            // Load the new background
            setBackground();
            return this; // Stay in PlayState for the next level
        }
        catch (const std::runtime_error &e)
        {
            // If no next level, transition to the WIN state
            std::cerr << "No next level: " << e.what() << std::endl;
            return state[WIN];
        }
    }

    // Update particle system
    static sf::Clock particleClock;  // Dedicated clock for particles
    deltaTime = particleClock.restart().asSeconds();
    particleSource.updateParticles(deltaTime);
    std::cout << "DeltaTime: " << deltaTime << " seconds\n";

    return this; // Continue in the current state
}


void PlayState::render(sf::RenderWindow &window)
{
    window.draw(backgroundSprite);
    gameBoard.render(window);
    gameScore.render(window);
    if(particleSource.PositionSet)
    {
        particleSource.draw(window);
    }
    
    gameTimer.render(window);
    pauseButton.render(window);
    gameMove.render(window);
}

