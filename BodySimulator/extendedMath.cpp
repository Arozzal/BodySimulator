#include "extendedMath.hpp"
#include <random>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <SFML\System.hpp>
#include <SFML/Window/Mouse.hpp>

typedef std::mt19937 rng_type;
std::uniform_int_distribution<rng_type::result_type> udist(0, 2000000000);
rng_type rng;
rng_type::result_type seedval;

void initMath()
{
	seedval = time(NULL);
	rng.seed(seedval);
}

unsigned int getRandomNumber()
{
	rng_type::result_type random_number = udist(rng);
	return random_number;
}

unsigned int getRandomNumberRange(int begin, int end)
{
	std::uniform_int_distribution<rng_type::result_type> udistRange(begin, end);
	rng_type::result_type random_number = udistRange(rng);
	return random_number;
}

float getRandomFloat()
{
	return getRandomNumber() / float(INT_MAX) * 2 - 1;
}

sf::Vector2f getRandomDirectionVec()
{
	return sf::Vector2f(getRandomFloat(), getRandomFloat());
}

sf::Vector2f addVec(sf::Vector2f first, sf::Vector2f second)
{
	return sf::Vector2f(first.x + second.x, first.y + second.y);
}

sf::Vector2f subVec(sf::Vector2f first, sf::Vector2f second)
{
	return sf::Vector2f(first.x - second.x, first.y - second.y);
}

float calcVecLength(sf::Vector2f vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f normalizeVec(sf::Vector2f vec)
{
	float normal = calcVecLength(vec);
	return sf::Vector2f(vec.x / normal, vec.y / normal);
}

sf::Vector2f mulScalarVec(sf::Vector2f vec, float scalar)
{
	return sf::Vector2f(vec.x * scalar, vec.y * scalar);
}

std::string setAmountOfDecimals(float number, int amountOfDigits)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(amountOfDigits) << number;
	return ss.str();
}

