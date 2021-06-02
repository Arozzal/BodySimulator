#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

#include "extendedMath.hpp"
#include "BaseBody.hpp"

class Gui;
class ClickManager;
class BaseBody;
class System
{

	sf::RenderWindow* window;
	std::vector<BaseBody*> simpleUnits;
	std::vector<BaseBody*> staticUnits;
	std::vector<BaseBody*> movingUnits;
	sf::Clock clock;
	sf::Font font;
	sf::Text fpsText;
	sf::View view;
	sf::View guiView;

	unsigned long long currentId = 0;

	float winSizeX = 0;
	float winSizeY = 0;
	float winPosX = 0;
	float winPosY = 0;
	float winScale = 1.f;

	float elapsedTime = 0;
	int fps;

	Gui* gui;
	ClickManager* clickManager;
	BaseBody* clickedThing = nullptr;

public:

	std::vector<BaseBody*>* getSimpleUnit() {return &simpleUnits;};
	std::vector<BaseBody*>* getStaticUnit() { return &staticUnits; };
	std::vector<BaseBody*>* getMovingUnit() { return &movingUnits; };

	void calculateTime();
	
	float getElapsedTime() { return elapsedTime; }
	unsigned long long generateNewId() { currentId++; return currentId; }

	System();
	void updateInput();
	void update();
	void draw();
	~System();
};


