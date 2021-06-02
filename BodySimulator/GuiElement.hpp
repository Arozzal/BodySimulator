#pragma once
#include <SFML\Graphics.hpp>

class GuiElement
{
protected:
	float height;
	float width;
	float x;
	float y;
	bool clickedOnThis = false;

public:

	float getHeight() { return height; }
	float getWidth() { return width; }

	virtual void setWidth(float width);
	virtual void setHeight(float height);
	virtual void setSize(float width, float height);
	virtual void setPosition(float x, float y);
	virtual void draw(sf::RenderWindow* window) = 0;

	virtual bool isMouseOver();
	virtual bool isMouseReleased();

	float getX() { return x; }
	float getY() { return y; }

};

