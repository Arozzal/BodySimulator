#include <SFML/Graphics.hpp>
#include "System.hpp"

int main()
{

	System system;

	while (true)
	{
		system.updateInput();
		system.update();
		system.draw();
	}

	return 0;
}