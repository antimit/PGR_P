#ifndef PLAY_STATE_IG
#define PLAY_STATE_IG

#include "States/GameState.hpp"
#include "Board.hpp"
#include "Score.hpp"
#include "Timer.hpp"
#include "Button.hpp"
#include "Move.hpp"
#include "Music.hpp"
#include "ParticleSystem.hpp"
#include "World.hpp"


class PlayState : public GameState
{
public:
    PlayState();
    ~PlayState();
    virtual GameState *eventHandler(sf::RenderWindow &, StateList &, sf::Event &) override;
    virtual GameState *update(sf::RenderWindow &, StateList &) override;
    virtual void render(sf::RenderWindow &) override;


bool handlePauseButtonClick(sf::Event &event);
void handleTileSelection(sf::Event &event, sf::RenderWindow &window);
void processFirstTileSelection(size_t i, size_t j);
void processSecondTileSelection(size_t i, size_t j, sf::RenderWindow &window);
void resetFirstTile(size_t i, size_t j);
bool isAdjacent(size_t firstI, size_t firstJ, size_t secondI, size_t secondJ);

private:
    Board gameBoard;
    Score gameScore;
    Timer gameTimer;
    Move gameMove;
    
    Button pauseButton;
    ParticleSource particleSource;
    

   //temp
//    const int width = 800;
//     const int height = 800;
//     const int fps = 30;
//     const int substeps = 6;
//      int n_particles = 0;
    //  psim::World;

    
};

#endif