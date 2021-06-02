#pragma once
#include "SingleCommand.hpp"

class CommandSelectMenu : public GuiElement
{
	std::vector<SingleCommand> cmds;
	std::vector<SingleCommand> attrs;
	sf::RectangleShape background;

	bool isCmdMode = false;
	sf::Font* font;
	float offset = 20.0f;
	float elementHight = 35.0f;

public:

	CommandSelectMenu(float x, float y, float width, float height, sf::Color color, sf::Font* font);

	void setWidth(float width);
	void setHeight(float height);

	Interpreter::Cmd getClickedCmd();
	Interpreter::Atr getClickedAtr();

	bool IsInCmdMode();

	void setCmdMode(bool mode);
	void setPosition(float x, float y) override;
	void setSize(float x, float y) override;
	void draw(sf::RenderWindow* window) override;

};

