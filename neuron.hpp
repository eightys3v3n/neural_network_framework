#ifndef NEURON_
#define NEURON_

#include <vector>
#include <map>
#include <stdlib.h>
#ifdef SMFL
#include <SFML/Graphics.hpp>
#endif // SFML
#include "math.hpp"

struct Neuron
{
	#ifdef SFML
	Neuron();
	#endif // SFML

  double output = 0;
  double input = 0;
  std::vector<Neuron*> childNeurons;
  std::vector<Neuron*> parentNeurons;
  std::map<Neuron*, bool> childStatus;
  std::map<Neuron*, bool*> parentStatus;
  std::map<Neuron*, double> childBias;
  std::map<Neuron*, double*> parentBias;
	#ifdef SFML
	sf::CircleShape nucleus;
	std::map<Neuron*, sf::RectangleShape> childAxions;
	std::map<Neuron*, sf::RectangleShape*> parentAxions;
	#endif // sFML

  void connect(Neuron* neuron);
	std::vector<Neuron*> disconnect() { return childNeurons; }
  void disconnect(Neuron* neuron);
  void forward();
  bool forward(double newInput, Neuron* parent);
  void backward();
  bool backward(double newOutput, Neuron* child);
  void randBias();
  void randBias(Neuron* targetChild);
  void randBias(Neuron& targetChild) { randBias(&targetChild); }
};

#endif // NEURON_