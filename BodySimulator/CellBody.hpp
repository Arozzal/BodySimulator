#pragma once
#include "BaseBody.hpp"

class CellBody : public BaseBody
{
	sf::CircleShape body;
	bool boolGreyState = false;

public:

	CellBody(float x, float y, unsigned long long id, System* system);
	virtual ~CellBody() { amountOfCells--; }
	void healthDegneration();
	virtual void update() override;
	virtual void postDamaged() override;
	virtual void draw(sf::RenderWindow* win) override;
	

};

