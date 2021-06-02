#include "EggBody.hpp"
#include "WasteCell.hpp"
#include "CellBody.hpp"
#include "FoodCell.hpp"
#include <iostream>

EggBody::EggBody(float x, float y, unsigned long long id, System* system, BaseBody* cloneObject, Type type)
{
	this->system = system;
	init(x, y, id, T_EGGBODY);
	radius = 1;
	moveDirection = normalizeVec(getRandomDirectionVec());
	body.setRadius(radius);
	body.setFillColor(sf::Color(64, 64, 64, 256));
	body.setOutlineThickness(2);
	body.setOutlineColor({255, 255, 255, 255});

	name = "Egg";
	inter = cloneObject->getInterpreter();
	cloneType = cloneObject->getBodyType();

	leafCount = inter.getCmdSize();
	if (leafCount > 10)
		leafCount = 10;

	for (int i = 0; i < leafCount; i++) {
		float angle = 360 / leafCount * i;

		float xBL =  cos((angle - 8) * 3.141 / 180.f) * 20.f * 0.5f;
		float yBL =  sin((angle - 8) * 3.141 / 180.f) * 20.f * 0.5f;
														
		float xBR =  cos((angle + 8) * 3.141 / 180.f) * 20.f * 0.5f;
		float yBR =  sin((angle + 8) * 3.141 / 180.f) * 20.f * 0.5f;
													
		float xML =  cos((angle - 12) * 3.141 / 180.f) * 20.f;
		float yML =  sin((angle - 12) * 3.141 / 180.f) * 20.f;
													
		float xMR =  cos((angle + 12) * 3.141 / 180.f) * 20.f;
		float yMR =  sin((angle + 12) * 3.141 / 180.f) * 20.f;
													
		float xTL =  cos((angle - 8) * 3.141 / 180.f) * 20.f * 1.5f;
		float yTL =  sin((angle - 8) * 3.141 / 180.f) * 20.f * 1.5f;
														
		float xTR =  cos((angle + 8) * 3.141 / 180.f) * 20.f * 1.5f;
		float yTR =  sin((angle + 8) * 3.141 / 180.f) * 20.f * 1.5f;


		leafs[i].setPointCount(6);

		leafs[i].setPoint(0, { xBL, yBL });
		leafs[i].setPoint(1, { xML, yML });
		leafs[i].setPoint(2, { xTL, yTL });
		leafs[i].setPoint(3, { xTR, yTR });
		leafs[i].setPoint(4, { xMR, yMR });
		leafs[i].setPoint(5, { xBR, yBR });

		sf::Color innerColor = inter.getCmdColor(inter.getCmdArr()[i]);
		sf::Color outerColor = inter.getAtrColor(inter.getAtrArr()[i]);

		innerColor.a = 128;
		outerColor.a = 128;

		leafs[i].setFillColor(innerColor);
		leafs[i].setOutlineColor(outerColor);
		leafs[i].setOutlineThickness(3);
	}
}

void EggBody::update()
{
	if (radius < 5) {
		radius += 5.f * system->getElapsedTime();
		body.setRadius(radius);
		body.setOrigin(radius, radius);
	}

	sf::Vector2f collDir;
	BaseBody* collider = 0;

	timer -= system->getElapsedTime();
	if (timer <= 0) {
		if (checkCollisionWithStatic(collDir, collider, 40.0f) == false) {
			hatchEgg();
		}
		else {
			timer = 1.0f;
			triedHatches++;
		}

		if (triedHatches > 10) {
			initDeletion();
		}
	}


	pos += mulScalarVec(moveDirection, 100.f) * system->getElapsedTime();


	body.setPosition(pos);
	for (int i = 0; i < leafCount; i++) {
		leafs[i].setPosition(pos);
	}

	

	if (checkCollisionWithStatic(collDir, collider)) {
		pos -= mulScalarVec(moveDirection, 100.f) * system->getElapsedTime();
		moveDirection = normalizeVec({ -collDir.x, -collDir.y });
	}

	checkBoundries();
}

void EggBody::draw(sf::RenderWindow * win)
{
	win->draw(body);
	for (int i = 0; i < leafCount; i++) {
		win->draw(leafs[i]);
	}
}

void EggBody::hatchEgg()
{
	switch (cloneType) {
	case T_WASTECELL: {
		BaseBody* clone = new WasteCell(pos.x, pos.y, system->generateNewId(), system);
		clone->useEnergy(clone->getMaxEnergy() * 0.5);
		system->getStaticUnit()->push_back(clone);
	}
		break;
	case T_CELL: {
		BaseBody* clone = new CellBody(pos.x, pos.y, system->generateNewId(), system);
		clone->useEnergy(clone->getMaxEnergy() * 0.5);
		system->getStaticUnit()->push_back(clone);
	}
		break;
	case T_FOODCELL: {
		BaseBody* clone = new FoodCell(pos.x, pos.y, system->generateNewId(), system);
		clone->useEnergy(clone->getMaxEnergy() * 0.5);
		system->getStaticUnit()->push_back(clone);
	}
		break;
	default:
		break;
	}

	initDeletion();
}
