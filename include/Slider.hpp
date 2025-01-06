#ifndef SLIDER_IG
#define SLIDER_IG

#include <SFML/Graphics.hpp>
#include <iostream>

class SliderSFML
{
    SliderSFML(int x, int y);
	sf::RectangleShape slider;
	sf::RectangleShape axis;
	sf::Font font;
	sf::Text text;
	int minValue;
	int maxValue;
	int xCord;
	int yCord;
	int axisWidth;
	int axisHeight;
	int sliderWidth;
	int sliderHeight;
	float sliderValue;
	
public:
	
    static SliderSFML& getInstance(int x = 0, int y = 0)
    {
        static SliderSFML instance(x, y);  
        return instance;
    }

    
    SliderSFML(const SliderSFML&) = delete;
    SliderSFML& operator=(const SliderSFML&) = delete;
	sf::Text returnText(int x, int y, std::string z, int fontSize);
	void create(int min, int max);
	void logic(sf::RenderWindow &window);
	float getSliderValue();
	void setSliderValue(float newValue);
	void setSliderPercentValue(float newPercentValue);
	void draw(sf::RenderWindow & window);
	bool changed;
};

#endif