#pragma once
#include <vector>
#include <SFML\System.hpp>
#include <SFML\Graphics\Color.hpp>
#include <map>

class System;
class Interpreter
{
	

public:
	enum Cmd {
		C_EMPTY,
		C_CONSUME,
		C_MOVEOUT,
		C_REPAIR,
		C_MOVEIN,
		C_REPLICATE,
		C_WRITE_POS,
		C_MOVE,
		C_SIZE,
		C_NONE
	};

	enum Atr {
		A_EMPTY,
		A_FOOD,
		A_WASTE,
		A_HULL,
		A_SUN,
		A_EGG,
		A_NEAREST_CORPSE,
		A_POS,
		A_NEAREST_STATIC,
		A_NEAREST_ENEMIE,
		A_SIZE,
		A_NONE
	};

	enum Task {
		TK_EMPTY,
		TK_MOVE_POS,
	};

	static const std::string* cmdStringArr;
	static const std::string* atrStringArr;
	static const sf::Color* cmdColor;
	static const sf::Color* atrColor;

private:
	std::vector<Cmd> cmds;
	std::vector<Atr> atrs;
	float counter = 0;
	float elapseAmount = 1.f;
	int currIndex = 0;
	sf::Vector2f varPos;

	static std::map<unsigned long long, sf::Vector2f> enemiePoses;

	sf::Clock clock;
	bool isCommandExecuted = false;
	bool isAttributeExecuted = false;
	bool isMachineOne = true;
	bool isTaskActive = false;

	Task currentTask = TK_EMPTY;
public:

	
	int getCmdSize() { return cmds.size(); }
	void pushCmd(Cmd cmd, Atr atr);
	void insertCmd(Cmd cmd, Atr atr, int index);
	void removeCmd(int index);
	void overrideCmd(Cmd cmd, int index);
	void overrideAtr(Atr atr, int index);
	void update();
	void stopCycle() { isMachineOne = false; };
	void startCycle() { isMachineOne = true; };
	void startTask(Task task) { isTaskActive = true; currentTask = task; }
	Task getCurrentTask() { return currentTask; }
	void taskFinnished() { isTaskActive = false; currentTask = TK_EMPTY; }

	void writeVarPos(sf::Vector2f varPos);
	sf::Vector2f getVarPos() { return varPos; }

	Cmd getCurrentCmd();
	Atr getCurrentAtr();
	int getCurrentIndex() { return currIndex; }

	const std::vector<Interpreter::Cmd>& getCmdArr() { return cmds; }
	const std::vector<Interpreter::Atr>& getAtrArr() { return atrs; }
	static const std::string& getCmdString(int index) { return cmdStringArr[index]; }
	static const std::string& getAtrString(int index) { return atrStringArr[index]; }
	static const sf::Color getCmdColor(Cmd cmd) { return cmdColor[cmd]; }
	static const sf::Color getAtrColor(Atr atr) { return atrColor[atr]; }

	static void writeVarEnemiePos(unsigned long long id, sf::Vector2f pos);
	static sf::Vector2f readVarEnemiePos(unsigned long long& id);
	static void deleteVarEnemiePos(unsigned long long id);

	Interpreter();
	~Interpreter();
};

