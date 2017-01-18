#ifndef NETWORK_TEST_
#define NETWORK_TEST_

#include <iostream>
#include <vector>
#include "../network.cpp"
#include "levelTest.hpp"

namespace test
{
	bool networkSt = false;
	bool networkStructureSt = false;
	bool networkInputSt = false;
	bool networkOutputSt = false;
	bool networkGlobalSetBiasSt = false;
	bool networkForwardSt = false;
	bool networkBackwardSt = false;

	bool network();
	bool networkStructure();
	bool networkInput();
	bool networkOutput();
	bool networkGlobalSetBias();
	bool networkForward();
	bool networkBackward();
}

#ifndef NETWORK_TEST_SA
	#include "networkTest.cpp"
#endif // NETWORK_TEST_SA
#endif // NETWORK_TEST_