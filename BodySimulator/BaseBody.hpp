#pragma once
#include <SFML\Graphics.hpp>
#include "System.hpp"
#include "Interpreter.hpp"

class System;
class BaseBody
{
	bool deleteThisBody = false;
	unsigned long long id = 0;

public:

	static int amountOfFoods;
	static int amountOfWastes;
	static int amountOfCells;
	static int amountOfFoodCells;
	static int amountOfEggBodies;
	static int amountOfWasteCells;
	static int amountOfHarvesterCells;
	static int amountOfPredators;
	static int amountOfSearchers;
	static int amountOfDefenderCells;

	enum Type {
		T_BASE,
		T_FOOD,
		T_WASTE,
		T_CELL,
		T_FOODCELL,
		T_EGGBODY,
		T_WASTECELL,
		T_HARVESTERCELL,
		T_PREDATORCELL,
		T_SEARCHER,
		T_DEFENDERCELL
	};

protected:
	System* system;
	sf::Vector2f pos;
	sf::Vector2f moveDirection;
	float radius = 0;
	float radiusBorder = 0;
	float outerRadius = 0;
	float health = 1;
	float maxHealth = 1;
	float energy = 1;
	float maxEnergy = 1;
	int xChunk = 0;
	int yChunk = 0;
	float damageCooldown = 1.f;
	unsigned long long enemieId = 0;
	bool canConsumeSun = false;
	bool hasOuterRing = false;
	bool thisBodyHostile = false;
	Type type;
	std::string name;
	Interpreter inter;
	Interpreter::Cmd currCmd = Interpreter::C_EMPTY;
	Interpreter::Atr currAtr = Interpreter::A_EMPTY;


public:
	void init(float x, float y, unsigned long long id, Type type);
	virtual ~BaseBody() {};
	void checkBoundries();
	bool checkChunk(int xChunk1, int xChunk2, int yChunk1, int yChunk2);
	void initDeletion();
	bool readyForDeletion() { return deleteThisBody; };
	bool checkCollisionWithStatic(sf::Vector2f& direction, BaseBody*& collidedBody, float radius = -1);
	bool checkCollision(std::vector<BaseBody*>* bodies, sf::Vector2f pos, float radius, BaseBody*& collidedObject, Type checkType = T_BASE, bool checkOnlyEnergyless = false);
	bool checkCollisionOuterRing(std::vector<BaseBody*>* bodies, sf::Vector2f pos, float radius, float outerRadius, BaseBody*& collidedObject, Type checkType = T_BASE);
	void damageBody(float amount);
	bool isHostile() { return thisBodyHostile; }
	bool isStaticUnit();

	sf::Vector2f getMoveDirection() { return moveDirection; }
	float getHealth() { return health; }
	float getMaxHealth() { return maxHealth; }
	float getEnergy() { return energy; }
	float getMaxEnergy() { return maxEnergy; }
	void useEnergy(float amount) { this->energy -= amount; }
	void addEnergy(float amount);
	int getXChunk() { return xChunk; }
	int getYChunk() { return yChunk; }
	void setChunk(int xChunk, int yChunk) { this->xChunk = xChunk; this->yChunk = yChunk; }

	std::string getName() { return name; }
	sf::Vector2f getPos() { return pos; }
	void setPos(sf::Vector2f pos) { this->pos = pos; }
	float getRadius() { return radius; }
	float getBorderRadius() { return radiusBorder; }
	float getOuterRadius() { return outerRadius; }
	unsigned long long getId() { return id; }
	Type getBodyType() { return type; }
	Interpreter& getInterpreter() { return inter; }

	void executeTask();

	const std::vector<Interpreter::Cmd>& getCmdArr() { return inter.getCmdArr(); }
	const std::vector<Interpreter::Atr>& getAtrArr() { return inter.getAtrArr(); }
	int getCurrentInterIndex() { return inter.getCurrentIndex(); }
	void execCommandChain();
	void execConsumeCommand();
	void execRepairCommand();
	void execMoveOutCommand();
	void execMoveInCommand();
	void execReplicateCommand();
	void execWritePos();
	void execMove();

	virtual void setEnergylessState() {};

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow* win) = 0;
	virtual void postDamaged() {};
};

class FoodBody;