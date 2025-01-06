#include "Jewels/PinkJewel.hpp"

using namespace std;

PinkJewel::PinkJewel() : Jewel(PINK_JEWEL_SCORE)
{
    try
    {
        
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + std:: string("pink_jewel.png")))
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