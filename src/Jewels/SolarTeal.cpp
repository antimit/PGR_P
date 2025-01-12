#include "SolarTeal.hpp"
#include <iostream>
#include <string>

using namespace std;

SolarTeal::SolarTeal() : Jewel(SOLAR_TEAL_SCORE)
{
    try
    {
         setJewelPath();
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + jewelPath+ std:: string("SolarTeal.png")))
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
