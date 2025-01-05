#include "States/MainMenuState.hpp"
#include "States/PlayState.hpp"
#include "configs.hpp"
#include "States/OptionState.hpp"

using namespace	std;

MainMenuState::MainMenuState() : playButton(BUTTON_TEXTURE_DIRECTORY
	+ string("play_button.png")), exitButton(BUTTON_TEXTURE_DIRECTORY
	+ string("exit_button.png")),optionsButton(BUTTON_TEXTURE_DIRECTORY + string("options_button.png"))
{   
    playButton.change_scale(1.0f,0.70f);
    exitButton.change_scale(1.0f,0.70f);
    optionsButton.change_scale(1.0f,0.70f);

	playButton.setButtonPosition(250, 700);
    optionsButton.setButtonPosition(250,800);
	exitButton.setButtonPosition(250, 900);
	backgroundPath = "main_menu.jpg";
	Music::getInstance(MUSIC_DIRECTORY + std::string("SA_Game_mode_mixed_modes_loop.mp3")).play();
	setBackground();
}

GameState *MainMenuState::eventHandler(sf::RenderWindow &window,
	StateList &state, sf::Event &event)
{
		

	if (playButton.isPressedButton(window, event))
	{
		if (state[PLAY] != nullptr)
            delete state[PLAY];
		state[PLAY] = new PlayState();
		return (state[PLAY]);
	}
	if (exitButton.isPressedButton(window, event))
		window.close();
	if (optionsButton.isPressedButton(window, event))
	{
		return (state[OPTIONS]);
	}
	return (this);
}
GameState *MainMenuState::update(sf::RenderWindow &window, StateList &state)
{
	playButton.HandleHover(window);
    optionsButton.HandleHover(window);
	exitButton.HandleHover(window);
	SliderSFML & slider = SliderSFML::getInstance();
	float volume = slider.getSliderValue();
	// std::cout << volume << std::endl;
	return (this);
}
void MainMenuState::render(sf::RenderWindow &window)
{
	window.draw(backgroundSprite);
	playButton.render(window);
    optionsButton.render(window);
	exitButton.render(window);
}