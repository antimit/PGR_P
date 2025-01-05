#include "States/PauseState.hpp"
#include "States/PlayState.hpp"
#include <string>

using namespace std;

PauseState::PauseState() : resumeButton(BUTTON_TEXTURE_DIRECTORY + string("resume_button.png")),
                           exitButton(BUTTON_TEXTURE_DIRECTORY + string("exit_button.png")),
                           restartButton(BUTTON_TEXTURE_DIRECTORY + string("restart_button.png"))
{
    backgroundPath = "pause_background.png";
    setBackground();
    this->resumeButton.setButtonPosition(235, 200);
    this->restartButton.setButtonPosition(235, 400);
    this->exitButton.setButtonPosition(235, 585);
}

GameState *PauseState::eventHandler(sf::RenderWindow &window, StateList &state, sf::Event &event)
{
    // checks whether the resume button is selected or not
   if(resumeButton.isPressedButton(window,event))
                return state[PLAY];
    // checks whether the exit button is selected or not
    if(exitButton.isPressedButton(window,event))
                return state[MAINMENU];
    // checks whether the restart button is selected or not
   if(restartButton.isPressedButton(window,event))
            {
                delete state[PLAY];
                state[PLAY] = new PlayState();
                return state[PLAY];
            }
    return this;
}
GameState *PauseState::update(sf::RenderWindow &window, StateList &state)
{
    resumeButton.HandleHover(window);
    exitButton.HandleHover(window);
    restartButton.HandleHover(window);
    return this;
}
void PauseState::render(sf::RenderWindow &window)
{
    window.draw(this->backgroundSprite);
    this->resumeButton.render(window);
    this->restartButton.render(window);
    this->exitButton.render(window);
}