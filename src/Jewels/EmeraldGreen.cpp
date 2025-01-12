#include "Jewels/EmeraldGreen.hpp"

using namespace std;

EmeraldGreen::EmeraldGreen() : Jewel(VIOLET_JEWEL_SCORE)
{
   try
    {
        
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + std:: string("EmeraldGreen.png")))
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