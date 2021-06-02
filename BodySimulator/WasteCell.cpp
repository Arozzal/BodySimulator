#include "WasteCell.hpp"
#include "GetDefaultInterArrs.hpp"


WasteCell::WasteCell(float x, float y, unsigned long long id, System * system)
{
	this->system = system;
	init(x, y, id, T_WASTECELL);
	radius = 40;
	radiusBorder = 20;
	health = 200.f;
	maxHealth = 200.f;
	energy = 300.f;
	maxEnergy = 300.f;
	hasOuterRing = true;
	innerBody.setRadius(radius);
	innerBody.setOutlineThickness(radiusBorder);
	innerBody.setOutlineColor(sf::Color(40, 20, 20, 255));
	innerBody.setFillColor(sf::Color(255, 50, 25, 64));
	innerBody.setPosition(x, y);
	innerBody.setOrigin(radius, radius);

	outerRadius = radius * 5.f;
	outerBody.setRadius(outerRadius);
	outerBody.setFillColor(sf::Color(64, 32, 32, 100));
	outerBody.setPosition(x, y);
	outerBody.setOrigin(outerRadius, outerRadius);

	name = "Waste Cell";
	
	inter = getDefaultInters(T_WASTECELL);
	setChunk(getPos().x / 50, getPos().y / 50);
}

void WasteCell::healthDegneration()
{
	if (health <= 0) {
		initDeletion();
	}
}

void WasteCell::update()
{

	healthDegneration();

	if (energy > 0) {
		inter.update();
	}
	else {
		inter.stopCycle();

		if (boolGreyState == false) {
			boolGreyState = true;
			innerBody.setFillColor({ 100, 50, 25, 64 });
			innerBody.setOutlineColor({ 60, 20, 20, 255 });
			outerBody.setFillColor({ 100, 50, 25, 32 });
		}
	}


	execCommandChain();
}

void WasteCell::postDamaged()
{
	innerBody.setOutlineThickness(radiusBorder * health / maxHealth);
}

void WasteCell::draw(sf::RenderWindow * win)
{
	if(energy > 0)
		win->draw(outerBody);
	win->draw(innerBody);
}
