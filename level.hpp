#ifndef LEVEL_
#define LEVEL_

#include <vector>
#include "neuron.hpp"

struct Level
{
  std::vector<Neuron> neurons;
	double x = 0;

  void setSize(int newSize);
  void connect(Level* level);
  void disconnect(Level* level);
  void setInput(std::vector<double> newInputs);
  void setOutput(std::vector<double> newOutputs);
  void forward();
  void backward();
  void setBias(Neuron* parent, Neuron* child, double newBias);
  void globalSetBias(double newBias);
  void randBias();
};

#endif // LEVEL_