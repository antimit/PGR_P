#include "Jewels/RedJewel.hpp"

using namespace std;

RedJewel::RedJewel() : Jewel(RED_JEWEL_SCORE)
{
    try
    {
        // Attempt to load the texture
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + std:: string("red_jewel.png")))
        {
            throw runtime_error("Failed to load texture for Blue Jewel");
        }

        // Set the texture to the sprite
        this->jewelSprite.setTexture(jewelTexture);
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
        // Optionally: Set a default texture or log the error
    }
}