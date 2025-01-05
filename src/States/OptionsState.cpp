#include "MainMenuState.hpp"
#include "States/OptionState.hpp"
#include <string>

OptionsState::OptionsState() : mainmenuButton(BUTTON_TEXTURE_DIRECTORY
	+ std::string("main_menu_button.png"))

{
	// initialize each elements to nullptr
	backgroundPath = "options_background.png";
	setBackground();
	this->mainmenuButton.setButtonPosition(500, 500);

	// Get the singleton instance of SliderSFML and initialize it
	SliderSFML &slider = SliderSFML::getInstance(100, 100);
		// Pass the coordinates once to set them
	slider.create(0, 100);                                 
		// You can use min and max values for the slider
	slider.setSliderValue(50);                             
		// Set the initial value, for example, 50

	if (!this->soundFont.loadFromFile(FONT_DIRECTORY
			+ std::string("Xerox Sans Serif Narrow Bold.ttf")))
	{
		std::cout << "Error: Failed to load font!" << std::endl;
	}
	this->soundText.setFont(this->soundFont);
	this->soundText.setCharacterSize(50);
	this->soundText.setOutlineThickness(1.5);
	this->soundText.setOutlineColor(sf::Color::Blue);
	this->soundText.setFillColor(sf::Color::White);
	this->soundText.setPosition(sf::Vector2f(50, 10));  // Adjust position as needed
    this->soundText.setString("Sound Volume");

}

OptionsState::~OptionsState()
{
	// delete each ability that allocated dynamically
}

GameState *OptionsState::eventHandler(sf::RenderWindow &window,
	StateList &state, sf::Event &event)
{
	// checks whether the restart button is selected or not
	if (mainmenuButton.isPressedButton(window, event))
	{
		return (state[MAINMENU]);
	}
	// checks whether the main menu button is selected or not
	return (this);
}

GameState *OptionsState::update(sf::RenderWindow &window, StateList &state)
{
	this->mainmenuButton.HandleHover(window);
	Music::getInstance().update_music_volume();
	return (this);
}
void OptionsState::render(sf::RenderWindow &window)
{
	window.draw(this->backgroundSprite);
    window.draw(this->soundText);
	SliderSFML &slider = SliderSFML::getInstance();
	slider.draw(window);
	this->mainmenuButton.render(window);
	
}

// float OptionsState::getSliderValue()
// {
//     return (slider1.getSliderValue());  // Return the value of the slider
// }