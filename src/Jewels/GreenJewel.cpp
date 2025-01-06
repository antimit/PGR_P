#include "Jewels/GreenJewel.hpp"

using namespace std;

GreenJewel::GreenJewel() : Jewel(GREEN_JEWEL_SCORE)
{
    try
    {
        
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + std:: string("green_jewel.png")))
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