#pragma once
#include "BaseBody.hpp"

class WasteBody : public BaseBody
{
	sf::CircleShape body;
public:
	WasteBody(float x, float y, unsigned long long id, System* system);
	virtual ~WasteBody() { amountOfWastes--; }
	virtual void update() override;
	virtual void draw(sf::RenderWindow* win) override;

};