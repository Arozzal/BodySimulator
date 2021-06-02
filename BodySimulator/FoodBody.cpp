#include "FoodBody.hpp"




FoodBody::FoodBody(float x, float y, unsigned long long id, System* system)
{
	this->system = system;
	init(x, y, id, T_FOOD);
	radius = 1;
	moveDirection = normalizeVec(getRandomDirectionVec());
	body.setRadius(radius);
	body.setFillColor(sf::Color::Red);
	body.setPointCount(9);
	name = "Food";
}

void FoodBody::update()
{
	if (circleFinished == false) {
		radius += 8.f * system->getElapsedTime();
		body.setRadius(radius);
		body.setOrigin(radius, radius);
		if (radius >= 8)
			circleFinished = true;
	}

	

	
	

	sf::Vector2f collDir;
	BaseBody* placeHolder = 0;
	if (checkCollisionWithStatic(collDir, placeHolder)) {
		pos += mulScalarVec(moveDirection, 25.f) * system->getElapsedTime();
	}
	else {
		pos += mulScalarVec(moveDirection, 100.f) * system->getElapsedTime();
	}

	body.setPosition(pos);
	checkBoundries();
}

void FoodBody::draw(sf::RenderWindow * win)
{
	win->draw(body);
}
