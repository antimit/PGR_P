#include "Jewels/LightningAmethyst.hpp"

using namespace std;

LightningAmethyst::LightningAmethyst() : Jewel(LIGHTNING_AMETHYST_SCORE)
{
    try
    {
         setJewelPath();
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + jewelPath+ std:: string("LightningAmethyst.png")))
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