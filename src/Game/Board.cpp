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

    // deletes each jewel that allocated dynamically
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
    MemoryTracker &memoryTracker = MemoryTracker::getInstance();
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
    for (size_t i = 0; i < numberOfRow; i++)
    {
        for (size_t j = 0; j < numberOfColumn - 2; j++)
        {
            if (isCombinationInvalid(i, j, i, j + 1, i, j + 2))
            {
                return false;
            }
        }
    }

    // Check jewels vertically
    for (size_t j = 0; j < numberOfColumn; j++)
    {
        for (size_t i = 0; i < numberOfRow - 2; i++)
        {
            if (isCombinationInvalid(i, j, i + 1, j, i + 2, j))
            {
                return false;
            }
        }
    }

    return true;
}

// Helper function to check if a combination of jewels is invalid (i.e., three consecutive jewels are the same)
bool Board::isCombinationInvalid(size_t i1, size_t j1, size_t i2, size_t j2, size_t i3, size_t j3) const
{
    if (*listOfJewels[i1][j1] == *listOfJewels[i2][j2] && *listOfJewels[i2][j2] == *listOfJewels[i3][j3])
    {
        return true; // Invalid combination found
    }
    return false; // No invalid combination
}

// if three or more jewels are next to each other, it fixes their combination
void Board::validateJewels()
{
    // Validate jewels horizontally
    for (size_t i = 0; i < numberOfRow; i++)
    {
        for (size_t j = 0; j < numberOfColumn - 2; j++)
        {
            validateAndReplaceJewels(i, j, i, j + 1, i, j + 2);
        }
    }

    // Validate jewels vertically
    for (size_t j = 0; j < numberOfColumn; j++)
    {
        for (size_t i = 0; i < numberOfRow - 2; i++)
        {
            validateAndReplaceJewels(i, j, i + 1, j, i + 2, j);
        }
    }
}

// Helper function to validate and replace jewels
void Board::validateAndReplaceJewels(size_t i1, size_t j1, size_t i2, size_t j2, size_t i3, size_t j3)
{
    if (*listOfJewels[i1][j1] == *listOfJewels[i2][j2] && *listOfJewels[i2][j2] == *listOfJewels[i3][j3])
    {
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
    if (i1 == i2)
    {                                    // Same row
        dx = (j1 > j2 ? -32.0f : 32.0f); // Left or right
    }
    else
    {                                    // Same column
        dy = (i1 > i2 ? -32.0f : 32.0f); // Up or down
    }

    // Gradual movement
    while (elapsedTime < animationDuration)
    {
        float deltaTime = clock.restart().asSeconds();
        elapsedTime += deltaTime;

        if (dx != 0.0f)
        {
            listOfJewels[i1][j1]->moveJewel(dx * deltaTime / animationDuration, 0);
            listOfJewels[i2][j2]->moveJewel(-dx * deltaTime / animationDuration, 0);
        }
        else if (dy != 0.0f)
        {
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
    std::vector<std::vector<bool>> markedForDeletion(numberOfRow, std::vector<bool>(numberOfColumn, false));

    // Step 1: Mark all matches
    while (!isJewelsCombinationValid())
    {
        markMatches(markedForDeletion);

        // Step 2: Remove matches and apply gravity
        for (size_t j = 0; j < numberOfColumn; j++)
        {
            handleColumnGravity(j, markedForDeletion, result, numberOfDeletedJewel);
        }
    }

    return result;
}

void Board::markMatches(std::vector<std::vector<bool>> &markedForDeletion)
{
    // Horizontal matches
    for (size_t i = 0; i < numberOfRow; i++)
    {
        for (size_t j = 0; j < numberOfColumn - 2; j++)
        {
            if (*listOfJewels[i][j] == *listOfJewels[i][j + 1] &&
                *listOfJewels[i][j + 1] == *listOfJewels[i][j + 2])
            {
                markedForDeletion[i][j] = true;
                markedForDeletion[i][j + 1] = true;
                markedForDeletion[i][j + 2] = true;
            }
        }
    }

    // Vertical matches
    for (size_t j = 0; j < numberOfColumn; j++)
    {
        for (size_t i = 0; i < numberOfRow - 2; i++)
        {
            if (*listOfJewels[i][j] == *listOfJewels[i + 1][j] &&
                *listOfJewels[i + 1][j] == *listOfJewels[i + 2][j])
            {
                markedForDeletion[i][j] = true;
                markedForDeletion[i + 1][j] = true;
                markedForDeletion[i + 2][j] = true;
            }
        }
    }
}

void Board::handleColumnGravity(size_t column, std::vector<std::vector<bool>> &markedForDeletion, scorePair &result, us &numberOfDeletedJewel)
{
    us jewelScore = 0;
    size_t writeIndex = numberOfRow - 1;

    // Collect jewels not marked for deletion
    for (int i = numberOfRow - 1; i >= 0; i--)
    {
        if (!markedForDeletion[i][column])
        {
            if (writeIndex != i)
            {
                listOfJewels[writeIndex][column] = listOfJewels[i][column];
                listOfJewels[writeIndex][column]->setJewelPosition(column, writeIndex);
            }
            writeIndex--;
        }
        else
        {
            if (!jewelScore)
            {
                jewelScore = listOfJewels[i][column]->getJewelScore();
            }
            delete listOfJewels[i][column];
            listOfJewels[i][column] = nullptr;
            numberOfDeletedJewel++;
        }
    }

    // Fill remaining slots at the top with new jewels
    for (int i = writeIndex; i >= 0; i--)
    {
        listOfJewels[i][column] = generateRandomJewel();
        listOfJewels[i][column]->setJewelPosition(column, i);
    }

    // Add result for this column if any jewels were deleted
    if (numberOfDeletedJewel > 0)
    {
        result.push_back(std::make_pair(numberOfDeletedJewel, jewelScore));
        numberOfDeletedJewel = 0;
    }
}
