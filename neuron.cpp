#include <vector>
#include <map>
#include <stdlib.h>
#ifdef SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#endif // SFML
#include "math.hpp"

#ifdef SFML
extern int neuronRadius;
extern int neuronOutlineThickness;
extern int axionOutlineThickness;
extern int axionThickness;
extern int topBoarder;
extern int bottomBoarder;
extern int leftBoarder;
extern int rightBoarder;
extern sf::Color neuronFillColour;
extern sf::Color neuronOutlineColour;
extern sf::Color axionFillColour;
extern sf::Color axionOutlineColour;
#endif // SFML
bool passon = true; // if true; each neuron will trigger child neurons upon completing calculation
bool autocalc = true; // if true; neurons will calculate upon recieving the last parent's input

struct Neuron
{
	Neuron();

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
	#endif // SFML

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

#ifdef SFML
Neuron::Neuron()
{
	nucleus.setRadius(neuronRadius);
	nucleus.setFillColor( sf::Color::Transparent );
	nucleus.setOutlineColor( neuronOutlineColour );
	nucleus.setOutlineThickness( neuronOutlineThickness );
	nucleus.setPosition( sf::Vector2f(0, 0));
	nucleus.setOrigin( sf::Vector2f( neuronRadius, neuronRadius ));
}
#endif // SFML

void Neuron::connect(Neuron* neuron)
{
  childNeurons.push_back( neuron );

  childStatus[ neuron ] = false;
  childBias[neuron] = 0;
	#ifdef SFML
	childAxions[ neuron ].setFillColor( axionFillColour );
	childAxions[ neuron ].setOutlineThickness( axionOutlineThickness );
	#endif // SFML

  neuron->parentNeurons.push_back( this );
  neuron->parentStatus[ this ] = &childStatus[ neuron ];
  neuron->parentBias[ this ] = &childBias[ neuron ];

  #ifdef SFML
	neuron->parentAxions[ this ] = &childAxions[ neuron ];
  #endif // SFML
}

void Neuron::disconnect(Neuron* neuron)
{
  for (unsigned int c = 0; c < childNeurons.size(); c++)
    if (childNeurons[c] == neuron)
      childNeurons.erase(childNeurons.begin() + c);

  childStatus.erase(neuron);
  childBias.erase(neuron);

  #ifdef SFML
	childAxions.erase( childAxions.find( neuron ) );
  #endif // SFML

  for (unsigned int c = 0; c < neuron->parentNeurons.size(); c++)
    if (neuron->parentNeurons[c] == this)
      neuron->parentNeurons.erase(neuron->parentNeurons.begin() + c);

  neuron->parentStatus.erase(this);
  neuron->parentBias.erase(this);

  #ifdef SFML
  neuron->parentAxions.erase( neuron->parentAxions.find( this ) );
  #endif // SFML
}

void Neuron::forward()
{
  output = ( input >= 1 ? 1 : 0 );
  input = 0;

  for (auto& p : parentStatus)
    *p.second = false;

	if (passon)
  	for (auto& c : childNeurons)
			c->forward(output * childBias[c], this);
}

bool Neuron::forward(double newInput, Neuron* parent)
{
  input += newInput;
  *parentStatus[parent] = true;

  for (auto& p : parentStatus)
  {
    if (p.second == false)
      return true;
  }

	if (autocalc)
  	forward();

  return false;
}

void Neuron::backward()
{
  input = ( output >= 1 ? 1 : 0 );
  output = 0;

  for (auto& c : childStatus)
    c.second = false;

	if (passon)
  	for (auto& p : parentNeurons)
   		p->backward(input / *parentBias[p], this);
}

bool Neuron::backward(double newOutput, Neuron* child)
{
  output += newOutput;
  childStatus[child] = true;

  for (auto& c : childStatus)
  {
    if (c.second == false)
      return true;
  }

	if (autocalc)
  	backward();

  return false;
}

void Neuron::randBias()
{
	int random = rand() % 1000 + 1;

  for (auto& b : childBias)
		b.second = random / 1000;
}