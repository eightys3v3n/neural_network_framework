#ifndef LEVEL_TEST_
#define LEVEL_TEST_

#include <iostream>
#include <vector>
#include "../level.hpp"
#include "neuronTest.hpp"

namespace test
{
	bool levelSt = false;
	bool levelSetSizeSt = false;
	bool levelConnectSt = false;
	bool levelDisconnectSt = false;
	bool levelSetInputSt = false;
	bool levelSetOutputSt = false;
	bool levelGlobalSetBiasSt = false;
	bool levelForwardSt = false;
	bool levelBackwardSt = false;

	bool level();
	bool levelSetSize();
	bool levelConnect();
	bool levelDisconnect();
	bool levelSetInput();
	bool levelSetOutput();
	bool levelGlobalSetBias();
	bool levelForward();
	bool levelBackward();
}

#ifndef LEVEL_TEST_SA
	#include "levelTest.cpp"
#endif // LEVEL_TEST_SA
#endif // LEVEL_TEST_