#include "DoubleCommand.hpp"

DoubleCommand::DoubleCommand(float x, float y, float width, float height, Interpreter::Cmd cmd, Interpreter::Atr atr, sf::Font* font)
{
	this->cmd = new SingleCommand(x, y, width * 0.5f, height, cmd, font);
	this->atr = new SingleCommand(x + width * 0.5f, y, width * 0.5f, height, atr, font);
	setPosition(x, y);
	setSize(width, height);
}

void DoubleCommand::setWidth(float width)
{
	cmd->setWidth(width * 0.5f);
	atr->setWidth(width * 0.5f);
	this->width = width;
	setPosition(x, y);
}

void DoubleCommand::setHeight(float height)
{
	cmd->setHeight(height);
	atr->setHeight(height);
	this->height = height;
	setPosition(x, y);
}

void DoubleCommand::setCommand(Interpreter::Cmd cmd)
{
	this->cmd->setCommand(cmd);
}

void DoubleCommand::setAttribute(Interpreter::Atr atr)
{
	this->atr->setAttribute(atr);
}

void DoubleCommand::setPosition(float x, float y)
{
	cmd->setPosition(x, y);
	atr->setPosition(x + width * 0.5, y);
	this->x = x;
	this->y = y;
}

void DoubleCommand::setSize(float width, float height)
{
	setWidth(width);
	setHeight(height);
}

void DoubleCommand::draw(sf::RenderWindow* window)
{
	cmd->draw(window);
	atr->draw(window);
}

SingleCommand* DoubleCommand::getCmd()
{
	return cmd;
}

SingleCommand* DoubleCommand::getAtr()
{
	return atr;
}

DoubleCommand::~DoubleCommand()
{
	delete cmd;
	delete atr;
}
