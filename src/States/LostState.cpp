#include "States/LostState.hpp"
#include "States/PlayState.hpp"
#include <string>

using namespace	std;

LostState::LostState() : restartButton(BUTTON_TEXTURE_DIRECTORY
	+ string("restart_button.png")),
	mainmenuButton(BUTTON_TEXTURE_DIRECTORY
	+ string("main_menu_button.png"))
{
	backgroundPath = "lost_background.jpg";
	setBackground();
	this->restartButton.change_scale(0.9f,0.9f);
	this->mainmenuButton.change_scale(0.9f,0.9f);

	this->restartButton.setButtonPosition(255, 700);
	this->mainmenuButton.setButtonPosition(255, 850);
	
}

GameState *LostState::eventHandler(sf::RenderWindow &window, StateList &state,
	sf::Event &event)
{
		

	if (restartButton.isPressedButton(window, event))
	{
		delete state[PLAY];
		LoadLevel& loader = LoadLevel::getInstance();
        LevelData level = loader.loadLevel(loader.currentLevel); // Example level ID	
		state[PLAY] = new PlayState(level);
		return (state[PLAY]);
	}
	
	if (mainmenuButton.isPressedButton(window, event))
	{
		state[PLAY] = nullptr;
		return (state[MAINMENU]);
	}
	return (this);
}

GameState *LostState::update(sf::RenderWindow &window, StateList &state)
{
    restartButton.HandleHover(window);
    mainmenuButton.HandleHover(window);
	return (this);
}

void LostState::render(sf::RenderWindow &window)
{
	window.draw(this->backgroundSprite);
	this->restartButton.render(window);
	this->mainmenuButton.render(window);
}