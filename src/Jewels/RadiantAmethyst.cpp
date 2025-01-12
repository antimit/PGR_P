#include "Jewels/RadiantAmethyst.hpp"

using namespace std;

RadiantAmethyst::RadiantAmethyst() : Jewel(RADIANT_AMETHYST_SCORE)
{
   try
    {
         setJewelPath();
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + jewelPath+ std:: string("RadiantAmethyst.png")))
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