#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class game_of_life {
private:
	static const unsigned int STUPACA = 20;
	static const unsigned int REDAKA = 15; // 3/4 stupaca zbog rezolucije SFML prozora
	float cellSize = 40.f; //veličina ćelije u SFML-u
	bool generacija[REDAKA][STUPACA];
	bool sljedecaGeneracija[REDAKA][STUPACA];
	bool slucajnaVrijednost();
	bool celijaZauzeta(int i, int j) const;

	sf::RenderWindow* window;

	//grid colors
	sf::Color aliveCell = sf::Color(134, 167, 137);
	sf::Color deadCell = sf::Color(79, 111, 82);
	sf::Color outline = sf::Color(115, 144, 114);

	//flower colors
	vector<sf::Color> flowerColors =
	{
		sf::Color(83, 62, 133), //purple
		sf::Color(7, 102, 173), //blue
		sf::Color(244, 212, 91), //yellowish
		sf::Color(232, 124, 60), //orange
		sf::Color(216, 76, 59), //red
		sf::Color(224, 139, 134) //pink

	};
public:
	game_of_life();
	void slijedecaGeneracija();
	void iscrtaj() const; //console game
	void draw(sf::RenderWindow& window) const; //SFML game
};
#endif