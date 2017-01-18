#include <vector>
#include "level.hpp"

extern bool passon;

struct Network
{
  std::vector<Level> levels;

	std::vector<unsigned int> structure();
  void structure(std::vector<unsigned int> newStructure);
  std::vector<double> input();
  void input(std::vector<double> newInputs);
  std::vector<double> output();
  void output(std::vector<double> newOutputs);
	void globalSetBias(double newBias);
  void forward();
  void backward();
	void randomize();

	//void evolve(std::vector<Move> incorrect);
};

std::vector<unsigned int> Network::structure()
{
	std::vector<unsigned int> output(levels.size());

	for (unsigned int l = 0; l < levels.size(); l++)
		output[l] = levels[l].neurons.size();

	return output;
}

void Network::structure(std::vector<unsigned int> newStructure)
{
  for (auto& l : newStructure)
  {
    levels.resize(levels.size() + 1);
    levels[levels.size() - 1].setSize(l);

    if (levels.size() > 1)
      levels[levels.size() - 2].connect( &levels[levels.size() - 1] );
  }
}

void Network::input(std::vector<double> newInputs)
{
  for(unsigned int n = 0; n < levels[0].neurons.size(); n++)
    levels[0].neurons[n].input = newInputs[n];
}

void Network::output(std::vector<double> newOutputs)
{
  for(unsigned int n = 0; n < levels[levels.size() - 1].neurons.size(); n++)
    levels[levels.size() - 1].neurons[n].output = newOutputs[n];
}

std::vector<double> Network::input()
{
  std::vector<double> input;

  for (auto& n: levels[0].neurons)
    input.push_back(n.input);

  return input;
}

std::vector<double> Network::output()
{
  std::vector<double> output;

  for (auto& n: levels[levels.size() - 1].neurons)
    output.push_back(n.output);

  return output;
}

void Network::globalSetBias(double newBias)
{
	for (auto& l : levels)
		l.globalSetBias(newBias);
}

void Network::forward()
{
	if (passon)
		levels[0].forward();
	else
  	for (auto& l : levels)
			l.forward();
}

void Network::backward()
{
	if (passon)
		levels[levels.size() - 1].backward();
	else
		for (unsigned int l = levels.size() - 1; l - 1 > 0; l--)
  		levels[l].backward();
}

void Network::randomize()
{
	for (auto& l: levels)
		for (auto& n: l.neurons)
			n.randBias();
}

/*void Network::evolve(std::vector<Move> incorrect)
{

}*/