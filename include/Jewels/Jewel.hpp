#ifndef JEWEL_IG
#define JEWEL_IG

#include <SFML/Graphics.hpp>
#include "configs.hpp"
#include <string>
#include <iostream>



enum JewelsEnum
{
    AMBER_YELLOW,
    AMETHYSTPURPLE,
    AQEAMARINE,
    CERULEANBLUE,
    EMERALDGREEN,
    LAVENDERPURPLE,
    LIMEGREEN,
    TEALGREEN
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
    

    void moveJewel(float, float);
    bool operator==(const Jewel &);

protected:
    sf::Sprite jewelSprite;
    sf::Texture jewelTexture;
    unsigned int score;
};

#endif