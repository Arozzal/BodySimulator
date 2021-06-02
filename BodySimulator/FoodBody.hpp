#pragma once
#include "BaseBody.hpp"
class FoodBody : public BaseBody
{
	sf::CircleShape body;
	bool circleFinished = false;

public:
	FoodBody(float x, float y, unsigned long long id, System* system);
	virtual ~FoodBody() { amountOfFoods--; }
	virtual void update() override;
	virtual void draw(sf::RenderWindow* win) override;

};

