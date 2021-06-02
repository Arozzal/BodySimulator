#include "BaseBody.hpp"
#include "WasteBody.hpp"
#include "FoodBody.hpp"
#include "EggBody.hpp"


#include <iostream>

int BaseBody::amountOfFoods = 0;
int BaseBody::amountOfWastes = 0;
int BaseBody::amountOfCells = 0;
int BaseBody::amountOfFoodCells = 0;
int BaseBody::amountOfEggBodies = 0;
int BaseBody::amountOfWasteCells = 0;
int BaseBody::amountOfHarvesterCells = 0;
int BaseBody::amountOfPredators = 0;
int BaseBody::amountOfSearchers = 0;
int BaseBody::amountOfDefenderCells = 0;

void BaseBody::init(float x, float y, unsigned long long id, Type type)
{
	pos = sf::Vector2f(x, y);
	this->id = id;
	this->type = type;

	switch (type) {
	case T_FOOD:
		amountOfFoods++;
		break;
	case T_WASTE:
		amountOfWastes++;
		break;
	case T_CELL:
		amountOfCells++;
		break;
	case T_FOODCELL:
		amountOfFoodCells++;
		break;
	case T_EGGBODY:
		amountOfEggBodies++;
		break;
	case T_WASTECELL:
		amountOfWasteCells++;
		break;
	case T_HARVESTERCELL:
		amountOfHarvesterCells++;
		break;
	case T_PREDATORCELL:
		amountOfPredators++;
		break;
	case T_SEARCHER:
		amountOfSearchers++;
		break;
	case T_DEFENDERCELL:
		amountOfDefenderCells++;
		break;
	default:
		std::cout << "Unknown Type initialised" << std::endl;
		break;
	}
}

void BaseBody::checkBoundries()
{
	if (pos.x < -4000) {
		pos.x = 4000;
	}

	if (pos.x > 4000) {
		pos.x = -4000;
	}

	if (pos.y < -4000) {
		pos.y = 4000;
	}

	if (pos.y > 4000) {
		pos.y = -4000;
	}

	setChunk(getPos().x / 50, getPos().y / 50);
}

bool BaseBody::checkChunk(int xChunk1, int xChunk2, int yChunk1, int yChunk2)
{
	if (abs(xChunk1 - xChunk2) <= 2 && abs(yChunk1 - yChunk2) <= 2) {
		return true;
	}

	return false;
}

void BaseBody::initDeletion()
{
	deleteThisBody = true;
}

bool BaseBody::checkCollisionWithStatic(sf::Vector2f& direction, BaseBody*& collidedBody, float radius)
{
	std::vector<BaseBody*>* simpelUnits = system->getStaticUnit();

	if (radius < 0)
		radius = this->getRadius();

	for (BaseBody* body : *simpelUnits) {
		if (checkChunk(getXChunk(), body->getXChunk(), getYChunk(), body->getYChunk()) == false) {
			continue;
		}

		sf::Vector2f currPos = body->getPos();
		sf::Vector2f finalPos = { abs(pos.x - currPos.x), abs(pos.y - currPos.y) };
		
		if (sqrt(finalPos.x * finalPos.x + finalPos.y * finalPos.y) < body->radius + (body->radiusBorder / 2) + radius &&
			sqrt(finalPos.x * finalPos.x + finalPos.y * finalPos.y) > body->radius - radius) {
			
			if (sqrt(finalPos.x * finalPos.x + finalPos.y * finalPos.y) < body->radius + (body->radiusBorder / 2) - radius) {
				direction = { -(currPos.x - pos.x), -(currPos.y - pos.y) };
			}
			else {
				direction = { currPos.x - pos.x, currPos.y - pos.y };
			}


			collidedBody = body;
			return true;
		}
	}

	return false;
}

bool BaseBody::checkCollision(std::vector<BaseBody*>* bodies, sf::Vector2f pos, float radius, BaseBody*& collidedObject, Type checkType, bool checkOnlyEnergyless)
{
	for (BaseBody* body : *bodies) {
		if (checkChunk(getXChunk(), body->getXChunk(), getYChunk(), body->getYChunk()) == false) {
			continue;
		}

		if (checkOnlyEnergyless) {
			if (body->getEnergy() > 0) {
				continue;
			}
		}

		if (checkType != T_BASE) {
			if (checkType != body->getBodyType()) {
				continue;
			}
		}

		sf::Vector2f otherPos = body->getPos();
		sf::Vector2f diff = { abs(otherPos.x - pos.x), abs(otherPos.y - pos.y) };
		float length = sqrt(diff.x * diff.x + diff.y * diff.y);

		if (length < radius + body->getRadius()) {
			

			collidedObject = body;
			return true;
		}
	}
	collidedObject = nullptr;
	return false;
}

bool BaseBody::checkCollisionOuterRing(std::vector<BaseBody*>* bodies, sf::Vector2f pos, float radius, float outerRadius, BaseBody*& collidedObject, Type checkType)
{


	for (int i = 0; i < bodies->size(); i++) {

		if (checkChunk(getXChunk(), bodies->at(i)->getXChunk(), getYChunk(), bodies->at(i)->getYChunk()) == false) {
			continue;
		}

		if (checkType != T_BASE) {
			if (checkType != bodies->at(i)->getBodyType()) {
				continue;
			}
		}

		sf::Vector2f otherPos = bodies->at(i)->getPos();
		sf::Vector2f diff = { abs(otherPos.x - pos.x), abs(otherPos.y - pos.y) };
		float length = sqrt(diff.x * diff.x + diff.y * diff.y);

		if (length < outerRadius + bodies->at(i)->getRadius()) {
			if (length < radius + bodies->at(i)->getRadius()) {
				continue;
			}
			
			
			collidedObject = bodies->at(i);
			return true;
		}
	}
	collidedObject = nullptr;
	return false;
}

void BaseBody::damageBody(float amount)
{
	damageCooldown -= system->getElapsedTime();
	
	//if (damageCooldown <= 0) {
		health -= amount;
		postDamaged();
		//damageCooldown = 1.f;
	//}
}

bool BaseBody::isStaticUnit()
{
	switch (type) {
	case T_CELL:
	case T_HARVESTERCELL:
	case T_WASTECELL:
		return true;
	}
	return false;
}

void BaseBody::addEnergy(float amount)
{
	this->energy += amount;
	if (energy > maxEnergy) {
		energy = maxEnergy;
	}
}

void BaseBody::executeTask()
{
	switch (inter.getCurrentTask()) {
	case Interpreter::TK_MOVE_POS: {
		sf::Vector2f movDir =  inter.getVarPos() - getPos();
		if (sqrt(movDir.x * movDir.x + movDir.y * movDir.y) < 5) {
			inter.taskFinnished();
			break;
		}
		setPos(getPos() + normalizeVec(movDir) * system->getElapsedTime() * 200.f) ;
		
	}
		break;
	default:
		break;
	}
}

void BaseBody::execCommandChain()
{
	currCmd =  inter.getCurrentCmd();
	currAtr = inter.getCurrentAtr();

	if (getEnergy() <= 0) {
		return;
	}

	switch (currCmd) {
	case Interpreter::C_REPAIR:
		useEnergy(2.f + float(getRandomNumberRange(1, 10000)) / 10000.f);
		execRepairCommand();
		break;
	case Interpreter::C_CONSUME:
		useEnergy(2.f + float(getRandomNumberRange(1, 10000)) / 10000.f);
		execConsumeCommand();
		break;
	case Interpreter::C_MOVEOUT:
		useEnergy(2.f + float(getRandomNumberRange(1, 10000)) / 10000.f);
		execMoveOutCommand();
		break;
	case Interpreter::C_MOVEIN:
		useEnergy(2.f + float(getRandomNumberRange(1, 10000)) / 10000.f);
		execMoveInCommand();
		break;
	case Interpreter::C_REPLICATE:
		useEnergy(2.f + float(getRandomNumberRange(1, 10000)) / 10000.f);
		execReplicateCommand();
		break;
	case Interpreter::C_WRITE_POS:
		useEnergy(1.f + float(getRandomNumberRange(1, 10000)) / 10000.f);
		execWritePos();
		break;
	case Interpreter::C_MOVE:
		useEnergy(2.f + float(getRandomNumberRange(1, 10000)) / 10000.f);
		execMove();
		break;
	default:
		break;
	}
}

void BaseBody::execConsumeCommand()
{
	switch (currAtr) {
	case Interpreter::A_FOOD: {
		BaseBody* checkBody;
		if (checkCollision(system->getSimpleUnit(), getPos(), getRadius() + getBorderRadius(), checkBody, T_FOOD)) {
			checkBody->initDeletion();
			system->getSimpleUnit()->push_back(new WasteBody(getPos().x, getPos().y, system->generateNewId(), system));
			addEnergy(getMaxEnergy() * 0.4);
		}
	}
		break;
	case Interpreter::A_SUN: {
		if (canConsumeSun) {
			if (getRandomNumberRange(0, amountOfFoods)  < 800) {
				addEnergy((getMaxEnergy() - getEnergy()) * 0.4);
				system->getSimpleUnit()->push_back(new FoodBody(getPos().x, getPos().y, system->generateNewId(), system));
			}
			else {
				addEnergy((getMaxEnergy() - getEnergy()) * 0.15);
			}
		}
	}
		break;
	case Interpreter::A_WASTE: {
		BaseBody* checkBody;
		if (checkCollision(system->getSimpleUnit(), getPos(), getRadius(), checkBody, T_WASTE)) {
			checkBody->initDeletion();
			useEnergy(22.f);
		}
	}
		break;
	case Interpreter::A_NEAREST_CORPSE: {
		BaseBody* checkBody;
		if (checkCollision(system->getStaticUnit(), getPos(), getRadius(), checkBody, T_BASE, true)) {
			checkBody->initDeletion();
			addEnergy(40.f);
			for (int i = 0; i < 6; i++) {
				system->getSimpleUnit()->push_back(new FoodBody(getPos().x, getPos().y, system->generateNewId(), system));
			}
			system->getSimpleUnit()->push_back(new WasteBody(getPos().x, getPos().y, system->generateNewId(), system));
			system->getSimpleUnit()->push_back(new WasteBody(getPos().x, getPos().y, system->generateNewId(), system));
		}
	}
		break;
	case Interpreter::A_NEAREST_STATIC: {
		BaseBody* checkBody;
		if (checkCollision(system->getStaticUnit(), getPos(), getRadius(), checkBody, T_BASE)) {
			checkBody->damageBody(20.f);
			addEnergy(20.f);

			system->getSimpleUnit()->push_back(new WasteBody(getPos().x, getPos().y, system->generateNewId(), system));
		}
	}
		break;
	case Interpreter::A_NEAREST_ENEMIE: {
		BaseBody* checkBody;
		if (checkCollision(system->getMovingUnit(), getPos(), getRadius(), checkBody, T_PREDATORCELL)) {
			checkBody->damageBody(52.f);
			addEnergy(getMaxEnergy() - getEnergy() * 0.8);
		}
	}

		break;
	default:
		break;
	}
}

void BaseBody::execRepairCommand()
{
	switch (currAtr) {
	case Interpreter::A_HULL: {
		float healtDiff = maxHealth - health;
		health += healtDiff * 0.4f;
		break;
	}
	default:
		break;
	}
}

void BaseBody::execMoveOutCommand()
{
	switch (currAtr) {
	case Interpreter::A_WASTE: {
		BaseBody* checkBody;
		if (checkCollision(system->getSimpleUnit(), getPos(), getRadius(), checkBody, T_WASTE)) {
			float angle = getRandomNumberRange(0, 360) - 180;

			float radius = this->radius + checkBody->getRadius() + getBorderRadius() + 1.f;

			float x = cos(angle*3.141 / 180.f) * radius;
			float y = sin(angle*3.141 / 180.f) * radius;


			x += getPos().x;
			y += getPos().y;


			checkBody->setPos({ x, y });
		}
		}
		break;
	case Interpreter::A_EGG: {
		BaseBody* checkBody;
		if (checkCollision(system->getSimpleUnit(), getPos(), getRadius(), checkBody, T_EGGBODY)) {
			float angle = getRandomNumberRange(0, 360) - 180;

			float radius = this->radius + checkBody->getRadius() + getBorderRadius() + 1.f;

			float x = cos(angle*3.141 / 180.f) * radius;
			float y = sin(angle*3.141 / 180.f) * radius;


			x += getPos().x;
			y += getPos().y;


			checkBody->setPos({ x, y });
		}
	}
	default:
		break;
	}

}

void BaseBody::execMoveInCommand()
{
	if (hasOuterRing == false) {
		return;
	}

	static int moveOoutCOunt = 0;
	moveOoutCOunt++;

	switch (currAtr) {
	case Interpreter::A_WASTE: {
		float outRadius = getOuterRadius();
		BaseBody* checkBody;
		if (checkCollisionOuterRing(system->getSimpleUnit(), getPos(), radius, outerRadius, checkBody, T_WASTE)) {
			checkBody->setPos(getPos());
		}
	}
		break;
	case Interpreter::A_FOOD: {
		float outRadius = getOuterRadius();
		BaseBody* checkBody;
		if (checkCollisionOuterRing(system->getSimpleUnit(), getPos(), radius, outerRadius, checkBody, T_FOOD)) {
			checkBody->setPos(getPos());
		}
	}
		break;
	default:
		break;
	}
}

void BaseBody::execReplicateCommand()
{
	if (getMaxEnergy() * 0.7 > getEnergy()) {
		return;
	}

	int randChanche = getRandomNumberRange(0, 10);
	if (randChanche != 2) {
		return;
	}


	switch (currAtr) {
	case Interpreter::A_EGG: {
		EggBody* egg = new EggBody(getPos().x, getPos().y, system->generateNewId(), system, this, getBodyType());
		system->getSimpleUnit()->push_back(egg); 
		useEnergy(getMaxEnergy() * 0.6);
	}
		break;
	default:
		break;
	}
}

void BaseBody::execWritePos()
{
	BaseBody* currNearest = nullptr;
	float distance = 1000000;

	switch (currAtr) {
	case Interpreter::A_NEAREST_CORPSE: {

		for (int i = 0; i < system->getStaticUnit()->size(); i++) {
			if (system->getStaticUnit()->at(i)->getEnergy() <= 0) {
				if (getRandomNumberRange(0, 3) == 2) {
					continue;
				}

				BaseBody* compareUnit = system->getStaticUnit()->at(i);
				sf::Vector2f dist = { abs(compareUnit->getPos().x - getPos().x), abs(compareUnit->getPos().y - getPos().y) };
				float currDistance = sqrt(dist.x * dist.x + dist.y * dist.y);
				if (currDistance < distance) {
					distance = currDistance;
					currNearest = system->getStaticUnit()->at(i);
					this->getInterpreter().writeVarPos(system->getStaticUnit()->at(i)->getPos());
				}
			}
		}
		if (currNearest == nullptr) {
			sf::Vector2f currPos = getPos();
			getInterpreter().writeVarPos(currPos);
		}
	}
		break;
	case Interpreter::A_NEAREST_STATIC: {
		for (int i = 0; i < system->getStaticUnit()->size(); i++) {

			if (getRandomNumberRange(0, 3) == 2) {
				continue;
			}

			BaseBody* compareUnit = system->getStaticUnit()->at(i);
			sf::Vector2f dist = { abs(compareUnit->getPos().x - getPos().x), abs(compareUnit->getPos().y - getPos().y) };
			float currDistance = sqrt(dist.x * dist.x + dist.y * dist.y);
			if (currDistance < distance) {
				distance = currDistance;
				currNearest = system->getStaticUnit()->at(i);
				this->getInterpreter().writeVarPos(system->getStaticUnit()->at(i)->getPos());
			}
			
		}
		if (currNearest == nullptr) {
			sf::Vector2f currPos = getPos();
			getInterpreter().writeVarPos(currPos);
		}
	}
		break;
	case Interpreter::A_NEAREST_ENEMIE: {
		
		
		sf::Vector2f enemiePos = Interpreter::readVarEnemiePos(enemieId);

		if (enemiePos == sf::Vector2f(-10000, -10000)) {
			sf::Vector2f currPos = getPos();
			getInterpreter().writeVarPos(currPos);
			break;
		}
		getInterpreter().writeVarPos(enemiePos);
		break;

	}
		break;

	default:
		break;
	}

}

void BaseBody::execMove()
{
	switch (currAtr) {
	case Interpreter::A_POS:
		if (abs(getPos().x - inter.getVarPos().x) < 1.f && abs(getPos().y - inter.getVarPos().y) < 1.f) {
			break;
		}

		inter.startTask(Interpreter::TK_MOVE_POS);
		break;
	default:
		break;
	}
}
