#pragma once
#include "BaseBody.hpp"

class PredatorCell : public BaseBody
{
public:
	sf::CircleShape body;
	bool boolGreyState = false;
	sf::CircleShape tail[10];
	sf::CircleShape spikes[6];
	sf::Vector2f spikePoses[10];

public:

	PredatorCell(float x, float y, unsigned long long id, System* system);
	virtual ~PredatorCell() { amountOfHarvesterCells--; }
	void healthDegneration();
	virtual void update() override;
	virtual void postDamaged() override;
	virtual void draw(sf::RenderWindow* win) override;
};
