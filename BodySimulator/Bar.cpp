#include "Bar.hpp"
#include "extendedMath.hpp"

static const float barOff = 2.0f;

Bar::Bar(float x, float y, float width, float height, int currGauge, int maxGauge, sf::Color color, sf::Font* font) 
{
	setPosition(x, y);
	setSize(width, height);
	
	this->font = font;
	text.setFont(*font);
	text.setCharacterSize(18);
	setAmount(currGauge, maxGauge);
	bar.setFillColor(color);
	barMax.setFillColor(sf::Color(200, 200, 200));
}

void Bar::setWidth(float width)
{
	GuiElement::setWidth(width);
	barMax.setSize(sf::Vector2f(width, barMax.getGlobalBounds().height));
	bar.setSize(sf::Vector2f(width * percentage - 2 * barOff, height - 2 * barOff));
	setString(text.getString());
}

void Bar::setHeight(float height)
{
	GuiElement::setHeight(height);
	barMax.setSize(sf::Vector2f(barMax.getGlobalBounds().width, height));
	bar.setSize(sf::Vector2f(width * percentage - 2 * barOff, height - 2 * barOff));
	setString(text.getString());
}

void Bar::setPosition(float x, float y)
{
	GuiElement::setPosition(x, y);
	bar.setPosition(x + barOff, y + barOff);
	barMax.setPosition(x, y);
	setString(text.getString());
}

void Bar::setSize(float width, float height)
{
	setWidth(width);
	setHeight(height);
}

void Bar::setAmount(int currGauge, int maxGauge)
{
	this->currGauge = currGauge;
	this->maxGauge = maxGauge;

	this->percentage = 1.0f / maxGauge * currGauge;
	setString(std::to_string(currGauge) + "/" + std::to_string(maxGauge) + " " + setAmountOfDecimals(this->percentage * 100.0f, 0) + "%");
	setWidth(width);
}

void Bar::setString(std::string str)
{
	this->text.setString(str);
	this->text.setPosition(x + width / 2.0f - text.getGlobalBounds().width / 2.0f, y + height / 2.0f - text.getGlobalBounds().height / 2.0f - 2);
}

void Bar::draw(sf::RenderWindow* window)
{
	window->draw(barMax);
	window->draw(bar);
	window->draw(text);
}
