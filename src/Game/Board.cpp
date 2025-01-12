#include <Board.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "RandomNumberGenerator.hpp"

#include "Jewels/GoldenAmber.hpp"
#include "Jewels/RadiantAmethyst.hpp"
#include "Jewels/OceanAquamarine.hpp"
#include "Jewels/SkyCerulean.hpp"
#include "Jewels/ForestEmerald.hpp"
#include "Jewels/MoonLavender.hpp"
#include "Jewels/FieryLime.hpp"
#include "Jewels/LightningAmethyst.hpp"
#include "Jewels/SolarTeal.hpp"
#include "MemoryTracker.hpp"

using namespace std;

Board::Board()
{

    for (auto &row : listOfJewels)
        for (auto &jewel : row)
            jewel = nullptr;

    for (auto &row : listOfTiles)
        for (auto &tile : row)
            tile = nullptr;

    shuffleJewels(listOfJewels);

    while (!isJewelsCombinationValid())
        validateJewels();

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

    for (auto &row : listOfTiles)
        for (auto &tile : row)
            delete tile;

    for (auto &row : listOfJewels)
        for (auto &jewel : row)
            delete jewel;
}

void Board::render(sf::RenderWindow &window)
{

    for (auto row : listOfTiles)
        for (auto tile : row)
            tile->render(window);

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

Jewel *Board::generateRandomJewel()
{
    Jewel *jewel;
    MemoryTracker &memoryTracker = MemoryTracker::getInstance();
    switch (generateRandomNumber(GOLDEN_AMBER, MOON_LAVENDER))
    {

    case GOLDEN_AMBER:
        jewel = new GoldenAmber();
        break;
    case RADIANT_AMETHYST:
        jewel = new RadiantAmethyst();
        break;
    case OCEAN_AQUAMARINE:
        jewel = new OceanAquamarine();
        break;
    case SKY_CERULEAN:
        jewel = new SkyCerulean();
        break;
    case FOREST_EMERALD:
        jewel = new ForestEmerald();
        break;
    case MOON_LAVENDER:
        jewel = new MoonLavender();
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

bool Board::isJewelsCombinationValid() const
{

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

bool Board::isCombinationInvalid(size_t i1, size_t j1, size_t i2, size_t j2, size_t i3, size_t j3) const
{
    if (*listOfJewels[i1][j1] == *listOfJewels[i2][j2] && *listOfJewels[i2][j2] == *listOfJewels[i3][j3])
    {
        return true;
    }
    return false;
}

void Board::validateJewels()
{

    for (size_t i = 0; i < numberOfRow; i++)
    {
        for (size_t j = 0; j < numberOfColumn - 2; j++)
        {
            validateAndReplaceJewels(i, j, i, j + 1, i, j + 2);
        }
    }

    for (size_t j = 0; j < numberOfColumn; j++)
    {
        for (size_t i = 0; i < numberOfRow - 2; i++)
        {
            validateAndReplaceJewels(i, j, i + 1, j, i + 2, j);
        }
    }
}

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
    const float animationDuration = 0.3f;
    sf::Clock clock;
    float elapsedTime = 0.0f;

    float dx = 0.0f;
    float dy = 0.0f;

    if (i1 == i2)
    {
        dx = (j1 > j2 ? -32.0f : 32.0f);
    }
    else
    {
        dy = (i1 > i2 ? -32.0f : 32.0f);
    }

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

        render(window);
        listOfJewels[i1][j1]->render(window);
        listOfJewels[i2][j2]->render(window);
        window.display();
    }

    listOfJewels[i1][j1]->moveJewel(dx, dy);
    listOfJewels[i2][j2]->moveJewel(-dx, -dy);

    std::swap(listOfJewels[i1][j1], listOfJewels[i2][j2]);
}

scorePair Board::refreshBoard(ParticleSource &particleSource)
{
    us numberOfDeletedJewel = 0;
    scorePair result;
    std::vector<std::vector<bool>> markedForDeletion(numberOfRow, std::vector<bool>(numberOfColumn, false));

    while (!isJewelsCombinationValid())
    {
        markMatches(markedForDeletion);

        for (size_t j = 0; j < numberOfColumn; j++)
        {
            handleColumnGravity(j, markedForDeletion, result, numberOfDeletedJewel, particleSource);
        }
    }
    sf::Vector2f particlePosition = particleSource.getPosition();

    return result;
}

void Board::markMatches(std::vector<std::vector<bool>> &markedForDeletion)
{

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

void Board::handleColumnGravity(size_t column, std::vector<std::vector<bool>> &markedForDeletion, scorePair &result, us &numberOfDeletedJewel, ParticleSource &particleSource)
{
    us jewelScore = 0;
    size_t writeIndex = numberOfRow - 1;

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

            sf::Color jewelColor = listOfJewels[i][column]->getJewelColor();
            sf::Vector2f jewelPosition(column * 64.0f, i * 64.0f);

            sf::Vector2f explosionPosition = listOfTiles[i][column]->getTilePosition();
            particleSource.setPosition(explosionPosition);

            particleSource.setParticleSize(5.0f);
            particleSource.PositionSet = true;

            delete listOfJewels[i][column];
            listOfJewels[i][column] = nullptr;
            numberOfDeletedJewel++;
        }
    }

    for (int i = writeIndex; i >= 0; i--)
    {
        listOfJewels[i][column] = generateRandomJewel();
        listOfJewels[i][column]->setJewelPosition(column, i);
    }

    if (numberOfDeletedJewel > 0)
    {
        result.push_back(std::make_pair(numberOfDeletedJewel, jewelScore));
        numberOfDeletedJewel = 0;
    }
}

void Board::clearBoard()
{
    for (size_t i = 0; i < numberOfRow; i++)
    {
        for (size_t j = 0; j < numberOfColumn; j++)
        {

            delete listOfJewels[i][j];
            listOfJewels[i][j] = nullptr;
        }
    }
}

void Board::generateNewJewels()
{
    for (size_t i = 0; i < numberOfRow; i++)
    {
        for (size_t j = 0; j < numberOfColumn; j++)
        {
            if (listOfJewels[i][j] == nullptr)
            {
                listOfJewels[i][j] = generateRandomJewel();
                listOfJewels[i][j]->setJewelPosition(j, i);
            }
        }
    }
}
