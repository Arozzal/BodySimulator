#pragma once
#include "SingleCommand.hpp"

class DoubleCommand : public GuiElement
{
	SingleCommand* cmd;
	SingleCommand* atr;

public:

	DoubleCommand(float x, float y, float width, float height, Interpreter::Cmd cmd, Interpreter::Atr atr, sf::Font* font);

	void setWidth(float width);
	void setHeight(float height);

	void setCommand(Interpreter::Cmd cmd);
	void setAttribute(Interpreter::Atr atr);

	void setPosition(float x, float y) override;
	void setSize(float x, float y) override;
	void draw(sf::RenderWindow* window) override;

	SingleCommand* getCmd();
	SingleCommand* getAtr();

	~DoubleCommand();

};
