#include "Jewels/Jewel.hpp"

Jewel::Jewel(unsigned int score)
{
    
    if (score >= 10 && score <= 15)
        this->score = score;
}


void Jewel::render(sf::RenderWindow &window)
{
    window.draw(this->jewelSprite);
}


unsigned int Jewel::getJewelScore() const
{
    return this->score;
}


void Jewel::setJewelPosition(float x, float y)
{
    this->jewelSprite.setPosition(x * TILE_WIDTH + 153, TILE_HEIGHT * y + 153);
}


void Jewel::moveJewel(float x, float y)
{
    this->jewelSprite.move(sf::Vector2f(x, y));
}


bool Jewel::operator==(const Jewel &secondJewel)
{
    return this->score == secondJewel.score;
}

Jewel::~Jewel(){};