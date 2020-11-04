#include "SliderSFML.h"
#include <string>

SliderSFML::SliderSFML(int x, int y)
{
	xCord = x;
	yCord = y;
	axisHeight = 10;
	axisWidth = 200;
	sliderWidth = 20;
	sliderHeight = 30;
	if (!font.loadFromFile("Fonts\\ProductSans-Black.ttf"))
		std::cout << "Error loading font\n";

	text.setFont(font);
	text.setFillColor(sf::Color::White);

	axis.setPosition(x, y);
	axis.setOrigin(0, axisHeight / 2);
	axis.setSize(sf::Vector2f(axisWidth, axisHeight));
	axis.setFillColor(sf::Color(63,63,63));
	slider.setPosition(x, y);
	slider.setOrigin(sliderWidth / 2, sliderHeight / 2);
	slider.setSize(sf::Vector2f(sliderWidth, sliderHeight));
	slider.setFillColor(sf::Color(192,192,192));
}

sf::Text SliderSFML::returnText(int x, int y, std::string z, int fontSize)
{
	text.setCharacterSize(fontSize);
	text.setPosition(x, y);
	text.setString(z);
	return text;
}

void SliderSFML::create(int min, int max, std::string new_name, bool b)
{
	sliderValue = min;
	minValue = min;
	maxValue = max;
	snapToInt = b;
	name = new_name;
}

void SliderSFML::logic(sf::RenderWindow &window)
{
	isValueChanged = false;
	if (slider.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
		&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		isActive = true;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isActive) {
		isActive = false;
		isValueChanged = true;
	}
	if (isActive)
	{
		if (sf::Mouse::getPosition(window).x < xCord)
		{
			slider.setPosition(xCord, yCord);
			sliderValue = minValue;
		} 
		else if (sf::Mouse::getPosition(window).x > xCord + axisWidth)
		{
			slider.setPosition(xCord + axisWidth, yCord);
			sliderValue = maxValue;
		}
		else if (sf::Mouse::getPosition(window).x >= xCord && sf::Mouse::getPosition(window).x <= xCord + axisWidth)
		{
			slider.setPosition(sf::Mouse::getPosition(window).x, yCord);
			sliderValue = (minValue + ((slider.getPosition().x - xCord) / axisWidth * (maxValue - minValue)));
		}

		
	}
	if (snapToInt) {
		sliderValue = getSliderValue();
		slider.setPosition(xCord + axisWidth * (sliderValue / (maxValue - minValue)), yCord);
	}
}

float SliderSFML::getSliderValue()
{
	if (snapToInt) return std::round(sliderValue);
	return sliderValue;
}
bool SliderSFML::getIsValueChanged() {
	return isValueChanged;
}

void SliderSFML::setSliderValue(float newValue)
{
	if (newValue >= minValue && newValue <= maxValue)
	{
		sliderValue = newValue;
		float diff = maxValue - minValue;
		float diff2 = newValue - minValue;
		float zzz = axisWidth / diff;
		float posX = zzz*diff2;
		posX += xCord;
		slider.setPosition(posX, yCord);
	}
}

void SliderSFML::setSliderPercentValue(float newPercentValue)
{
	if (newPercentValue >= 0 && newPercentValue <= 100)
	{
		sliderValue = newPercentValue / 100 * maxValue;
		slider.setPosition(xCord + (axisWidth*newPercentValue / 100), yCord);
	}
}

void SliderSFML::draw(sf::RenderWindow &window)
{
	logic(window);
	window.draw(returnText(xCord - 200, yCord - 15, name, 30));
	window.draw(returnText(xCord - 10, yCord + 5, std::to_string(minValue), 20));
	window.draw(axis);
	window.draw(returnText(xCord + axisWidth - 10, yCord + 5, std::to_string(maxValue), 20));
	window.draw(slider);
	window.draw(returnText(slider.getPosition().x - sliderWidth, slider.getPosition().y - sliderHeight,
		std::to_string((int)std::round(sliderValue)), 15));
}
