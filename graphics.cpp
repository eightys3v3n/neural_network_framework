#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>
#include "math.hpp"
#include "network.hpp"

extern int topBoarder;
extern int bottomBoarder;
extern int leftBoarder;
extern int rightBoarder;
extern int axionThickness;

void calculateLevel(sf::RenderWindow& window, Level& level)
{
	double newY;

	for (unsigned int n = 0; n < level.neurons.size(); n++)
	{
		newY = (double)1 / ( level.neurons.size() - 1 ) * ( window.getSize().y - topBoarder - bottomBoarder );
		newY *= n;
		newY += topBoarder;

		level.neurons[n].nucleus.setPosition(sf::Vector2f(level.x, newY));
	}
}

void calculateNetwork(sf::RenderWindow& window, Network& network)
{
	double newX;

	for (unsigned int l = 0; l < network.levels.size(); l++)
	{
		newX = (double)1 / ( network.levels.size() - 1 ) * ( window.getSize().x - leftBoarder - rightBoarder );
		newX *= l;
		newX += leftBoarder;

		network.levels[l].x = newX;

		calculateLevel(window, network.levels[l]);
	}
}

void calculateAxions(Network& network)
{
	double newX;
	double newY;

	for (unsigned int l = 0; l < network.levels.size(); l++)
	{
	for (unsigned int n = 0; n < network.levels[l].neurons.size(); n++)
	{
	for (unsigned int a = 0; a < network.levels[l].neurons[n].childNeurons.size(); a++)
	{
		network.levels[l].neurons[n].childAxions[ network.levels[l].neurons[n].childNeurons[a] ].setSize( sf::Vector2f(1, axionThickness) );
		network.levels[l].neurons[n].childAxions[ network.levels[l].neurons[n].childNeurons[a] ].setPosition( sf::Vector2f(0, 0) );
		network.levels[l].neurons[n].childAxions[ network.levels[l].neurons[n].childNeurons[a] ].setOrigin( sf::Vector2f(0, axionThickness / 2) );

		newX = network.levels[l].neurons[n].nucleus.getPosition().x;
		newY = network.levels[l].neurons[n].nucleus.getPosition().y;

		network.levels[l].neurons[n].childAxions[ network.levels[l].neurons[n].childNeurons[a] ].setPosition( sf::Vector2f(newX, newY) );

		newX = network.levels[l].neurons[n].childNeurons[a]->nucleus.getPosition().x - network.levels[l].neurons[n].nucleus.getPosition().x;
		newY = network.levels[l].neurons[n].childNeurons[a]->nucleus.getPosition().y - network.levels[l].neurons[n].nucleus.getPosition().y;

		network.levels[l].neurons[n].childAxions[ network.levels[l].neurons[n].childNeurons[a] ].setSize( sf::Vector2f( sqrt(newX * newX + newY * newY), axionThickness / 2) );

		network.levels[l].neurons[n].childAxions[ network.levels[l].neurons[n].childNeurons[a] ].setRotation( degree( atan( newY / newX ) ) );
	}
	}
	}
}

void drawAxions(sf::RenderWindow& window, Neuron& neuron)
{
	for (unsigned int a = 0; a < neuron.childNeurons.size(); a++)
	{
		if (*neuron.childNeurons[a]->parentStatus[ &neuron ])
			neuron.childAxions[neuron.childNeurons[a]].setOutlineColor(sf::Color::White);
		else
			neuron.childAxions[neuron.childNeurons[a]].setOutlineColor(sf::Color::Transparent);

		window.draw(neuron.childAxions[neuron.childNeurons[a]]);
	}
}

void drawNeuron(sf::RenderWindow& window, Neuron& neuron)
{
	drawAxions(window, neuron);

	if (neuron.output)
		neuron.nucleus.setFillColor( sf::Color::White );
	else
		neuron.nucleus.setFillColor( sf::Color::Transparent );

	window.draw(neuron.nucleus);
}

void drawLevel(sf::RenderWindow& window, Level& level)
{
	for (unsigned int n = 0; n < level.neurons.size(); n++)
		drawNeuron(window, level.neurons[n]);
}

void drawNetwork(sf::RenderWindow& window, Network& network)
{
	for (unsigned int l = 0; l < network.levels.size(); l++)
		drawLevel(window, network.levels[l]);
}

void initiateNetwork(sf::RenderWindow& window, Network& network)
{
	calculateNetwork(window, network);
	calculateAxions(network);
	drawNetwork(window, network);
}