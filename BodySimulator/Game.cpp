#include "Game.hpp"
#include <chrono>


Game Game::game;

Game& Game::getInst()
{
	return Game::game;
}

void Game::setWindow(sf::RenderWindow* win)
{
	this->window = win;
}

sf::Vector2i Game::getMousePos()
{
	return sf::Mouse::getPosition(*window);
}

bool Game::isMouseClicked()
{
	return clickedThisFrame;
}

bool Game::isMouseClickedLastFrame()
{
	return clickedLastFrame;
}

long Game::getTimeInMilliseconds()
{
	unsigned long now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	return now;
}

void Game::update()
{
	clickedLastFrame = clickedThisFrame;
	clickedThisFrame = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

