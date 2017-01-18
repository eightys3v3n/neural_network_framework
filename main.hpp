#ifndef MAIN_
	#define MAIN_

	#include <iostream>
	#include <vector>
	#include <thread>
	#include <chrono>
	#include "network.hpp"
	#include "graphics.hpp"

	bool quit = false;
	#ifdef SFML
	int windowWidth = 800;
	int windowHeight = 500;
	int neuronRadius = 10;
	int neuronOutlineThickness = 2;
	int neuronSeperation = 20;
	int axionOutlineThickness = 2;
	int axionThickness = 2;
	int topBoarder = 20;
	int bottomBoarder = 20;
	int leftBoarder = 110;
	int rightBoarder = 20;
	sf::Color neuronFillColour = sf::Color::White;
	sf::Color neuronOutlineColour = sf::Color::White;
	sf::Color axionFillColour = sf::Color::White;
	sf::Color axionOutlineColour = sf::Color::White;
	#endif // SFML
#endif // MAIN_