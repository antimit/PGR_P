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


void Button::setButtonPosition(float x, float y)
{
	this->buttonSprite.setPosition(sf::Vector2f(x, y));
}


void Button::render(sf::RenderWindow &window)
{
	window.draw(this->buttonSprite);
}


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












   




        










        


           

        
        
    
    

