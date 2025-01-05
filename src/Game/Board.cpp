#include <Board.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "RandomNumberGenerator.hpp"

#include "Jewels/YellowJewel.hpp"
#include "Jewels/GreenJewel.hpp"
#include "Jewels/RedJewel.hpp"
#include "Jewels/BlueJewel.hpp"
#include "Jewels/PinkJewel.hpp"
#include "Jewels/VioletJewel.hpp"
#include "MemoryTracker.hpp"

using namespace std;

Board::Board()
{
    // initializes each element of listOfJewels to nullptr
    for (auto &row : listOfJewels)
        for (auto &jewel : row)
            jewel = nullptr;
    // initializes each element of listOfTiles to nullptr
    for (auto &row : listOfTiles)
        for (auto &tile : row)
            tile = nullptr;
    // generate random jewels for each tile
    shuffleJewels(listOfJewels);
    // validates jewels combination
    while (!isJewelsCombinationValid())
        validateJewels();
    // sets tiles and jewels position
    for (size_t i = 0; i < numberOfRow; i++)
    {

    
        for (size_t j = 0; j < numberOfColumn; j++)
        {
            listOfTiles[i][j] = new Tile();
            listOfTiles[i][j]->setTilePosition(j, i);
            listOfJewels[i][j]->setJewelPosition(j, i);
        }
    }
}

Board::~Board()
{
    // deletes each tile that allocated dynamically
    for (auto &row : listOfTiles)
        for (auto &tile : row)
            delete tile;

    //deletes each jewel that allocated dynamically
    for (auto &row : listOfJewels)
        for (auto &jewel : row)
            delete jewel;
}

void Board::render(sf::RenderWindow &window)
{
    // draws each tile in the window
    for (auto row : listOfTiles)
        for (auto tile : row)
            tile->render(window);
    // draws each jewel in the window
    for (auto row : listOfJewels)
        for (auto jewel : row)
            jewel->render(window);
}

size_t Board::getNumberOfRow() const
{
    return this->numberOfRow;
}

size_t Board::getNumberOfColumn() const
{
    return this->numberOfColumn;
}

TileList Board::getListOfTiles() const
{
    return listOfTiles;
}

JewelList Board::getListOfJewels() const
{
    return listOfJewels;
}

// generate one jewel and return it
Jewel *Board::generateRandomJewel()
{
    Jewel *jewel;
    MemoryTracker& memoryTracker = MemoryTracker::getInstance();
    switch (generateRandomNumber(YELLOW_JEWEL, VIOLET_JEWEL))
    {
    case YELLOW_JEWEL:
        jewel = new YellowJewel();
        break;
    case GREEN_JEWEL:
        jewel = new GreenJewel();
        break;
    case RED_JEWEL:
        jewel = new RedJewel();
        break;
    case BLUE_JEWEL:
        jewel = new BlueJewel();
        break;
    case PINK_JEWEL:
        jewel = new PinkJewel();
        break;
    case VIOLET_JEWEL:
        jewel = new VioletJewel();
        break;
    }

    return jewel;
}

void Board::shuffleJewels(JewelList &listOfJewels)
{
    for (size_t i = 0; i < numberOfRow; i++)
        for (size_t j = 0; j < numberOfColumn; j++)
        {
            if (listOfJewels[i][j] != nullptr)
                delete listOfJewels[i][j];
            listOfJewels[i][j] = generateRandomJewel();
        }
}

// Check jewels combination
bool Board::isJewelsCombinationValid() const
{
    // Check jewels horizontally
    for (size_t i = 0; i < numberOfRow; i++) {
        for (size_t j = 0; j < numberOfColumn - 2; j++) {
            if (isCombinationInvalid(i, j, i, j + 1, i, j + 2)) {
                return false;
            }
        }
    }

    // Check jewels vertically
    for (size_t j = 0; j < numberOfColumn; j++) {
        for (size_t i = 0; i < numberOfRow - 2; i++) {
            if (isCombinationInvalid(i, j, i + 1, j, i + 2, j)) {
                return false;
            }
        }
    }

    return true;
}

// Helper function to check if a combination of jewels is invalid (i.e., three consecutive jewels are the same)
bool Board::isCombinationInvalid(size_t i1, size_t j1, size_t i2, size_t j2, size_t i3, size_t j3) const
{
    if (*listOfJewels[i1][j1] == *listOfJewels[i2][j2] && *listOfJewels[i2][j2] == *listOfJewels[i3][j3]) {
        return true; // Invalid combination found
    }
    return false; // No invalid combination
}


// if three or more jewels are next to each other, it fixes their combination
void Board::validateJewels()
{
    // Validate jewels horizontally
    for (size_t i = 0; i < numberOfRow; i++) {
        for (size_t j = 0; j < numberOfColumn - 2; j++) {
            validateAndReplaceJewels(i, j, i, j + 1, i, j + 2);
        }
    }

    // Validate jewels vertically
    for (size_t j = 0; j < numberOfColumn; j++) {
        for (size_t i = 0; i < numberOfRow - 2; i++) {
            validateAndReplaceJewels(i, j, i + 1, j, i + 2, j);
        }
    }
}

// Helper function to validate and replace jewels
void Board::validateAndReplaceJewels(size_t i1, size_t j1, size_t i2, size_t j2, size_t i3, size_t j3)
{
    if (*listOfJewels[i1][j1] == *listOfJewels[i2][j2] && *listOfJewels[i2][j2] == *listOfJewels[i3][j3]) {
        delete listOfJewels[i2][j2];
        listOfJewels[i2][j2] = generateRandomJewel();
    }
}


void Board::swapTwoJewels(size_t i1, size_t j1, size_t i2, size_t j2, sf::RenderWindow &window)
{
    const float animationDuration = 0.3f; // Total animation duration in seconds
    sf::Clock clock;
    float elapsedTime = 0.0f;

    float dx = 0.0f;
    float dy = 0.0f;

    // Calculate the total distance the jewels need to move
    if (i1 == i2) { // Same row
        dx = (j1 > j2 ? -32.0f : 32.0f); // Left or right
    } else {         // Same column
        dy = (i1 > i2 ? -32.0f : 32.0f); // Up or down
    }

    // Gradual movement
    while (elapsedTime < animationDuration) {
        float deltaTime = clock.restart().asSeconds();
        elapsedTime += deltaTime;

        if (dx != 0.0f) {
            listOfJewels[i1][j1]->moveJewel(dx * deltaTime / animationDuration, 0);
            listOfJewels[i2][j2]->moveJewel(-dx * deltaTime / animationDuration, 0);
        } else if (dy != 0.0f) {
            listOfJewels[i1][j1]->moveJewel(0, dy * deltaTime / animationDuration);
            listOfJewels[i2][j2]->moveJewel(0, -dy * deltaTime / animationDuration);
        }

        
        render(window); // Render the entire board
        listOfJewels[i1][j1]->render(window);
        listOfJewels[i2][j2]->render(window);
        window.display();
    }

    // Ensure final positions are snapped to their correct spots
    listOfJewels[i1][j1]->moveJewel(dx, dy);
    listOfJewels[i2][j2]->moveJewel(-dx, -dy);

    // Swap the jewels in the board data structure
    std::swap(listOfJewels[i1][j1], listOfJewels[i2][j2]);
}


scorePair Board::refreshBoard()
{
    us numberOfDeletedJewel = 0;
    scorePair result;
    while (!isJewelsCombinationValid())
    {
        refreshHorizontally(result, numberOfDeletedJewel);
        refreshVertically(result, numberOfDeletedJewel);
    }
    return result;
}

void Board::refreshHorizontally(scorePair &result, us &numberOfDeletedJewel)
{
    for (int i = numberOfRow - 1; i != -1; i--)
    {
        for (size_t j = 0; j < numberOfColumn - 1; j++)
        {
            if (j + 1 != numberOfColumn)
            {
                if (*listOfJewels[i][j] == *listOfJewels[i][j + 1] &&
                    *listOfJewels[i][j + 1] == *listOfJewels[i][j + 2])
                {
                    handleHorizontalMatch(i, j, result, numberOfDeletedJewel);
                }
            }
        }
    }
}

void Board::refreshVertically(scorePair &result, us &numberOfDeletedJewel)
{
    for (size_t j = 0; j < numberOfColumn; j++)
    {
        for (int i = numberOfRow - 1; i > 0; i--)
        {
            if (i - 1 != 0)
            {
                if (*listOfJewels[i][j] == *listOfJewels[i - 1][j] &&
                    *listOfJewels[i - 1][j] == *listOfJewels[i - 2][j])
                {
                    handleVerticalMatch(i, j, result, numberOfDeletedJewel);
                }
            }
        }
    }
}

void Board::handleHorizontalMatch(int i, size_t j, scorePair &result, us &numberOfDeletedJewel)
{
    us jewelScore = listOfJewels[i][j]->getJewelScore();
    size_t k = j;
    while (listOfJewels[i][k]->getJewelScore() == jewelScore)
    {
        if (k == numberOfColumn)
            break;
        delete listOfJewels[i][k];
        shiftColumnUp(i, k, jewelScore);
        k++;
        numberOfDeletedJewel++;
    }
    result.push_back(make_pair(numberOfDeletedJewel, jewelScore));
    numberOfDeletedJewel = 0;
}

void Board::handleVerticalMatch(int i, size_t j, scorePair &result, us &numberOfDeletedJewel)
{
    us jewelScore = listOfJewels[i][j]->getJewelScore();
    while (listOfJewels[i][j]->getJewelScore() == jewelScore)
    {
        delete listOfJewels[i][j];
        shiftColumnUp(i, j, jewelScore);
        i--;
        numberOfDeletedJewel++;
    }
    result.push_back(make_pair(numberOfDeletedJewel, jewelScore));
    numberOfDeletedJewel = 0;
}

void Board::shiftColumnUp(int i, size_t column, us jewelScore)
{
    if (i != 0)
    {
        for (int f = i - 1; f != -1; f--)
        {
            listOfJewels[f + 1][column] = listOfJewels[f][column];
            listOfJewels[f + 1][column]->setJewelPosition(column, (f + 1));
        }
    }
    listOfJewels[0][column] = generateRandomJewel();
    while (listOfJewels[0][column]->getJewelScore() == jewelScore)
    {
        delete listOfJewels[0][column];
        listOfJewels[0][column] = generateRandomJewel();
    }
    listOfJewels[0][column]->setJewelPosition(column, 0);
}








