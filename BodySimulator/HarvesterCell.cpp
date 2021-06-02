#include "HarvesterCell.hpp"
#include "GetDefaultInterArrs.hpp"

HarvesterCell::HarvesterCell(float x, float y, unsigned long long id, System * system)
{
	this->system = system;
	init(x, y, id, T_HARVESTERCELL);
	radius = 40;
	radiusBorder = 10;
	health = 100.f;
	maxHealth = 100.f;
	energy = 250.f;
	maxEnergy = 250.f;
	body.setRadius(radius);
	body.setOutlineThickness(radiusBorder);
	body.setOutlineColor(sf::Color::Blue);
	body.setFillColor(sf::Color(20, 20, 255, 128));
	body.setPosition(x, y);
	body.setOrigin(radius, radius);
	name = "Harvester Cell";
	inter = getDefaultInters(T_HARVESTERCELL);
	setChunk(getPos().x / 50, getPos().y / 50);

	for (int i = 0; i < 5; i++) {
		tail[i].setRadius(radius / (2 + i) + 8);
		tail[i].setOrigin(tail[i].getRadius(), tail[i].getRadius());
		tail[i].setPosition(getPos().x, getPos().y + radius * (i +  2) * 2);
		tail[i].setOutlineColor(sf::Color::Blue);
		tail[i].setFillColor(sf::Color(20, 20, 255, 128));
		tail[i].setOutlineThickness(3);
	}
}

void HarvesterCell::healthDegneration()
{

	if (health <= 0) {
		initDeletion();
	}
}

void HarvesterCell::update()
{
	
	healthDegneration();
	body.setPosition(getPos());
	sf::Vector2f diff = body.getPosition() - tail[0].getPosition();
	if (sqrt(diff.x * diff.x + diff.y * diff.y) > tail[0].getRadius() + body.getRadius() + body.getOutlineThickness()) {
		tail[0].move(diff.x * 2.5 * system->getElapsedTime(), diff.y * 2.5 * system->getElapsedTime());
	}

	
	for (int i = 1; i < 5; i++) {
		sf::Vector2f diff = tail[i - 1].getPosition() - tail[i].getPosition();
		if (sqrt(diff.x * diff.x + diff.y * diff.y) < tail[i].getRadius() + tail[i - 1].getRadius()) {
			continue;
		}

		tail[i].move(diff.x * system->getElapsedTime() * 2.5, diff.y * system->getElapsedTime() * 2.5);
	}

	
	if (energy > 0) {
		inter.update();
	}
	else {
		inter.stopCycle();

		if (boolGreyState == false) {
			boolGreyState = true;
			body.setFillColor({ 128, 128, 128, 64 });
			body.setOutlineColor({ 128, 128, 128, 255 });
		}
	}

	execCommandChain();
	executeTask();
	checkBoundries();
}

void HarvesterCell::postDamaged()
{
	body.setOutlineThickness(radiusBorder * health / maxHealth);
}

void HarvesterCell::draw(sf::RenderWindow * win)
{
	win->draw(body);
	for (int i = 0; i < 5; i++) {
		win->draw(tail[i]);
	}
}
