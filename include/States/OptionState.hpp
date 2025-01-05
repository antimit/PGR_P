#ifndef OPTIONS_STATE_IG
#define OPTIONS_STATE_IG

#include "States/GameState.hpp"
#include "Board.hpp"
#include "Score.hpp"
#include "Timer.hpp"
#include "Button.hpp"
#include "Move.hpp"
#include "Slider.hpp"


class OptionsState : public GameState
{
public:
    OptionsState();
    ~OptionsState();
    virtual GameState *eventHandler(sf::RenderWindow &, StateList &, sf::Event &) override;
    virtual GameState *update(sf::RenderWindow &, StateList &) override;
    virtual void render(sf::RenderWindow &) override;

    float getSliderValue() ;

private:
    Button mainmenuButton;
    sf::Font soundFont;
    sf::Text soundText;
        
};

#endif