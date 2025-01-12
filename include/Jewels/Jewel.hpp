#ifndef JEWEL_IG
#define JEWEL_IG

#include <SFML/Graphics.hpp>
#include "configs.hpp"
#include <string>
#include <iostream>



enum JewelsEnum
{
    GOLDEN_AMBER,
RADIANT_AMETHYST,
OCEAN_AQUAMARINE,
SKY_CERULEAN,
FOREST_EMERALD,
MOON_LAVENDER,
FIERY_LIME,
LIGHTNING_AMETHYST,
SOLAR_TEAL,
};

class Jewel
{
public:
    explicit Jewel(unsigned int);
    virtual ~Jewel() = 0;
    unsigned int getJewelScore() const;
    void render(sf::RenderWindow &);
    void setJewelPosition(float, float);
    sf::Color getJewelColor();
    void setJewelPath();
    

    void moveJewel(float, float);
    bool operator==(const Jewel &);

protected:
    sf::Sprite jewelSprite;
    sf::Texture jewelTexture;
    std::string jewelPath;
    unsigned int score;
};

#endif