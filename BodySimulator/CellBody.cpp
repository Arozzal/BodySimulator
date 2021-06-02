#include "CellBody.hpp"
#include "GetDefaultInterArrs.hpp"



CellBody::CellBody(float x, float y, unsigned long long id, System * system)
{
	this->system = system;
	init(x, y, id, T_CELL);
	radius = 40;
	radiusBorder = 10;
	health = 100.f;
	maxHealth = 100.f;
	energy = 250.f;
	maxEnergy = 250.f;
	body.setRadius(radius);
	body.setOutlineThickness(radiusBorder);
	body.setOutlineColor(sf::Color::Magenta);
	body.setFillColor(sf::Color(sf::Color::Magenta.r, sf::Color::Magenta.g, sf::Color::Magenta.b, 64));
	body.setPosition(x, y);
	body.setOrigin(radius, radius);
	name = "Cell";
	inter = getDefaultInters(T_CELL);
	setChunk(getPos().x / 50, getPos().y / 50);
}

void CellBody::healthDegneration()
{

	if (health <= 0) {
		initDeletion();
	}
}

void CellBody::update()
{
	
	healthDegneration();

	if (energy > 0){
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
}

void CellBody::postDamaged()
{
	body.setOutlineThickness(radiusBorder * health / maxHealth);
}

void CellBody::draw(sf::RenderWindow * win)
{
	win->draw(body);
}
