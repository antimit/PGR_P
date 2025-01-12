#include "Jewels/FieryLime.hpp"
#include "LoadLevel.hpp"


using namespace std;

FieryLime::FieryLime() : Jewel(FIERY_LIME_SCORE)
{
    try
    {
        
        if (!this->jewelTexture.loadFromFile(TEXTURE_DIRECTORY  + jewelPath+ std:: string("FieryLime.png")))
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