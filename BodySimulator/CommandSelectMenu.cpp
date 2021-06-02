#include "CommandSelectMenu.hpp"

CommandSelectMenu::CommandSelectMenu(float x, float y, float width, float height, sf::Color color, sf::Font* font)
{
	for (int i = 0; i < Interpreter::Cmd::C_SIZE; i++) {
		SingleCommand singleCommand(x + offset, y + offset, width - offset * 2, elementHight, Interpreter::Cmd(i), font);
		cmds.push_back(singleCommand);
	}

	for (int i = 0; i < Interpreter::Atr::A_SIZE; i++) {
		SingleCommand singleCommand(x + offset, y + offset, width - offset * 2, elementHight, Interpreter::Atr(i), font);
		attrs.push_back(singleCommand);
	}


	setPosition(x, y);
	setSize(width, height);
	background.setFillColor(color);
	this->font = font;
}

void CommandSelectMenu::setWidth(float width)
{
	this->width = width;
	for (int i = 0; i < Interpreter::Cmd::C_SIZE; i++) {
		cmds[i].setWidth(width - 2 * offset);
	}

	for (int i = 0; i < Interpreter::Atr::A_SIZE; i++) {
		attrs[i].setWidth(width - 2 * offset);
	}
}

void CommandSelectMenu::setHeight(float height)
{
	background.setSize(sf::Vector2f(width, height));
	this->height = height;
}

Interpreter::Cmd CommandSelectMenu::getClickedCmd()
{
	for (int i = 0; i < Interpreter::Cmd::C_SIZE; i++) {
		if (cmds[i].isMouseReleased()) {
			return cmds[i].getCmd();
		}
	}
	return Interpreter::Cmd::C_NONE;
}

Interpreter::Atr CommandSelectMenu::getClickedAtr()
{
	for (int i = 0; i < Interpreter::Atr::A_SIZE; i++) {
		if (attrs[i].isMouseReleased()) {
			return attrs[i].getAtr();
		}
	}
	return Interpreter::Atr::A_NONE;
}

bool CommandSelectMenu::IsInCmdMode()
{
	return isCmdMode;
}

void CommandSelectMenu::setCmdMode(bool mode)
{
	isCmdMode = mode;
}

void CommandSelectMenu::setPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	background.setPosition(x, y);
	for (int i = 0; i < Interpreter::Cmd::C_SIZE; i++) {
		cmds[i].setPosition(x + offset, y + offset + i * elementHight);
	}

	for (int i = 0; i < Interpreter::Atr::A_SIZE; i++) {
		attrs[i].setPosition(x + offset, y + offset + i * elementHight);
	}
}

void CommandSelectMenu::setSize(float width, float height)
{
	setWidth(width);
	setHeight(height);
}

void CommandSelectMenu::draw(sf::RenderWindow* window)
{
	window->draw(background);
	if (isCmdMode) {
		for (int i = 0; i < Interpreter::Cmd::C_SIZE; i++) {
			cmds[i].draw(window);
		}
	}
	else {
		for (int i = 0; i < Interpreter::Atr::A_SIZE; i++) {
			attrs[i].draw(window);
		}
	}
}
