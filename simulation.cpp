#include <vector>

struct Simulation
{
  Simulation();
  Simulation(std::vector<bool> &newInputs, std::vector<bool> &newOutputs);

  std::vector<bool> inputs;
  std::vector<bool> outputs;
};

Simulation::Simulation()
{
  inputs.resize(0);
  outputs.resize(0);
}

Simulation::Simulation(std::vector<bool> &newInputs, std::vector<bool> &newOutputs)
{
  inputs = newInputs;
  outputs = newOutputs;
}