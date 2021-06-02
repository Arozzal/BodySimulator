#pragma once
#include <SFML\Graphics.hpp>



class Game
{
	sf::RenderWindow* window;
	static Game game;
	bool clickedLastFrame = false;
	bool clickedThisFrame = false;


public:

	static Game& getInst();
	void setWindow(sf::RenderWindow* window);
	
	sf::Vector2i getMousePos();
	bool isMouseClicked();
	bool isMouseClickedLastFrame();
	long getTimeInMilliseconds();
	void update();
};

