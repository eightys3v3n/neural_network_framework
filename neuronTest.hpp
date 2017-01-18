#ifndef NEURONTEST_
#define NEURONTEST_

#include <string>

extern bool neuronTestStatus;
extern bool neuronConnectTestStatus;
extern bool neuronDisconnectTestStatus;
extern bool neuronForwardTestStatus;
extern bool neuronBackwardTestStatus;

bool neuronTest();
bool neuronConnectTest();
bool neuronDisconnectTest();
bool neuronForwardTest();
bool neuronBackwardTest();

#endif // NEURONTEST_