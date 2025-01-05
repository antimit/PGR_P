#include "Button.hpp"
#include <iostream>

using namespace	std;

Button::Button(string texturePath)
{
	this->buttonTexture.loadFromFile(texturePath);
	this->buttonSprite.setTexture(this->buttonTexture);
   
	isHovered = false;
	isPressed = false;
}

// set button position
void Button::setButtonPosition(float x, float y)
{
	this->buttonSprite.setPosition(sf::Vector2f(x, y));
}

// display button
void Button::render(sf::RenderWindow &window)
{
	window.draw(this->buttonSprite);
}

// check if button pressed or not
bool Button::isButtonPressed(sf::Vector2f mousePoint)
{
	if (buttonSprite.getGlobalBounds().contains(mousePoint))
		return (true);
	return (false);
}

bool Button::isPressedButton(sf::RenderWindow &window, sf::Event &event)
{
	if (this->buttonSprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x,
				event.mouseButton.y)))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
                isPressed = true;
                // HandlePress();

				return (true);
			}
		}
	}
    isPressed = false;
	return (false);
}


void Button::HandleHover(sf::RenderWindow & window)
{
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if(buttonSprite.getGlobalBounds().contains(mousePosition))
    {
        if(!isHovered)
        {
            isHovered = true;
            buttonSprite.setColor(sf::Color(200,200,200));
        }
    }
    else
    {
        if(isHovered)
        {
            isHovered = false;
            buttonSprite.setColor(sf::Color(255,255,255));
        }
    }
}

void Button::change_scale(float x, float y)
{
	buttonSprite.setScale(sf::Vector2f(x, y));
}




// void Button::HandlePress()
// {   

//      static bool isAnimating = false;  // This ensures the animation only happens once
//     static float elapsedTime = 0.0f;  // Track how much time has passed

//     const float animationDuration = 100.0f;  // Animation duration for scaling effect

   
//         // Start shrinking the button when pressed
//         buttonSprite.setScale(0.7f, 0.7f);
//         // Use a static clock for smooth animation over multiple frames
//         sf::Clock clock;
        

//         // Gradually scale the button back to normal size
//         while(elapsedTime < animationDuration)
//         {
//             float deltaTime = clock.restart().asSeconds();  // Track the time between frames
//             elapsedTime += deltaTime;
//             // Update the scale based on elapsed time (smooth animation)
//             float scale = 0.7f + (elapsedTime / animationDuration) * 0.1f;  // Gradually return to 1.0f
//             buttonSprite.setScale(scale, scale);
//         }
        
//             // Once the animation is done, reset the scale and stop animating
//             buttonSprite.setScale(1.0f, 1.0f);
           
//             elapsedTime = 0.0f;  // Reset the elapsed time for future animations
        
        
    
    
// }
