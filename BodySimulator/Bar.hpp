#pragma once
#include <SFML\Graphics.hpp>

#include "GuiElement.hpp"

class Bar : public GuiElement
{
	sf::RectangleShape barMax;
	sf::RectangleShape bar;
	sf::Font* font;
	sf::Text text;


	float percentage = 0;
	int currGauge = 0;
	int maxGauge = 0;

public:
	Bar(float x, float y, float width, float height, int currGauge, int maxGauge, sf::Color color, sf::Font* font);

	void setWidth(float width);
	void setHeight(float height);
	
	void setPosition(float x, float y) override;
	void setSize(float x, float y) override;
	void setAmount(int currGauge, int maxGauge);
	void setString(std::string str);
	void draw(sf::RenderWindow* window) override;



};

