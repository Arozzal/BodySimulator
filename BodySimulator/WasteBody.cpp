#include "WasteBody.hpp"



WasteBody::WasteBody(float x, float y, unsigned long long id, System* system)
{
	this->system = system;
	init(x, y, id, T_WASTE);
	radius = 1;
	moveDirection = normalizeVec(getRandomDirectionVec());
	body.setRadius(radius);
	body.setFillColor(sf::Color(150, 75, 0));
	name = "Waste";
	body.setPointCount(9);
}

void WasteBody::update()
{
	if (radius < 10) {
		radius += 10.f * system->getElapsedTime();
		body.setRadius(radius);
		body.setOrigin(radius, radius);
	}



	pos += mulScalarVec(moveDirection, 100.f) * system->getElapsedTime();
	body.setPosition(pos);

	sf::Vector2f collDir;
	BaseBody* collider = 0;

	if (checkCollisionWithStatic(collDir, collider)) {
		pos -= mulScalarVec(moveDirection, 100.f) * system->getElapsedTime();
		moveDirection = normalizeVec({ -collDir.x, -collDir.y });
		collider->damageBody(5.f);
	}

	checkBoundries();
}

void WasteBody::draw(sf::RenderWindow * win)
{
	win->draw(body);
}
