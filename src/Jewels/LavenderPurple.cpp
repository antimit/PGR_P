#include "Jewels/LavenderPurple.hpp"

using namespace std;

LavenderPurple::LavenderPurple() : Jewel(YELLOW_JEWEL_SCORE)
{
   try
    {
        
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + std:: string("LavenderPurple.png")))
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