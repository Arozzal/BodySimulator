#include "Gui.hpp"
#include "BaseBody.hpp"
#include <iostream>

Gui::Gui(sf::RenderWindow* window, sf::Font* font)
{
	this->window = window;
	this->font = font;
	backgroundSquare.setFillColor(sf::Color(127, 127, 127));
	nameAndId.setFont(*font);
	nameAndId.setCharacterSize(18);
	nameAndId.setPosition(borderOffsetX, 10);
	
	
	arrowTex.loadFromFile("arrow.png");
	arrowSprLeft.setTexture(arrowTex);
	arrowSprRight.setTexture(arrowTex);
	arrowSprRight.setScale(-1, 1);

	barHealth = new Bar(borderOffsetX, 10.0f, 400.0f, 50.0f, 75, 100, sf::Color(128, 0, 128), font);
	barEnergy = new Bar(borderOffsetX, 50.0f, 400.0f, 50.0f, 75, 100, sf::Color(204, 204, 0), font);

	populationTemplateStrings[0] = ("Foods: ");
	populationTemplateStrings[1] = ("Wastes: ");
	populationTemplateStrings[2] = ("Eggs: ");
	populationTemplateStrings[3] = ("Cells: ");
	populationTemplateStrings[4] = ("Plants: ");
	populationTemplateStrings[5] = ("Garbager: ");
	populationTemplateStrings[6] = ("Harvesters: ");


	for (int i = 0; i < amountOfPopulationTexts; i++) {
		populationTexts[i].setFont(*font);
		populationTexts[i].setCharacterSize(18);
		populationTexts[i].setString("sfjalsefga");
		populationTexts[i].setPosition(posx + borderOffsetX, 200 - borderOffsetX - (i + 20));
	}

	cmds.resize(20);

	for (int i = 0; i < 20; i++) {
		cmds[i] = new DoubleCommand(100.0f, 100.0f, 200.0f, 35.0f, Interpreter::Cmd::C_EMPTY, Interpreter::Atr::A_EMPTY, font);
	}

	commandSelectMenu = new CommandSelectMenu(100.0f, 100.0f, 250.0f, 400.0f, sf::Color(127, 127, 127), font);
	commandSelectMenu->setCmdMode(true);
}

bool Gui::isMouseOverAnElement()
{
	if (visible) {
		if (commandSelectMenu->isMouseOver()) {
			return true;
		}
		sf::Vector2i msPos = sf::Mouse::getPosition(*window);
		if (float(msPos.x) / float(window->getSize().x) > 0.7) {
			return true;
		}
	
	}

	return false;
}

void Gui::hide()
{
	visible = false; 
	selectedBody = nullptr;
}

void Gui::clearSelection()
{
	for (int i = 0; i < cmds.size(); i++) {
		cmds[i]->getCmd()->setSelected(false);
		cmds[i]->getAtr()->setSelected(false);
	}
	selectedCommand = nullptr;
}

void Gui::updateSize(int sizeX, int sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	backgroundSquare.setSize(sf::Vector2f(sizeX, sizeY));
}

void Gui::updatePos(int posx, int posy)
{
	this->posx = posx;
	this->posy = posy;
	backgroundSquare.setPosition(posx, posy);
	commandSelectMenu->setPosition(posx - commandSelectMenu->getWidth(), posy);
}

void Gui::updateBody(BaseBody * body)
{
	this->selectedBody = body;

	nameAndId.setString(sf::String(body->getName()) + "#" + std::to_string(body->getId()));
	nameAndId.setPosition(int(posx + sizeX / 2 - nameAndId.getLocalBounds().width / 2), borderOffsetX);
	amountOfCmds = body->getCmdArr().size();
}

void Gui::update()
{
	if (selectedBody == nullptr)
		return;

	if (visible == false)
		return;

	this->hp = selectedBody->getHealth();
	this->hpMax = selectedBody->getMaxHealth();
	this->energy = selectedBody->getEnergy();
	this->energyMax = selectedBody->getMaxEnergy();

	if (energy < 0)
		energy = 0;

	nameAndId.setString(sf::String(selectedBody->getName()) + "#" + std::to_string(selectedBody->getId()));
	nameAndId.setPosition(int(posx + sizeX / 2 - nameAndId.getLocalBounds().width / 2), borderOffsetX);

	barHealth->setPosition(posx + borderOffsetX, 50);
	barHealth->setSize(sizeX - 2 * borderOffsetX, 40.f);
	barHealth->setAmount(hp, hpMax);
	

	int rectEnergyYPos = barHealth->getY() + barHealth->getHeight() + borderOffsetX;


	barEnergy->setPosition(posx + borderOffsetX, rectEnergyYPos);
	barEnergy->setSize(sizeX - 2 * borderOffsetX, 40.f);
	barEnergy->setAmount(energy, energyMax);

	int cmdFirstPosY = barEnergy->getY() + barEnergy->getHeight() + borderOffsetX;

	for (int i = 0; i < amountOfCmds; i++) {
		cmds[i]->setCommand(selectedBody->getCmdArr()[i]);
		cmds[i]->setAttribute(selectedBody->getAtrArr()[i]);
		cmds[i]->setPosition(posx + cmdOffsetX, cmdFirstPosY + i * 40);
		cmds[i]->setSize(sizeX - (cmdOffsetX * 2), 35.0f);
		if (cmds[i]->isMouseReleased()) {
			std::cout << cmds[i]->getY() << std::endl;
		}
	}


	if (amountOfCmds > 0) {
		arrowSprLeft.setPosition(posx + cmdOffsetX - arrowSprLeft.getGlobalBounds().width, cmdFirstPosY + selectedBody->getCurrentInterIndex() * 40);
		arrowSprRight.setPosition(cmds[0]->getX() + cmds[0]->getWidth() + arrowSprRight.getGlobalBounds().width, cmdFirstPosY + selectedBody->getCurrentInterIndex() * 40);
	}

	populationAmountStrings[0] = BaseBody::amountOfFoods;
	populationAmountStrings[1] = BaseBody::amountOfWastes;
	populationAmountStrings[2] = BaseBody::amountOfEggBodies;
	populationAmountStrings[3] = BaseBody::amountOfCells;
	populationAmountStrings[4] = BaseBody::amountOfFoodCells;
	populationAmountStrings[5] = BaseBody::amountOfWasteCells;
	populationAmountStrings[6] = BaseBody::amountOfHarvesterCells;

	for (int i = 0; i < cmds.size(); i++) {
		if (cmds[i]->getCmd()->isMouseReleased()) {
			clearSelection();

			cmds[i]->getCmd()->setSelected(true);
			selectedCommand = cmds[i]->getCmd();
			commandSelectMenu->setCmdMode(true);
			selectedCommandIndex = i;
			break;
		}

		if (cmds[i]->getAtr()->isMouseReleased()) {
			clearSelection();

			cmds[i]->getAtr()->setSelected(true);
			selectedCommand = cmds[i]->getAtr();
			commandSelectMenu->setCmdMode(false);
			selectedCommandIndex = i;
			break;
		}
	}


	for (int i = 0; i < amountOfPopulationTexts; i++) {
		populationTexts[i].setString(populationTemplateStrings[i] + std::to_string(populationAmountStrings[i]));
		populationTexts[i].setPosition(posx + borderOffsetX, sizeY - borderOffsetX - ((i + 1) * 20));
	}

	if (commandSelectMenu->isMouseOver()) {
		if (commandSelectMenu->IsInCmdMode() && commandSelectMenu->getClickedCmd() != Interpreter::Cmd::C_NONE) {
			selectedBody->getInterpreter().overrideCmd(commandSelectMenu->getClickedCmd(), selectedCommandIndex);

		}
		if (commandSelectMenu->IsInCmdMode() == false && commandSelectMenu->getClickedAtr() != Interpreter::Atr::A_NONE) {
			selectedBody->getInterpreter().overrideAtr(commandSelectMenu->getClickedAtr(), selectedCommandIndex);
		}
	}
}

void Gui::draw()
{
	if (visible == false) {
		return;
	}

	if (selectedBody == nullptr)
		return;

	window->draw(backgroundSquare);
	window->draw(nameAndId);

	for (int i = 0; i < amountOfCmds; i++) {
		cmds[i]->draw(window);
	}


	for (int i = 0; i < amountOfPopulationTexts; i++) {
		window->draw(populationTexts[i]);
	}

	window->draw(arrowSprLeft);
	window->draw(arrowSprRight);
	barEnergy->draw(window);
	barHealth->draw(window);
	commandSelectMenu->draw(window);
}


Gui::~Gui()
{
	delete barHealth;
	delete barEnergy;
}
