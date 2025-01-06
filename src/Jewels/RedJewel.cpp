#include "Jewels/RedJewel.hpp"

using namespace std;

RedJewel::RedJewel() : Jewel(RED_JEWEL_SCORE)
{
    try
    {
        
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + std:: string("red_jewel.png")))
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