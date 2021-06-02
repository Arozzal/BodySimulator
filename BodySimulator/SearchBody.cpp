#include "SearchBody.hpp"



SearchBody::SearchBody(float x, float y, unsigned long long id, System* system)
{
	this->system = system;
	init(x, y, id, T_SEARCHER);
	radius = 1;
	moveDirection = normalizeVec(getRandomDirectionVec());
	body.setRadius(radius);
	body.setFillColor(sf::Color(255, 255, 0));
	name = "Searcher";
	body.setPointCount(3);
}

void SearchBody::update()
{
	if (radius < 10) {
		radius += 10.f * system->getElapsedTime();
		body.setRadius(radius);
		body.setOrigin(radius, radius);
	}


	sf::Vector2f collDir;
	BaseBody* collider = 0;

	writeTime += system->getElapsedTime();

	if (checkCollision(system->getMovingUnit(), getPos(), getRadius(), collider, T_PREDATORCELL)) {
		if (enemyFound == false) {
			enemyOffset = getPos() - collider->getPos();
			enemyOffset *= 0.7f;
			enemyFound = true;
		}

		setPos(collider->getPos() + enemyOffset);

		if (writeTime > 1.f) {
			writeTime = 0;
			Interpreter::writeVarEnemiePos(getId(), getPos());
		}
	}
	else {
		if (enemyFound) {
			inter.deleteVarEnemiePos(getId());
			enemyFound = false;
		}
		pos += mulScalarVec(moveDirection, 100.f) * system->getElapsedTime();
		if (checkCollisionWithStatic(collDir, collider)) {
			pos -= mulScalarVec(moveDirection, 100.f) * system->getElapsedTime();
			moveDirection = normalizeVec({ -collDir.x, -collDir.y });
		}
	}

	body.setPosition(pos);
	checkBoundries();
}

void SearchBody::draw(sf::RenderWindow * win)
{
	win->draw(body);
}
