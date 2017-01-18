#ifndef NETWORKIO_
#define NETWORKIO_

#include "network.hpp"

bool load(Network &network);
bool interpretNetwork(std::string &raw, Network &network);
bool interpretCluster(std::string raw, Cluster &cluster);
bool interpretLevel(std::string raw, Level &level);
bool interpretNeuron(std::string raw, Neuron &neuron);
bool interpretOutput(std::string raw, Connection &connection);
bool save(Network &network);

#endif // NETWORKIO_