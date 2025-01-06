#include "Jewels/YellowJewel.hpp"

using namespace std;

YellowJewel::YellowJewel() : Jewel(YELLOW_JEWEL_SCORE)
{
   try
    {
        
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + std:: string("yellow_jewel.png")))
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