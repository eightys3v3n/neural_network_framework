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

void Level::setSize(int newSize)
{
  neurons.resize(newSize);
}

void Level::connect(Level* level)
{
  for (auto& c : level->neurons)
    for (auto& n : neurons)
      n.connect(&c);
}

void Level::disconnect(Level* level)
{
  for (auto& c : level->neurons)
    for (auto& n : neurons)
      n.disconnect(&c);
}

void Level::setInput(std::vector<double> newInputs)
{
  for (unsigned int i = 0; i < newInputs.size(); i++)
    neurons[i].input = newInputs[i];
}

void Level::setOutput(std::vector<double> newOutputs)
{
  for (unsigned int o = 0; o < newOutputs.size(); o++)
    neurons[o].output = newOutputs[o];
}

void Level::forward()
{
  for (auto& n : neurons)
    n.forward();
}

void Level::backward()
{
  for (auto& n : neurons)
    n.backward();
}

void Level::setBias(Neuron* parent, Neuron* child, double newBias)
{
  parent->childBias[child] = newBias;
}

void Level::globalSetBias(double newBias)
{
  for (auto& n : neurons)
  {
    for (auto& b : n.childBias)
      b.second = newBias;
  }
}

void Level::randBias()
{
  for (auto& n : neurons)
    n.randBias();
}