#include "States/WinState.hpp"
#include "States/PlayState.hpp"
#include <string>

using namespace std;

WinState::WinState() : restartButton(BUTTON_TEXTURE_DIRECTORY + string("restart_button.png")),
                       mainmenuButton(BUTTON_TEXTURE_DIRECTORY + string("main_menu_button.png"))
{
    backgroundPath = "win_background.jpg";
    setBackground();
    this->restartButton.setButtonPosition(255, 700);
    this->mainmenuButton.setButtonPosition(255, 850);
}
GameState *WinState::eventHandler(sf::RenderWindow &window, StateList &state, sf::Event &event)
{
    
    if(restartButton.isPressedButton(window,event))
            {
                delete state[PLAY];
                state[PLAY] = new PlayState();
                return state[PLAY];
            }
    
   if(mainmenuButton.isPressedButton(window,event))
            {
                delete state[PLAY];
                state[PLAY] = nullptr;
                return state[MAINMENU];
            }
    return this;
}
GameState *WinState::update(sf::RenderWindow &window, StateList &state)
{
    restartButton.HandleHover(window);
    mainmenuButton.HandleHover(window);
    return this;
}
void WinState::render(sf::RenderWindow &window)
{
    window.draw(this->backgroundSprite);
    this->restartButton.render(window);
    this->mainmenuButton.render(window);
}