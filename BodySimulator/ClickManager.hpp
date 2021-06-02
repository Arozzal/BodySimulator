#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

class BaseBody;
class ClickManager
{
public:
	ClickManager();
	~ClickManager();

	BaseBody* checkBodyList(sf::Vector2f mousePos, std::vector<BaseBody*>* checkList);

};

