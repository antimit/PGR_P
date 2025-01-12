#include "Jewels/OceanAquamarine.hpp"

using namespace std;

OceanAquamarine::OceanAquamarine() : Jewel(OCEAN_AQUAMARINE_SCORE)
{
   try
    {
         setJewelPath();
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + jewelPath+ std:: string("OceanAquamarine.png")))
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