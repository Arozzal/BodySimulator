#include "DefenderCell.hpp"
#include "GetDefaultInterArrs.hpp"


DefenderCell::DefenderCell(float x, float y, unsigned long long id, System * system)
{
	this->system = system;
	init(x, y, id, T_DEFENDERCELL);
	radius = 40;
	radiusBorder = 10;
	health = 100.f;
	maxHealth = 100.f;
	energy = 1000.f;
	maxEnergy = 1000.f;
	body.setRadius(radius);
	body.setOutlineThickness(radiusBorder);
	body.setOutlineColor(sf::Color(25, 25, 112, 255));
	body.setFillColor(sf::Color(25, 25, 112, 128));
	body.setPosition(x, y);
	body.setOrigin(radius, radius);
	name = "Defender Cell";
	inter = getDefaultInters(T_DEFENDERCELL);
	setChunk(getPos().x / 50, getPos().y / 50);

	for (int i = 0; i < 5; i++) {
		float angle = 360 / 5 * i;
		spikes[i].setRadius(25);
		spikes[i].setPointCount(3);
		spikes[i].setRotation(angle + 30);
		spikes[i].setOrigin(spikes[i].getRadius(), spikes[i].getRadius());
		spikes[i].setFillColor(sf::Color(25, 25, 112, 128));
		spikes[i].setOutlineThickness(2);
		spikes[i].setOutlineColor(sf::Color(25, 25, 112, 255));

		float posX = cos(angle * 3.141 / 180.f) * (radius + spikes[i].getRadius() + body.getOutlineThickness() + spikes[i].getOutlineThickness());
		float posY = sin(angle * 3.141 / 180.f) * (radius + spikes[i].getRadius() + body.getOutlineThickness() + spikes[i].getOutlineThickness());
		spikePoses[i] = { posX, posY };
		spikes[i].setPosition(getPos().x + posX, getPos().y + posY);
	}
}

void DefenderCell::healthDegneration()
{

	if (health <= 0) {
		initDeletion();
	}
}

void DefenderCell::update()
{

	healthDegneration();
	body.setPosition(getPos());

	if (currCmd == Interpreter::C_CONSUME) {
		isRotating = true;
	}
	else if(currCmd != Interpreter::C_CONSUME && currCmd != Interpreter::C_EMPTY){
		isRotating = false;
	}
	
	

	if (isRotating) {
		for (int i = 0; i < 5; i++) {
			float angle = 360 / 5 * i;
			rotOffset += system->getElapsedTime() * 60.f;
			spikes[i].setRotation(angle + 30 + rotOffset);
			float posX = cos((angle + rotOffset) * 3.141 / 180.f) * (radius + spikes[i].getRadius() + body.getOutlineThickness() + spikes[i].getOutlineThickness());
			float posY = sin((angle + rotOffset) * 3.141 / 180.f) * (radius + spikes[i].getRadius() + body.getOutlineThickness() + spikes[i].getOutlineThickness());
			spikePoses[i] = { posX, posY };
		}
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
			for (int i = 0; i < 5; i++) {
				spikes[i].setFillColor(sf::Color(128, 128, 128, 128));
				spikes[i].setOutlineColor(sf::Color(128, 128, 128, 255));
				isRotating = false;
			}
		}
	}

	execCommandChain();
	executeTask();
	checkBoundries();
}

void DefenderCell::postDamaged()
{
	body.setOutlineThickness(radiusBorder * health / maxHealth);
}

void DefenderCell::draw(sf::RenderWindow * win)
{
	win->draw(body);

	for (int i = 0; i < 6; i++) {
		win->draw(spikes[i]);
	}
}
