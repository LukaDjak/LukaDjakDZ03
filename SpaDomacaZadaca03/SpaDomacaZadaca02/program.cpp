#include <SFML/Graphics.hpp>
#include "game_of_life.h"

int main()
{
	game_of_life the_game;

	//---CONSOLE GAME OF LIFE - uncomment the code
	/*
	bool dalje;
		do 
		{
			the_game.iscrtaj();
			the_game.slijedecaGeneracija();

			cout << "Dalje (1/0): ";
			cin >> dalje;
			system("CLS");
		} while (dalje);
	return 0;
	*/

	//---SFML GAME OF LIFE

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hello, SFML world!");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		the_game.draw(window);
		the_game.slijedecaGeneracija();
		window.display();

		sf::sleep(sf::seconds(2));
	}
}