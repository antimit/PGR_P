#ifndef GAME_IG
#define GAME_IG

#include <SFML/Graphics.hpp>
#include "configs.hpp"
#include "States/GameState.hpp"
#include <array>
#include "MemoryTracker.hpp"
#include "Slider.hpp"

typedef std::array<GameState*,NUMBER_OF_STATES> StateList;

class Game
{
public:
    Game();
    void init();
    void run();

    //Temp 
    sf::Font font;
    sf::Text text;

private:
    sf::RenderWindow mainWindow;
    GameState* currentState;
    StateList statesList;

};

#endif