#pragma once
#include "BaseBody.hpp"

class DefenderCell : public BaseBody
{
public:
	sf::CircleShape body;
	bool boolGreyState = false;
	sf::CircleShape spikes[6];
	sf::Vector2f spikePoses[6];
	bool isRotating = false;
	float rotOffset = 0;

public:

	DefenderCell(float x, float y, unsigned long long id, System* system);
	virtual ~DefenderCell() { amountOfDefenderCells--; }
	void healthDegneration();
	virtual void update() override;
	virtual void postDamaged() override;
	virtual void draw(sf::RenderWindow* win) override;
};
