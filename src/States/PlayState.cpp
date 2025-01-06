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



PlayState::PlayState() : gameScore(REQUIRED_SCORE), gameTimer(TIMER_COUNTDOWN), gameMove(NUM_OF_MOVE),
                         pauseButton(BUTTON_TEXTURE_DIRECTORY + string("pause_button.png")) 
{
 
    
    backgroundPath = "play_background.jpg";
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
        scorePair p = gameBoard.refreshBoard();
        for (const auto &item : p)
        {
            gameScore.increaseScore(item.first * item.second);
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
    if (gameTimer.getCountDownTime() < 0)
    {
        return state[LOST];
    }
    if (gameScore.getCurrentScore() >= gameScore.getRequiredScore())
    {
        return state[WIN];
    }
   
    return this;
}

void PlayState::render(sf::RenderWindow &window)
{
    window.draw(backgroundSprite);
    gameBoard.render(window);
    gameScore.render(window);
   
    gameTimer.render(window);
    pauseButton.render(window);
    gameMove.render(window);
}

