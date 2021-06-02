#include "ClickManager.hpp"
#include "BaseBody.hpp"

ClickManager::ClickManager()
{
}


ClickManager::~ClickManager()
{
}

BaseBody* ClickManager::checkBodyList(sf::Vector2f mousePos, std::vector<BaseBody*>* checkList)
{
	for (int i = 0; i < checkList->size(); i++) {
		sf::Vector2f currPos = checkList->at(i)->getPos();
		float radius = checkList->at(i)->getRadius();

		sf::Vector2f finalised = { abs(mousePos.x - currPos.x), abs(mousePos.y - currPos.y) };
		if (sqrt(finalised.x * finalised.x + finalised.y * finalised.y) <= radius) {
			return checkList->at(i);
		}
	}

	return nullptr;
}
