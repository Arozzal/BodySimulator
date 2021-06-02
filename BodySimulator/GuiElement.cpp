#include "GuiElement.hpp"
#include "Game.hpp"

void GuiElement::setWidth(float width)
{
	this->width = width;
}

void GuiElement::setHeight(float height)
{
	this->height = height;
}

void GuiElement::setSize(float width, float height)
{
	setHeight(height);
	setWidth(width);
}

void GuiElement::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool GuiElement::isMouseOver()
{
	sf::Vector2i mpos = Game::getInst().getMousePos();
	if (mpos.x >= x && mpos.x <= x + width && mpos.y >= y && mpos.y < y + height) {
		return true;
	}
	
	return false;
}

bool GuiElement::isMouseReleased()
{
	Game game = Game::getInst();

	if (game.isMouseClickedLastFrame() == false && game.isMouseClicked() == true) {
		if (isMouseOver()) {
			clickedOnThis = true;
		}
		else {
			clickedOnThis = false;
		}
	}

	if (isMouseOver()) {
		if (game.isMouseClickedLastFrame() == true && game.isMouseClicked() == false && clickedOnThis) {
			return true;
		}
	}

	return false;
}
