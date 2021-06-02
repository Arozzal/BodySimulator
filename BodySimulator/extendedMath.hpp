#pragma once
#include<SFML\System\Vector2.hpp>
#include<SFML\Graphics\RenderWindow.hpp>
#include <string>

void initMath();
unsigned int getRandomNumber();
unsigned int getRandomNumberRange(int begin, int end);
float getRandomFloat();

sf::Vector2f getRandomDirectionVec();
sf::Vector2f addVec(sf::Vector2f first, sf::Vector2f second);
sf::Vector2f subVec(sf::Vector2f first, sf::Vector2f second);
float calcVecLength(sf::Vector2f vec);
sf::Vector2f normalizeVec(sf::Vector2f vec);
sf::Vector2f mulScalarVec(sf::Vector2f vec, float scalar);
std::string setAmountOfDecimals(float number, int amountOfDigits);
