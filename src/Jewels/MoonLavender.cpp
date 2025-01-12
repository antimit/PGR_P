#include "MoonLavender.hpp"
#include <iostream>
#include <string>

using namespace std;

MoonLavender::MoonLavender() : Jewel(MOON_LAVENDER_SCORE)
{
    try
    {
         setJewelPath();
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + jewelPath+ std:: string("MoonLavender.png")))
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
