#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

class SliderSFML
{
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
	bool isActive;
	bool isValueChanged;
	bool snapToInt;
	std::string name;
public:
	SliderSFML(int x, int y);
	sf::Text returnText(int x, int y, std::string z, int fontSize);
	void create(int min, int max, std::string name = "Slider", bool b = false);
	void logic(sf::RenderWindow &window);
	float getSliderValue();
	bool getIsValueChanged();
	void setSliderValue(float newValue);
	void setSliderPercentValue(float newPercentValue);
	void draw(sf::RenderWindow & window);
};

