#include "States/GameState.hpp"
#include "configs.hpp"
#include <iostream>


using namespace std;

void GameState::setBackground()
{
    string address = string(BACKGROUND_DIRECTORY) + backgroundPath;
    // std::cout << address <<std::endl;
    // std::cout << backgroundPath <<std::endl;

    if(!backgroundTexture.loadFromFile(address))
    {
        std::cout <<"Couldnt't load the file " << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture);
}
