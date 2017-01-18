#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#ifdef SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#endif // SFML

#include "network.hpp"
#include "graphics.hpp"

using namespace std;

#ifdef SFML
using namespace sf;
#endif // SFML

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
Color neuronFillColour = Color::White;
Color neuronOutlineColour = Color::White;
Color axionFillColour = Color::White;
Color axionOutlineColour = Color::White;
#endif // SFLM

int main()
{
	Network network;
	#ifdef SFML
	RenderWindow window(VideoMode(windowWidth, windowHeight), "neural network simulator", Style::Close);
	Event event;
	#endif // SFML

	network.structure(vector<unsigned int>{9, 9, 9, 9});
	network.randomize();

	#ifdef SFML
	window.setFramerateLimit(6);
	initiateNetwork(window, network);
	#endif // SFML

	while (!quit)
	{
		#ifdef SFML
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				quit = true;
		}

		window.clear( Color::Black );

		drawNetwork(window, network);

		window.display();
		#endif // SFML
	}

	return false;
}