#pragma once
#include "BaseBody.hpp"

class WasteCell : public BaseBody
{
	sf::CircleShape innerBody;
	sf::CircleShape outerBody;
	bool boolGreyState = false;

public:

	WasteCell(float x, float y, unsigned long long id, System* system);
	virtual ~WasteCell() { amountOfWasteCells--; }

	void healthDegneration();
	virtual void update() override;
	virtual void postDamaged() override;
	virtual void draw(sf::RenderWindow* win) override;


};

