#include "FoodCell.hpp"
#include "GetDefaultInterArrs.hpp"


FoodCell::FoodCell(float x, float y, unsigned long long id, System * system)
{
	this->system = system;
	init(x, y, id, T_FOODCELL);
	radius = 60;
	radiusBorder = 1;
	health = 100.f;
	maxHealth = 100.f;
	energy = 100.f;
	maxEnergy = 100.f;
	body.setRadius(radius * 0.4);
	body.setOutlineThickness(radiusBorder);
	body.setOutlineColor(sf::Color::Green);
	body.setFillColor(sf::Color(sf::Color::Green.r, sf::Color::Green.g, sf::Color::Green.b, 64));
	body.setPosition(x, y);
	body.setOrigin(radius * 0.4, radius * 0.4);
	name = "Food Cell";
	inter = getDefaultInters(T_FOODCELL);
	canConsumeSun = true;

	for (int i = 0; i < leafCount; i++) {
		
		float angle = 360 / leafCount * i;

		float xBL = getPos().x + cos((angle - 15) * 3.141 / 180.f) * getRadius() * 0.5f;
		float yBL = getPos().y + sin((angle - 15) * 3.141 / 180.f) * getRadius() * 0.5f;

		float xBR = getPos().x + cos((angle + 15) * 3.141 / 180.f) * getRadius() * 0.5f;
		float yBR = getPos().y + sin((angle + 15) * 3.141 / 180.f) * getRadius() * 0.5f;

		float xML = getPos().x + cos((angle - 25) * 3.141 / 180.f) * getRadius();
		float yML = getPos().y + sin((angle - 25) * 3.141 / 180.f) * getRadius();

		float xMR = getPos().x + cos((angle + 25) * 3.141 / 180.f) * getRadius();
		float yMR = getPos().y + sin((angle + 25) * 3.141 / 180.f) * getRadius();

		float xTL = getPos().x + cos((angle - 10) * 3.141 / 180.f) * getRadius() * 1.5f;
		float yTL = getPos().y + sin((angle - 10) * 3.141 / 180.f) * getRadius() * 1.5f;

		float xTR = getPos().x + cos((angle + 10) * 3.141 / 180.f) * getRadius() * 1.5f;
		float yTR = getPos().y + sin((angle + 10) * 3.141 / 180.f) * getRadius() * 1.5f;


		leafs[i].setPointCount(6);

		leafs[i].setPoint(0, { xBL, yBL});
		leafs[i].setPoint(1, { xML, yML });
		leafs[i].setPoint(2, { xTL, yTL });
		leafs[i].setPoint(3, { xTR, yTR });
		leafs[i].setPoint(4, { xMR, yMR });
		leafs[i].setPoint(5, { xBR, yBR });

		leafs[i].setFillColor(sf::Color(34, 139, 34, 64));
		leafs[i].setOutlineColor(sf::Color::Green);
		leafs[i].setOutlineThickness(1);

	}
	setChunk(getPos().x / 50, getPos().y / 50);
}

void FoodCell::healthDegneration()
{
	if (health <= 0) {
		initDeletion();
	}
}

void FoodCell::update()
{
	healthDegneration();

	if (energy > 0) {
		inter.update();
	}
	else {
		inter.stopCycle();


		if (boolGreyState == false) {
			boolGreyState = true;
			body.setFillColor({ 128, 128, 128, 64 });
			body.setOutlineColor({ 128, 128, 128, 255 });
			for (int i = 0; i < leafCount; i++) {
				leafs[i].setFillColor({ 128, 128, 128, 64 });
				leafs[i].setOutlineColor({ 128, 128, 128, 255 });
			}
		}


	}


	execCommandChain();
}

void FoodCell::postDamaged()
{
	body.setOutlineThickness(radiusBorder * health / maxHealth);
}

void FoodCell::draw(sf::RenderWindow * win)
{
	win->draw(body);
	for (int i = 0; i < leafCount; i++) {
		win->draw(leafs[i]);
	}

}
