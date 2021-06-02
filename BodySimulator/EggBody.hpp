#pragma once
#include "BaseBody.hpp"

class EggBody : public BaseBody
{
public:
	sf::CircleShape body;
	int leafCount = 0;
	sf::ConvexShape leafs[10];
	sf::Vector2f leafPos[10];
	float timer = 20.f;
	int triedHatches = 0;
	Type cloneType = Type::T_BASE;

public:
	EggBody(float x, float y, unsigned long long id, System* system, BaseBody* cloneObject, Type type);
	virtual ~EggBody() { amountOfEggBodies--;};
	virtual void update() override;
	virtual void draw(sf::RenderWindow* win) override;
	void hatchEgg();
};

