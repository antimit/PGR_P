#include "SkyCerulean.hpp"
#include <iostream>
#include <string>

using namespace std;

SkyCerulean::SkyCerulean() : Jewel(SKY_CERULEAN_SCORE)
{
    try
    {
         setJewelPath();
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + jewelPath+ std:: string("SkyCerulean.png")))
        {
            throw runtime_error("Failed to load texture for Blue Jewel");
        }

        
        this->jewelSprite.setTexture(jewelTexture);
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
        
    }
}
