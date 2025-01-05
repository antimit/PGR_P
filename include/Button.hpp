#ifndef BUTTON_IG
#define BUTTON_IG

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
    Button(std::string);
    void setButtonPosition(float, float);
    bool isButtonPressed(sf::Vector2f);
    void render(sf::RenderWindow &);
    bool isPressedButton(sf::RenderWindow &window, sf::Event &event);
    void HandleHover(sf::RenderWindow & window);
    void change_scale(float x, float y);
    // sf::Sprite get_sprite();
    // void HandlePress();
    
    
    bool isHovered;
    bool isPressed;
    


private:
    sf::Sprite buttonSprite;
    sf::Texture buttonTexture;
    sf::Texture buttonHoverSprite;
};

#endif