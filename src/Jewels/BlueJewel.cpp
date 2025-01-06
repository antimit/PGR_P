#include "BlueJewel.hpp"
#include <iostream>
#include <string>

using namespace std;

BlueJewel::BlueJewel() : Jewel(BLUE_JEWEL_SCORE)
{
    try
    {
        
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + std:: string("blue_jewel.png")))
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
