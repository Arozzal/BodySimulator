#include "SingleCommand.hpp"
#include "Game.hpp"

void SingleCommand::init(float x, float y, float width, float height, sf::Font* font)
{
	setPosition(x, y);
	setSize(width, height);
	this->font = font;
	text.setFont(*font);
}

SingleCommand::SingleCommand(float x, float y, float width, float height, Interpreter::Cmd cmd, sf::Font* font)
{
	init(x, y, width, height, font);
	isCmdCommand = true;
	setCommand(cmd);
}

SingleCommand::SingleCommand(float x, float y, float width, float height, Interpreter::Atr atr, sf::Font* font)
{
	init(x, y, width, height, font);
	isCmdCommand = false;
	setAttribute(atr);
}

void SingleCommand::setCommand(Interpreter::Cmd cmd)
{
	text.setString(Interpreter::getCmdString(cmd));
	this->color = Interpreter::getCmdColor(cmd);
	rectangle.setFillColor(color);
	isCmdCommand = true;
	this->cmd = cmd;
	setPosition(x, y);
}

void SingleCommand::setAttribute(Interpreter::Atr atr)
{
	text.setString(Interpreter::getAtrString(atr));
	this->color = Interpreter::getAtrColor(atr);
	rectangle.setFillColor(color);
	isCmdCommand = false;
	this->atr = atr;
	setPosition(x, y);
}

Interpreter::Cmd SingleCommand::getCmd()
{
	return cmd;
}

Interpreter::Atr SingleCommand::getAtr()
{
	return atr;
}

void SingleCommand::setSelected(bool select)
{
	this->isSelected = select;
}

void SingleCommand::setWidth(float width)
{
	rectangle.setSize(sf::Vector2f(width, this->height));
	this->width = width;
	setPosition(x, y);
}

void SingleCommand::setHeight(float height)
{
	rectangle.setSize(sf::Vector2f(this->width, height));
	this->height = height;
	setPosition(x, y);
}

void SingleCommand::setPosition(float x, float y)
{
	rectangle.setPosition(x, y);
	this->text.setPosition(x + width / 2.0f - text.getGlobalBounds().width / 2.0f, y + height / 2.0f - text.getGlobalBounds().height / 2.0f - 7.0f);
	this->x = x;
	this->y = y;
}

void SingleCommand::setSize(float width, float height)
{
	setWidth(width);
	setHeight(height);
}

void SingleCommand::draw(sf::RenderWindow* window)
{
	if (isSelected) {
		double col = (sin(Game::getInst().getTimeInMilliseconds() / 100.0) + 1) / 2;
		sf::Color color;									  
		color.r = this->color.r + ((200 - this->color.r) * col);
		color.g = this->color.g + ((200 - this->color.g) * col);
		color.b = this->color.b + ((200 - this->color.b) * col);

		rectangle.setFillColor(color);
	}

	window->draw(rectangle);
	window->draw(text);
}

bool SingleCommand::isCommand()
{
	return isCmdCommand;
}
