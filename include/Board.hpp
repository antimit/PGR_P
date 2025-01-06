#ifndef BOARD_IG
#define BOARD_IG

#include <iostream>
#include <array>
#include <vector>
#include "Tile.hpp"
#include "Jewels/Jewel.hpp"
#include "configs.hpp"

typedef std::array<std::array<Tile *, NUM_OF_COLUMN>, NUM_OF_ROW> TileList;
typedef std::array<std::array<Jewel *, NUM_OF_COLUMN>, NUM_OF_ROW> JewelList;
typedef unsigned short int us;
typedef std::vector<std::pair<us, us>> scorePair;

class Board
{
public:
    Board();
    ~Board();
    size_t getNumberOfRow() const;
    size_t getNumberOfColumn() const;
    TileList getListOfTiles() const;
    JewelList getListOfJewels() const;
    void shuffleJewels(JewelList &);
    Jewel *generateRandomJewel();
    void render(sf::RenderWindow &);
    void swapTwoJewels(size_t, size_t, size_t, size_t, sf::RenderWindow &);
    scorePair refreshBoard();
    void validateAndReplaceJewels(size_t i1, size_t j1, size_t i2, size_t j2, size_t i3, size_t j3);
    bool isCombinationInvalid(size_t i1, size_t j1, size_t i2, size_t j2, size_t i3, size_t j3) const;

    void refreshHorizontally(scorePair &result, us &numberOfDeletedJewel);
    void refreshVertically(scorePair &result, us &numberOfDeletedJewel);
    void handleHorizontalMatch(int i, size_t j, scorePair &result, us &numberOfDeletedJewel);
    void handleVerticalMatch(int i, size_t j, scorePair &result, us &numberOfDeletedJewel);
    void shiftColumnUp(int i, size_t column, us jewelScore);

    
    

    
    void markMatches(std::vector<std::vector<bool>> &markedForDeletion);

    
    void handleColumnGravity(size_t column, std::vector<std::vector<bool>> &markedForDeletion,
                             scorePair &result, us &numberOfDeletedJewel);

private:
    const size_t numberOfRow = NUM_OF_ROW;
    const size_t numberOfColumn = NUM_OF_COLUMN;
    TileList listOfTiles;
    JewelList listOfJewels;
    bool isJewelsCombinationValid() const; 
    void validateJewels();                 
};

#endif