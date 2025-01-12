#include "Jewels/ForestEmerald.hpp"

using namespace std;

ForestEmerald::ForestEmerald() : Jewel(FOREST_EMERALD_SCORE)
{
    try
    {
        setJewelPath();
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + jewelPath+ std:: string("ForestEmerald.png")))
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