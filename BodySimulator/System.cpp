#include "System.hpp"

#include <iostream>

#include "FoodBody.hpp"
#include "WasteBody.hpp"
#include "CellBody.hpp"
#include "FoodCell.hpp"
#include "WasteCell.hpp"
#include "HarvesterCell.hpp"
#include "PredatorCell.hpp"
#include "SearchBody.hpp"
#include "DefenderCell.hpp"
#include "ClickManager.hpp"
#include "Gui.hpp"
#include "Game.hpp"

void System::calculateTime()
{
	static float timeFpsCount = 0;
	static int framCount = 0;

	elapsedTime = clock.getElapsedTime().asSeconds();
	if (elapsedTime > 0.3f) {
		std::cout << "Critical Frame " << elapsedTime << std::endl;
		elapsedTime = 0.3f;
	}
		


	timeFpsCount += elapsedTime;
	framCount++;

	if (timeFpsCount >= 1.0f) {
		fps = framCount;
		framCount = 0;
		timeFpsCount = 0;
		fpsText.setString("Fps: " + std::to_string(fps));
	}

	clock.restart();
}

System::System()
{
	winSizeX = 1600;
	winSizeY = 900;
	winScale = 2.f;
	winPosX = -1100;
	winPosY = -1100;
	window = new sf::RenderWindow(sf::VideoMode(winSizeX, winSizeY), "SFML works!");
	initMath();
	font.loadFromFile("font.ttf");
	fpsText.setFont(font);
	fpsText.setCharacterSize(12);
	fpsText.setPosition(10, 10);
	fpsText.setFillColor(sf::Color::White);
	guiView = window->getDefaultView();
	clickManager = new ClickManager();
	gui = new Gui(window, &font);
	Game::getInst().setWindow(window);

	for (int i = 0; i < 100; i++) {
		simpleUnits.push_back(new FoodBody(0, 0, generateNewId(), this));
	}

	for (int i = 0; i < 0; i++) {
		simpleUnits.push_back(new WasteBody(0, 0, generateNewId(), this));
	}

	for (int i = 0; i < 100; i++) {
		staticUnits.push_back(new CellBody(int(getRandomNumberRange(0, 8000 - 800)) - 3900, int(getRandomNumberRange(0, 8000 - 800)) - 3900, generateNewId(), this));
	}

	for (int i = 0; i < 50; i++) {
		staticUnits.push_back(new FoodCell(int(getRandomNumberRange(0, 8000 - 800)) - 3900, int(getRandomNumberRange(0, 8000 - 800)) - 3900, generateNewId(), this));
	}

	for (int i = 0; i < 70; i++) {
		staticUnits.push_back(new WasteCell(int(getRandomNumberRange(0, 8000 - 800)) - 3900, int(getRandomNumberRange(0, 8000 - 800)) - 3900, generateNewId(), this));
	}
	
	for (int i = 0; i < 5; i++) {
		movingUnits.push_back(new HarvesterCell(int(getRandomNumberRange(0, 8000 - 800)) - 3900, int(getRandomNumberRange(0, 8000 - 800)) - 3900, generateNewId(), this));
	}

	for (int i = 0; i < 5; i++) {
		movingUnits.push_back(new PredatorCell(int(getRandomNumberRange(0, 8000 - 800)) - 3900, int(getRandomNumberRange(0, 8000 - 800)) - 3900, generateNewId(), this));
	}

	for (int i = 0; i < 50; i++) {
		simpleUnits.push_back(new SearchBody(int(getRandomNumberRange(0, 8000 - 800)) - 3900, int(getRandomNumberRange(0, 8000 - 800)) - 3900, generateNewId(), this));
	}

	for (int i = 0; i < 5; i++) {
		movingUnits.push_back(new DefenderCell(int(getRandomNumberRange(0, 8000 - 800)) - 3900, int(getRandomNumberRange(0, 8000 - 800)) - 3900, generateNewId(), this));
	}
}

void System::updateInput()
{
	

	sf::Event event;
	while (window->pollEvent(event))
	{

		if (event.type == sf::Event::Closed) {
			window->close();
		}

		if (event.type == sf::Event::Resized) {
			winSizeX = window->getSize().x;
			winSizeY = window->getSize().y;
			guiView.reset({ 0, 0, winSizeX, winSizeY });
		}

		if (event.type == sf::Event::Closed) {
			exit(0);
		}

		if (event.type == sf::Event::MouseWheelMoved && window->hasFocus()) {
			float delta = float(event.mouseWheel.delta) / 10.f;
			if (delta < 0 && winScale < 3.5 || delta > 0 && winScale > 0.1) {
				sf::Vector2i currPos = sf::Mouse::getPosition(*window);
				sf::Vector2f part = { float(currPos.x) / float(winSizeX),  float(currPos.y) / float(winSizeY) };
				winPosX += winSizeX * (delta * part.x);
				winPosY += winSizeY * (delta * part.y);
				winScale -= delta;
			}
		}
	}

	if (window->hasFocus() == false)
		return;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		winPosY -= 1000.f * getElapsedTime();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		winPosY += 1000.f * getElapsedTime();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		winPosX -= 1000.f * getElapsedTime();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		winPosX += 1000.f * getElapsedTime();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		float scaleChange = 0.4f * getElapsedTime();
		winPosX += winSizeX * (scaleChange / 2.f);
		winPosY += winSizeY * (scaleChange / 2.f);
		winScale -= scaleChange;
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		float scaleChange = 0.4f * getElapsedTime();
		winPosX -= winSizeX * (scaleChange / 2.f);
		winPosY -= winSizeY * (scaleChange / 2.f);
		winScale += scaleChange;
	}


	static sf::Vector2i lastMiddlePos;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
		winPosX += (lastMiddlePos.x - sf::Mouse::getPosition(*window).x) * winScale;
		winPosY += (lastMiddlePos.y - sf::Mouse::getPosition(*window).y) * winScale;
	}

	lastMiddlePos = sf::Mouse::getPosition(*window);
	
	


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i msPos = sf::Mouse::getPosition(*window);
		sf::Vector2f worldPos = window->mapPixelToCoords(msPos, view);

		if (gui->isMouseOverAnElement() == false) {
			clickedThing = clickManager->checkBodyList(worldPos, &movingUnits);
			if (clickedThing == nullptr)
				clickedThing = clickManager->checkBodyList(worldPos, &staticUnits);


			if (clickedThing != nullptr) {
				gui->show();
				gui->updateBody(clickedThing);
			}
			else {
				if (float(msPos.x) / float(window->getSize().x) < 0.7)
					gui->hide();
			}
		}
	}

	Game::getInst().update();
}

void System::update()
{
	calculateTime();
	view.reset({ winPosX, winPosY, winSizeX * winScale, winSizeY * winScale });
	gui->updateSize(winSizeX * 0.3, winSizeY);
	gui->updatePos(winSizeX * 0.7, 0);

	static float spawnTimer = 0;
	spawnTimer += getElapsedTime();
	if (spawnTimer >= 1.f) {
		spawnTimer = 0;
		if (getRandomNumberRange(0, 150) == 15) {
			for (int i = 0; i < getRandomNumberRange(1, 4); i++) {
				movingUnits.push_back(new PredatorCell(int(getRandomNumberRange(0, 8000 - 800)) - 3900, int(getRandomNumberRange(0, 8000 - 800)) - 3900, generateNewId(), this));
			}
		}
	}


	std::vector<int> deletedIndicies;
	for (int i = 0; i < simpleUnits.size(); i++) {
		simpleUnits[i]->update();
		if (simpleUnits[i]->readyForDeletion()) {
			deletedIndicies.push_back(i);
		}
	}



	for (int i = 0; i < deletedIndicies.size(); i++) {
		int deleteIndex = deletedIndicies[i];
		delete simpleUnits[deleteIndex - i];
		simpleUnits.erase(simpleUnits.begin() + (deleteIndex - i));
	}

	deletedIndicies.clear();
	for (int i = 0; i < staticUnits.size(); i++) {
		staticUnits[i]->update();
		if (staticUnits[i]->readyForDeletion()) {
			deletedIndicies.push_back(i);
		}
	}

	

	for (int i = 0; i < deletedIndicies.size(); i++) {
		int deleteIndex = deletedIndicies[i];
		if (clickedThing != nullptr) {
			if (staticUnits[deleteIndex - i]->getId() == clickedThing->getId()) {
				clickedThing = nullptr;
				gui->hide();
			}
		}
			
		delete staticUnits[deleteIndex - i];
		staticUnits.erase(staticUnits.begin() + (deleteIndex - i));
	}
	
	deletedIndicies.clear();
	for (int i = 0; i < movingUnits.size(); i++) {
		movingUnits[i]->update();
		if (movingUnits[i]->readyForDeletion()) {
			deletedIndicies.push_back(i);
		}
	}



	for (int i = 0; i < deletedIndicies.size(); i++) {
		int deleteIndex = deletedIndicies[i];
		if (clickedThing != nullptr) {
			if (movingUnits[deleteIndex - i]->getId() == clickedThing->getId()) {
				clickedThing = nullptr;
				gui->hide();
			}
		}

		delete movingUnits[deleteIndex - i];
		movingUnits.erase(movingUnits.begin() + (deleteIndex - i));
	}

	gui->update();
}

void System::draw()
{
	window->clear();
	for (int i = 0; i < staticUnits.size(); i++) {
		staticUnits[i]->draw(window);
	}
	for (int i = 0; i < simpleUnits.size(); i++) {
		simpleUnits[i]->draw(window);
	}

	for (int i = 0; i < movingUnits.size(); i++) {
		movingUnits[i]->draw(window);
	}
	
	window->setView(guiView);
	gui->draw();
	window->draw(fpsText);
	window->setView(view);
	window->display();
}


System::~System()
{
}
