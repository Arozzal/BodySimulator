#include "Interpreter.hpp"
#include "extendedMath.hpp"
#include <iostream>

static std::string cmdStringTemp[] = { "EMPTY", "CONSUME", "MOVE OUT", "REPAIR", "MOVE IN", "REPLICATE", "WRITE(POS)", "MOVE" };
const std::string* Interpreter::cmdStringArr = cmdStringTemp;

static std::string atrStringTemp[] = { "EMPTY", "FOOD", "WASTE", "HULL", "SUN", "EGG", "#CORPSE", "(POS)", "#HERBEVOUR", "$ENEMIES" };
const std::string* Interpreter::atrStringArr = atrStringTemp;

static sf::Color tempCmdColor[] = { sf::Color::Black,  {191, 255, 0}, {255, 10, 10}, {10, 50, 255}, {20, 20, 255}, {255, 165, 79}, {025, 025, 112 }, {85, 026, 139} };
const sf::Color* Interpreter::cmdColor = tempCmdColor;

static sf::Color tempAtrColor[] = { sf::Color::Black,  {150, 75, 0}, {220, 220, 220}, {255, 100, 100}, {245, 255, 0}, {0, 238, 118}, {139, 69, 19}, {025, 025, 112}, {0, 255, 50}, sf::Color::Red };
const sf::Color* Interpreter::atrColor = tempAtrColor;

std::map<unsigned long long, sf::Vector2f> Interpreter::enemiePoses;

void Interpreter::pushCmd(Cmd cmd, Atr atr)
{
	cmds.push_back(cmd);
	atrs.push_back(atr);
}

void Interpreter::insertCmd(Cmd cmd, Atr atr, int index)
{
	if (index < 0) {
		return;
	}

	if (index >= cmds.size()) {
		return;
	}

	cmds.insert(cmds.begin() + index, cmd);
	atrs.insert(atrs.begin() + index, atr);
}

void Interpreter::removeCmd(int index)
{
	cmds.erase(cmds.begin() + index);
	atrs.erase(atrs.begin() + index);
}

void Interpreter::overrideCmd(Cmd cmd, int index)
{
	cmds[index] = cmd;
}

void Interpreter::overrideAtr(Atr atr, int index)
{
	atrs[index] = atr;
}

void Interpreter::update()
{
	if (isMachineOne == false) {
		return;
	}

	if (isTaskActive)
		return;

	counter += clock.getElapsedTime().asSeconds();
	clock.restart();
	if (counter >= elapseAmount) {
		isCommandExecuted = false;
		isAttributeExecuted = false;
		counter = 0;
		currIndex++;
		if (currIndex >= cmds.size()) {
			currIndex = 0;
		}
	}
}

void Interpreter::writeVarPos(sf::Vector2f varPos)
{
	this->varPos = varPos;
}

Interpreter::Cmd Interpreter::getCurrentCmd()
{
	if (isCommandExecuted == false) {
		isCommandExecuted = true;
		return cmds[currIndex];
	}
	else {
		return C_EMPTY;
	}
	
}

Interpreter::Atr Interpreter::getCurrentAtr()
{
	if (isAttributeExecuted == false) {
		isAttributeExecuted = true;
		return atrs[currIndex];
	}
	else {
		return A_EMPTY;
	}

	
}

void Interpreter::writeVarEnemiePos(unsigned long long id, sf::Vector2f pos)
{
	if (enemiePoses.find(id) != enemiePoses.end()) {
		enemiePoses[id] = pos;
	}


	enemiePoses.insert({ id, pos });
}

sf::Vector2f Interpreter::readVarEnemiePos(unsigned long long& id)
{
	if (enemiePoses.size() == 0) {
		return { -10000, -10000 };
	}

	int amountOfSkips = getRandomNumberRange(0, enemiePoses.size());

	if (amountOfSkips > 0)
		amountOfSkips--;

	if (enemiePoses.find(id) == enemiePoses.end()) {
		id = 0;
	}

	if (id == 0) {
		for (auto const& it : enemiePoses) {
			if (amountOfSkips > 0) {
				amountOfSkips--;
				continue;
			}

			id = it.first;
			return it.second;
		}
	}
	
	

	return enemiePoses.at(id);
}

void Interpreter::deleteVarEnemiePos(unsigned long long id)
{
	enemiePoses.erase(id);
}

Interpreter::Interpreter()
{
	clock.restart();
	elapseAmount = 0.9f + float(getRandomNumberRange(1, 100)) / 400.f;
}


Interpreter::~Interpreter()
{
	
}
