#pragma once
#include <SFML\Graphics.hpp>
#include "Bar.hpp"
#include "CommandSelectMenu.hpp"
#include "DoubleCommand.hpp"

class BaseBody;
class Gui
{
	bool visible = false;
	int sizeX = 0;
	int sizeY = 0;
	int posx = 0;
	int posy = 0;
	float borderOffsetX = 10;
	float cmdOffsetX = 40;
	sf::RenderWindow* window;

	sf::RectangleShape backgroundSquare;
	sf::Font* font;
	sf::Text nameAndId;

	float hpMax = 1.f;
	float hp = 1.f;
	float energyMax = 1.f;
	float energy = 1.f;

	Bar* barEnergy;
	Bar* barHealth;

	CommandSelectMenu* commandSelectMenu;

	const int amountOfPopulationTexts = 7;
	sf::String populationTemplateStrings[7];
	sf::Text populationTexts[7];
	int populationAmountStrings[7];

	sf::Texture arrowTex;
	sf::Sprite arrowSprLeft;
	sf::Sprite arrowSprRight;

	std::vector<DoubleCommand*> cmds;

	int amountOfCmds = 0;

	BaseBody* selectedBody;

	SingleCommand* selectedCommand = nullptr;
	int selectedCommandIndex = -1;

public:
	Gui(sf::RenderWindow* window, sf::Font* font);

	bool isMouseOverAnElement();

	void show() { visible = true; };
	void hide();
	void clearSelection();
	void updateSize(int sizeX, int sizeY);
	void updatePos(int posx, int posy);
	void updateBody(BaseBody* body);
	void update();
	void draw();

	~Gui();
};

