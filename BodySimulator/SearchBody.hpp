#pragma once
#include "BaseBody.hpp"



class SearchBody : public BaseBody
{
	bool enemyFound = false;
	sf::Vector2f enemyOffset = {0, 0};
	sf::CircleShape body;
	float writeTime = 0;
public:
	SearchBody(float x, float y, unsigned long long id, System* system);
	virtual ~SearchBody() { amountOfSearchers--; }
	virtual void update() override;
	virtual void draw(sf::RenderWindow* win) override;

};