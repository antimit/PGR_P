#include "Tile.hpp"
#include "configs.hpp"
#include <string>

using namespace std;

Tile::Tile()
{
    // tile shape properties
    this->tileTexture.loadFromFile(TILE_TEXTURE_DIRECTORY + string("tile_background.jpg"));
    this->tileSprite.setTexture(this->tileTexture);

   
}

// set the position of tile
void Tile::setTilePosition(float x, float y)
{
    this->tileSprite.setPosition(x * TILE_WIDTH + 150, TILE_HEIGHT * y + 150);
}

// draw tile on the window
void Tile::render(sf::RenderWindow &window)
{
    window.draw(this->tileSprite);
}

// checks whether the tile is selected or not
bool Tile::isTileSelected(sf::Vector2f mousePoint)
{
    if (this->tileSprite.getGlobalBounds().contains(mousePoint))
        return true;
    return false;
}

// set texture of tile's sprite to selectedTileTexture
void Tile::enableTileOutline()
{
    this->tileSprite.setTexture(this->tileTexture);

   this->tileSprite.setColor(sf::Color(200, 200, 200, 200));
    // Render the border (you may need to pass a window reference here)
    // window.draw(border);
}

// set texture of tile's sprite to tileTexture
void Tile::disableTileOutline()
{
    this->tileSprite.setTexture(this->tileTexture);
    this->tileSprite.setColor(sf::Color(255, 255, 255, 255)); // Restore to default (white, full opacity)
}
