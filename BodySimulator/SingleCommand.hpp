#pragma once
#include "GuiElement.hpp"
#include "Interpreter.hpp"

class SingleCommand : public GuiElement
{
	sf::RectangleShape rectangle;
	sf::Font* font;
	sf::Text text;
	sf::Color color;

	bool isSelected = false;
	bool isCmdCommand = true;
	Interpreter::Cmd cmd;
	Interpreter::Atr atr;

	void init(float x, float y, float width, float height, sf::Font* font);

public:

	SingleCommand(float x, float y, float width, float height, Interpreter::Cmd cmd, sf::Font* font);
	SingleCommand(float x, float y, float width, float height, Interpreter::Atr atr, sf::Font* font);

	void setCommand(Interpreter::Cmd);
	void setAttribute(Interpreter::Atr);
	
	Interpreter::Cmd getCmd();
	Interpreter::Atr getAtr();
	void setSelected(bool select);

	void setWidth(float width);
	void setHeight(float height);

	void setPosition(float x, float y) override;
	void setSize(float x, float y) override;
	void draw(sf::RenderWindow* window) override;

	bool isCommand();

};

