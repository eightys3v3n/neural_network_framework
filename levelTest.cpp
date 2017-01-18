#ifndef LEVEL_TEST_
	#define LEVEL_TEST_SA
	#include "levelTest.hpp"
#endif // LEVEL_TEST_

namespace test
{

bool level()
{
	if (levelSt)
		return false;

	if (neuron() || levelSetSize() || levelConnect() || levelDisconnect() || levelSetInput() || levelSetOutput() || levelGlobalSetBias() || levelForward() || levelBackward())
	{
		std::cout << "level failed" << std::endl;
		return true;
	}

	std::cout << "level passed" << std::endl;
	levelSt = true;
	return false;
}

bool levelSetSize()
{
	if (levelSetSizeSt)
		return false;

	Level level;

	level.setSize(4);

	if (level.neurons.size() != 4)
	{
		std::cout << " did not resize the neurons vector correctly" << std::endl;
		std::cout << " levelSetSize failed" << std::endl;
		return true;
	}

	std::cout << " levelSetSize passed" << std::endl;
	levelSetSizeSt = true;
	return false;
}

bool levelConnect()
{
	if (levelConnectSt)
		return true;

	Level parent, middle, child;

	if (neuronConnect())
	{
		std::cout << " levelConnect failed" << std::endl;
		return true;
	}

	std::cout << " levelConnect passed" << std::endl;
	levelConnectSt = true;
	return false;
}

bool levelDisconnect()
{
	if (levelDisconnectSt)
		return true;

	if (neuronDisconnect())
	{
		std::cout << " levelDisconnect failed" << std::endl;
		return true;
	}

	std::cout << " levelDisconnect passed" << std::endl;
	levelDisconnectSt = true;
	return false;
}

bool levelSetInput()
{
	if (levelSetInputSt)
		return false;

	Level level;
	level.setSize(3);

	level.setInput(std::vector<double>{1.1, 1.1, 1.1});

	for (auto& n : level.neurons)
	{
		if (n.input != 1.1)
		{
			std::cout << " a neurons input was not or incorrectly set" << std::endl;
			std::cout << " levelSetInput failed" << std::endl;
			return true;
		}
	}

	std::cout << " levelSetInput passed" << std::endl;
	levelSetInputSt = true;
	return false;
}

bool levelSetOutput()
{
	if (levelSetOutputSt)
		return false;

	Level level;
	level.setSize(3);

	level.setOutput(std::vector<double>{1.1, 1.1, 1.1});

	for (auto& n : level.neurons)
	{
		if (n.output != 1.1)
		{
			std::cout << " a neurons output was not or incorrectly set" << std::endl;
			std::cout << " levelSetOutput failed" << std::endl;
			return true;
		}
	}

	std::cout << " levelSetOutput passed" << std::endl;
	levelSetOutputSt = true;
	return false;
}

bool levelGlobalSetBias()
{
	if (levelGlobalSetBiasSt)
		return false;

	Level parent, child;

	if (levelSetSize())
	{
		std::cout << " levelSetSize failed" << std::endl;
		return true;
	}

	parent.setSize(3);
	child.setSize(3);
	parent.connect(&child);
	parent.globalSetBias(.44);

	for (auto& n : parent.neurons)
	{
		for (auto& b : n.childBias)
		{
			if (b.second != .44)
			{
				std::cout << " atleast one bias has not been set correctly" << std::endl;
				std::cout << " levelGlobalSetBias failed" << std::endl;
				return true;
			}
		}
	}

	std::cout << " levelGlobalSetBias passed" << std::endl;
	levelGlobalSetBiasSt = true;
	return false;
}

bool levelForward()
{
	if (levelForwardSt)
		return false;

	Level level;

	if (neuronForward() || levelGlobalSetBias())
	{
		std::cout << " levelForward failed" << std::endl;
		return true;
	}

	level.setSize(3);
	level.setInput(std::vector<double>{1.4, 1.4, 1.4});
	level.globalSetBias(2);
	level.forward();

	for (auto& n : level.neurons)
	{
		// assumes a neurons computation is ( input >= 1 ? output = 1 : output = 0 ) and that neuron outputs are initialized as zero
		if (n.output != 1)
		{
			std::cout << " a neuron is not being simulated" << std::endl;
			std::cout << " levelForward failed" << std::endl;
			return true;
		}
	}

	std::cout << " levelForward passed" << std::endl;
	levelForwardSt = true;
	return false;
}

bool levelBackward()
{
	if (levelBackwardSt)
		return false;

	Level level;

	if (neuronBackward() || levelGlobalSetBias())
	{
		std::cout << " levelBackward failed" << std::endl;
		return true;
	}

	level.setSize(3);
	level.setOutput(std::vector<double>{1.4, 1.4, 1.4});
	level.globalSetBias(0.5);
	level.backward();

	for (auto& n : level.neurons)
	{
		// assumes a neurons computation is ( output >= 1 ? input = 1 : input = 0 ) and that neuron outputs are initialized as zero
		if (n.input != 1)
		{
			std::cout << " a neuron is not being simulated" << std::endl;
			std::cout << " levelBackward failed" << std::endl;
			return true;
		}
	}

	std::cout << " levelBackward passed" << std::endl;
	levelBackwardSt = true;
	return false;
}

}

#ifdef LEVEL_TEST_SA
	int main()
	{
		if (test::level())
			return true;

		return false;
	}
#endif // LEVEL_TEST_SA