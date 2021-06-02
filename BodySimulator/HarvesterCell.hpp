#pragma once
#include "BaseBody.hpp"

class HarvesterCell : public BaseBody
{
public:
	sf::CircleShape body;
	bool boolGreyState = false;
	sf::CircleShape tail[5];

public:

	HarvesterCell(float x, float y, unsigned long long id, System* system);
	virtual ~HarvesterCell() { amountOfHarvesterCells--; }
	void healthDegneration();
	virtual void update() override;
	virtual void postDamaged() override;
	virtual void draw(sf::RenderWindow* win) override;
};
