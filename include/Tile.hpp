#ifndef Tile_IG
#define Tile_IG

#include <SFML/Graphics.hpp>

class Tile
{
public:
    Tile();
    void setTilePosition(float, float);
    sf::Vector2f getTilePosition();
    bool isTileSelected(sf::Vector2f);
    void enableTileOutline();
    void disableTileOutline();
    void render(sf::RenderWindow &);

private:
    sf::Sprite tileSprite;
    sf::Texture tileTexture;
   
};

#endif