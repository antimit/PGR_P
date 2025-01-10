#ifndef MAIN_MENU_STATE_IG
#define MAIN_MENU_STATE_IG

#include "States/GameState.hpp"
#include "Button.hpp"
#include "Music.hpp"
#include "States/PlayState.hpp"
#include "LoadLevel.hpp"
class MainMenuState : public GameState
{
public:
    MainMenuState();
    virtual GameState *eventHandler(sf::RenderWindow &, StateList &, sf::Event &) override;
    virtual GameState *update(sf::RenderWindow &, StateList &) override;
    virtual void render(sf::RenderWindow &) override;
    

private:
    Button playButton;
    Button optionsButton;
    Button exitButton;
    
};

#endif