#ifndef NETWORK_
	#define NETWORK_

#include <vector>
#include "level.hpp"

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

#endif // NETWORK_