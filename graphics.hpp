#ifndef GRAPHICS_
	#define GRAPHICS_

	#include <SFML/Graphics.hpp>
	#include <SFML/System.hpp>
	#include "network.hpp"
	#include "level.hpp"
	#include "neuron.hpp"

	void calculateLevel(sf::RenderWindow& window, Level& level);
	void calculateNetwork(sf::RenderWindow& window, Network& network);
	void calculateAxions(Network& network);

	void drawAxions(sf::RenderWindow& window, Neuron& neuron);
	void drawNeuron(sf::RenderWindow& window, Neuron& neuron);
	void drawLevel(sf::RenderWindow& window, Level& level);
	void drawNetwork(sf::RenderWindow& window, Network& network);

	void initiateNetwork(sf::RenderWindow& window, Network& network);

#endif // GRAPHICS_