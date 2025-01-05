#include "BlueJewel.hpp"
#include <iostream>
#include <string>

using namespace std;

BlueJewel::BlueJewel() : Jewel(BLUE_JEWEL_SCORE)
{
    try
    {
        // Attempt to load the texture
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY + std:: string("blue_jewel.png")))
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
