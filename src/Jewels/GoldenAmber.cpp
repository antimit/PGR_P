#include "Jewels/GoldenAmber.hpp"

using namespace std;

GoldenAmber::GoldenAmber() : Jewel(GOLDEN_AMBER_SCORE)
{
    try
    {
        
        setJewelPath();
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + jewelPath+ std:: string("GoldenAmber.png")))
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