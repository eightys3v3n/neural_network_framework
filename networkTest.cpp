#ifndef NETWORK_TEST_
	#define NETWORK_TEST_SA
	#include "networkTest.hpp"
#endif // NETWORK_TEST_

namespace test
{

bool network()
{
	if (networkSt)
		return false;

	if (level() || networkStructure() || networkInput() || networkOutput() || networkGlobalSetBias() || networkForward() || networkBackward())
	{
		std::cout << "network failed" << std::endl;
		return true;
	}

	std::cout << "network passed" << std::endl;
	networkSt = true;
	return false;
}

bool networkStructure()
{
	if (networkStructureSt)
		return false;

	Network network;

	if (test::levelSetSize())
	{
		std::cout << " networkStructure failed" << std::endl;
		return true;
	}

	network.structure(std::vector<unsigned int>{3, 3, 3});

	if (network.structure() != std::vector<unsigned int>{3, 3, 3})
	{
		std::cout << " network.structure() returns an incorrect vector" << std::endl;
		std::cout << " networkStructure failed" << std::endl;
		return true;
	}

	if (network.levels.size() != 3)
	{
		std::cout << " levels was resized wrong" << std::endl;
		std::cout << " networkStructure failed" << std::endl;
		return true;
	}

	for (auto& l : network.levels)
	{
		if (l.neurons.size() != 3)
		{
			std::cout << " neurons was resized wrong" << std::endl;
			std::cout << " networkStructure failed" << std::endl;
			return true;
		}
	}

	std::cout << " networkStructure passed" << std::endl;
	networkStructureSt = true;
	return false;
}

bool networkInput()
{
	if (networkInputSt)
		return false;

	Network network;

	if (levelSetInput() || networkStructure())
	{
		std::cout << " networkInput failed" << std::endl;
		return true;
	}

	network.structure(std::vector<unsigned int>{3, 3, 3});
	network.input(std::vector<double>{1.2, 1.2, 1.2});

	if (network.input() != std::vector<double>{1.2, 1.2, 1.2})
	{
		// this could be a problem with either the network.input() function or the network.input(std::vector<double) function.
		std::cout << " network.input() does not return the correct values" << std::endl;
		std::cout << " networkInput failed" << std::endl;
		return true;
	}

	for (auto& n : network.levels[0].neurons)
	{
		if (n.input != 1.2)
		{
			std::cout << " one of the neuron's input was not set correctly" << std::endl;
			std::cout << " networkInput failed" << std::endl;
			return true;
		}
	}

	std::cout << " networkInput passed" << std::endl;
	networkInputSt = true;
	return false;
}

bool networkOutput()
{
	if (networkOutputSt)
		return false;

	Network network;

	if (levelSetOutput() || networkStructure())
	{
		std::cout << " networkOutput failed" << std::endl;
		return true;
	}

	network.structure(std::vector<unsigned int>{3, 3, 3});
	network.output(std::vector<double>{1.2, 1.2, 1.2});

	if (network.output() != std::vector<double>{1.2, 1.2, 1.2})
	{
		// this could be a problem with either the network.input() function or the network.input(std::vector<double) function.
		std::cout << " network.input() does not return the correct values" << std::endl;
		std::cout << " networkOutput failed" << std::endl;
		return true;
	}

	for (auto& n : network.levels[3].neurons)
	{
		if (n.output != 1.2)
		{
			std::cout << " one of the neuron's output was not set correctly" << std::endl;
			std::cout << " networkOutput failed" << std::endl;
			return true;
		}
	}

	std::cout << " networkOutput passed" << std::endl;
	networkOutputSt = true;
	return false;
}

bool networkGlobalSetBias()
{
	if (networkGlobalSetBiasSt)
		return false;

	Network network;

	if (levelGlobalSetBias() || networkStructure())
	{
		std::cout << " networkGlobalSetBias failed" << std::endl;
		return true;
	}

	network.structure(std::vector<unsigned int>{3, 3, 3});
	network.globalSetBias(.33);

	for (auto& l : network.levels)
	{
		for (auto& n : l.neurons)
		{
			for (auto& b : n.childBias)
			{
				if (b.second != .33)
				{
					std::cout << " atleast one bias was not set correctly" << std::endl;
					std::cout << " networkGlobalSetBias failed" << std::endl;
					return true;
				}
			}
		}
	}

	std::cout << " networkGlobalSetBias passed" << std::endl;
	networkGlobalSetBiasSt = true;
	return false;
}

bool networkForward()
{
	if (networkForwardSt)
		return false;

	Network network;

	if (levelForward() || networkStructure() || networkInput() || networkOutput())
	{
		std::cout << " networkForward failed" << std::endl;
		return true;
	}

	network.structure(std::vector<unsigned int>{3, 3, 3});
	network.input(std::vector<double>{1, 1, 1});
	network.globalSetBias(2);
	passon = true;
	autocalc = true;
	network.forward();

	if (network.input() != std::vector<double>{0, 0, 0})
	{
		std::cout << " network did not reset inputs" << std::endl;
		std::cout << " networkForward failed" << std::endl;
		return true;
	}

	if (network.output() != std::vector<double>{1, 1, 1})
	{
		std::cout << " network outputs are incorrect" << std::endl;
		std::cout << " networkForward failed" << std::endl;
		return true;
	}

	std::cout << " networkForward passed" << std::endl;
	networkForwardSt = true;
	return false;
}

bool networkBackward()
{
	if (networkBackwardSt)
		return false;

	Network network;

	if (levelBackward() || networkStructure() || networkInput() || networkOutput())
	{
		std::cout << " networkBackward failed" << std::endl;
		return true;
	}

	network.structure(std::vector<unsigned int>{3, 3, 3});
	network.output(std::vector<double>{1, 1, 1});
	network.globalSetBias(.5);
	passon = true;
	autocalc = true;
	network.backward();

	if (network.output() != std::vector<double>{0, 0, 0})
	{
		std::cout << " network did not reset outputs" << std::endl;
		std::cout << " networkBackward failed" << std::endl;
		return true;
	}

	if (network.input() != std::vector<double>{1, 1, 1})
	{
		std::cout << " network inputs are incorrect" << std::endl;
		std::cout << " networkBackward failed" << std::endl;
		return true;
	}

	std::cout << " networkBackward passed" << std::endl;
	networkBackwardSt = true;
	return false;
}

}

#ifdef NETWORK_TEST_SA
	int main()
	{
		if (test::network())
			return true;

		return false;
	}
#endif // NETWORK_TEST_SA