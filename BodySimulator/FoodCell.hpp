#pragma once
#include "BaseBody.hpp"

class FoodCell : public BaseBody
{
	sf::CircleShape body;

	int leafCount = 6;
	sf::ConvexShape leafs[6];

	bool boolGreyState = false;
public:
	FoodCell(float x, float y, unsigned long long id, System* system);
	virtual ~FoodCell() { amountOfFoodCells--; }
	void healthDegneration();
	virtual void update() override;
	virtual void postDamaged() override;
	virtual void draw(sf::RenderWindow* win) override;
};

