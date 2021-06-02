#include "PredatorCell.hpp"
#include "GetDefaultInterArrs.hpp"

PredatorCell::PredatorCell(float x, float y, unsigned long long id, System * system)
{
	this->system = system;
	init(x, y, id, T_PREDATORCELL);
	radius = 70;
	radiusBorder = 10;
	health = 100.f;
	maxHealth = 100.f;
	energy = 250.f;
	maxEnergy = 250.f;
	body.setRadius(radius);
	body.setOutlineThickness(radiusBorder);
	body.setOutlineColor(sf::Color::Red);
	body.setFillColor(sf::Color(153, 0, 0, 128));
	body.setPosition(x, y);
	body.setOrigin(radius, radius);
	name = "Predator Cell";
	inter = getDefaultInters(T_PREDATORCELL);
	setChunk(getPos().x / 50, getPos().y / 50);
	thisBodyHostile = true;

	for (int i = 0; i < 10; i++) {
		tail[i].setRadius(radius / (4 + i));
		tail[i].setOrigin(tail[i].getRadius(), tail[i].getRadius());
		tail[i].setPosition(getPos().x, getPos().y + radius * (i + 2) * 2);
		tail[i].setOutlineColor(sf::Color::Red);
		tail[i].setFillColor(sf::Color(140, 10, 10, 128));
		tail[i].setOutlineThickness(3);
	}

	for (int i = 0; i < 6; i++) {
		float angle = 360 / 6 * i;
		spikes[i].setRadius(25);
		spikes[i].setOrigin(spikes[i].getRadius(), spikes[i].getRadius());
		spikes[i].setFillColor(sf::Color(140, 10, 10, 128));
		spikes[i].setOutlineThickness(2);
		spikes[i].setOutlineColor(sf::Color::Red);
		
		float posX = cos(angle * 3.141 / 180.f) * (radius + spikes[i].getRadius() + body.getOutlineThickness() + spikes[i].getOutlineThickness());
		float posY = sin(angle * 3.141 / 180.f) * (radius + spikes[i].getRadius() + body.getOutlineThickness() + spikes[i].getOutlineThickness());
		spikePoses[i] = {posX, posY};
		spikes[i].setPosition(getPos().x + posX,getPos().y + posY);
	}

}

void PredatorCell::healthDegneration()
{

	if (health <= 0) {
		initDeletion();
	}
}

void PredatorCell::update()
{

	healthDegneration();
	body.setPosition(getPos());
	sf::Vector2f diff = body.getPosition() - tail[0].getPosition();
	if (sqrt(diff.x * diff.x + diff.y * diff.y) > tail[0].getRadius() + body.getRadius() + body.getOutlineThickness()) {
		tail[0].move(diff.x * 2.5 * system->getElapsedTime(), diff.y * 2.5 * system->getElapsedTime());
	}


	for (int i = 1; i < 10; i++) {
		sf::Vector2f diff = tail[i - 1].getPosition() - tail[i].getPosition();
		if (sqrt(diff.x * diff.x + diff.y * diff.y) < tail[i].getRadius() + tail[i - 1].getRadius()) {
			continue;
		}

		tail[i].move(diff.x * system->getElapsedTime() * 2.5, diff.y * system->getElapsedTime() * 2.5);
	}
	
	for (int i = 0; i < 6; i++) {
		spikes[i].setPosition(spikePoses[i] + getPos());
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

void PredatorCell::postDamaged()
{
	body.setOutlineThickness(radiusBorder * health / maxHealth);
}

void PredatorCell::draw(sf::RenderWindow * win)
{
	win->draw(body);
	for (int i = 0; i < 10; i++) {
		win->draw(tail[i]);
	}

	for (int i = 0; i < 6; i++) {
		win->draw(spikes[i]);
	}
}
