#include <string>
#include "neuron.hpp"
#include "neuronTest.hpp"

bool neuronTestStatus = false;
bool neuronConnectTestStatus = false;
bool neuronDisconnectTestStatus = false;
bool neuronForwardTestStatus = false;
bool neuronBackwardTestStatus = false;
extern bool passon;
extern bool autocalc;

bool neuronTest()
{
	if (neuronTestStatus)
		return false;

	try
	{
		neuronConnectTest();
	}
	catch ( std::string *error )
	{
		throw new std::string("neuronConnectTest: " + *error );
		return true;
	}

	try
	{
		neuronDisconnectTest();
	}
	catch ( std::string *error )
	{
		throw new std::string("neuronDisconnectTest: " + *error );
		return true;
	}

	try
	{
		neuronForwardTest();
	}
	catch ( std::string *error )
	{
		throw new std::string("neuronForwardTest: " + *error );
		return true;
	}

	try
	{
		neuronBackwardTest();
	}
	catch ( std::string *error )
	{
		throw new std::string("neuronBackwardTest: " + *error );
		return true;
	}

	neuronTestStatus = true;
	return false;
}

bool neuronConnectTest()
{
	if (neuronConnectTestStatus)
		return false;

	Neuron parent, child;

	parent.connect(&child);

	if (parent.childNeurons.size() != 1)
	{
		throw new std::string( "parent.childNeurons is not initialized correctly" );
		return true;
	}
	if (child.parentNeurons.size() != 1)
	{
		throw new std::string( "child.parentNeurons is not initialized correctly" );
		return true;
	}
	if (parent.childStatus.size() != 1)
	{
		throw new std::string( "parent.childStatus is not initialized correctly" );
		return true;
	}
	if (child.parentStatus.size() != 1)
	{
		throw new std::string( "child.parentStatus is not initialized correctly" );
		return true;
	}
	if (parent.childBias.size() != 1)
	{
		throw new std::string( "parent.childBias is not initialized correctly" );
		return true;
	}
	if (child.parentBias.size() != 1)
	{
		throw new std::string( "child.parentBias is not initialized correctly" );
		return true;
	}

	if (parent.childNeurons[0] != &child)
	{
		throw new std::string( "parent.childNeurons[0] != &child" );
		return true;
	}
	if (child.parentNeurons[0] != &parent)
	{
		throw new std::string( "child.parentNeurons[0] != &parent" );
		return true;
	}

	if (parent.childStatus[&child] != false)
	{
		throw new std::string( "parent.childStatus[&child] is not initialized correctly" );
		return true;
	}
	if (*child.parentStatus[&parent] != false)
	{
		throw new std::string( "child.parentStatus[&parent] is not pointing to parent.childStatus[&child]" );
		return true;
	}

	neuronConnectTestStatus = true;
	return false;
}

bool neuronDisconnectTest()
{
	if (neuronDisconnectTestStatus)
		return false;

	Neuron parent, child;

	try
	{
		neuronConnectTest();
	}
	catch ( std::string *error )
	{
		throw new std::string("neuronConnectTest: " + *error );
		return true;
	}

	parent.connect(&child);
	parent.disconnect(&child);

	if (parent.childNeurons.size() != 0)
	{
		throw new std::string( "parent.childNeurons[&child] was not removed" );
		return true;
	}

	if (child.parentNeurons.size() != 0)
	{
		throw new std::string( "child.parentNeurons[&parent] was not removed" );
		return true;
	}

	if (parent.childStatus.size() != 0)
	{
		throw new std::string( "parent.childStatus[&child] was not removed" );
		return true;
	}

	if (child.parentStatus.size() != 0)
	{
		throw new std::string( "child.parentStatus[&parent] was not removed" );
		return true;
	}

	if (parent.childBias.size() != 0)
	{
		throw new std::string( "parent.childBias[&child] was not removed" );
		return true;
	}

	if (child.parentBias.size() != 0)
	{
		throw new std::string( "child.parentBias[&parent] was not removed" );
		return true;
	}

	neuronDisconnectTestStatus = true;
	return false;
}

bool neuronForwardTest()
{
	if (neuronForwardTestStatus)
		return false;


	Neuron parent, middle, child;

	try
	{
		neuronConnectTest();
	}
	catch ( std::string *error )
	{
		throw new std::string("neuronConnectTest: " + *error );
		return true;
	}

	parent.connect(&middle);
	parent.childBias[&middle] = 1;
	middle.connect(&child);
	middle.childBias[&child] = 1;
	passon = false;
	autocalc = false;

	middle.forward(1, &parent);

	if (*middle.parentStatus[&parent] != true)
	{
		throw new std::string( "the middle neuron's parent status is not being updated" );
		return true;
	}

	if (middle.input != 1)
	{
		// either the neuron is ignoring autocalc=false and resetting its input by its self or the input was not set correctly by .forward(int)
		throw new std::string( "the middle neuron is not waiting for forward() or forward(int) set it's input incorrectly" );
		return true;
	}

	if (middle.output != 0)
	{
		// this means that the neuron is doing its computation upon recieving the last of its parent's outputs. the neuron should wait until .forward() is called. this can also be caused if neuron outputs are not initialized as 0.
		throw new std::string( "the middle neuron is not waiting for forward()" );
		return true;
	}

	autocalc = true;

	middle.input = 0;
	*middle.parentStatus[&parent] = false;
	middle.forward(1, &parent);

	if (middle.input != 0)
	{
		// the neuron is not resetting the input upon finishing its computation. this could also be caused by the neuron ignoring autocalc and not starting computation upon recieving its last input.
		throw new std::string( "the middle neuron is not resetting its input or is not waiting for forward()" );
		return true;
	}

	// assuming the neurons computation consists of solely ( input >= 1 ? output = 1 : output = 0 )
	if (middle.output != 1)
	{
		// the output is either incorrect or the neuron is ignoring autocalc and not performing its computation upon recieving its last input.
		throw new std::string( "either the middle neuron's output is incorrect or it is ignoring autocalc" );
		return true;
	}

	passon = true;

	middle.input = 0;
	middle.output = 0;
	middle.forward(1, &parent);

	if (middle.output != 1)
	{
		// neurons are resetting their output after passing it on to all their children.
		throw new std::string( "the middle neuron reset its output after passing it to all children" );
		return true;
	}

	if (child.output != 1)
	{
		// this happens if the bias calculations produce anything other than 1 for child.forward(int).
		throw new std::string( "the child's bias calculations are not producing 1 when the input is 1" );
		return true;
	}

	// TODO every test should create a new copy of the network
	passon = false;
	autocalc = false;

	neuronForwardTestStatus = true;
	return false;
}

bool neuronBackwardTest()
{
	if (neuronBackwardTestStatus)
		return false;

	Neuron parent, middle, child;

	try
	{
		neuronConnectTest();
	}
	catch ( std::string *error )
	{
		throw new std::string("neuronConnectTest: " + *error );
		return true;
	}

	parent.connect(&middle);
	parent.childBias[&middle] = 1;
	middle.connect(&child);
	middle.childBias[&child] = 1;
	passon = false;
	autocalc = false;

	middle.backward(1, &child);

	if (middle.childStatus[&child] != true)
	{
		throw new std::string( "middle.childStatus[&child] is not being updated" );
		return true;
	}

	if (middle.output != 1)
	{
		// either the neuron is ignoring autocalc=false and resetting its output by its self or the output was not set correctly by .backward(int)
		throw new std::string( "the middle neuron is either not waiting for backward() or the output was set incorrectly by backward(int)" );
		return true;
	}

	if (middle.input != 0)
	{
		// this means that the neuron is doing its computation upon recieving the last of its child's inputs. the neuron should wait until .backward() is called. this can also be casued if neuron inputs are not initialized to 0.
		throw new std::string( "the middle neuron is not waiting for backward()" );
		return true;
	}

	autocalc = true;

	middle.output = 0;
	middle.childStatus[&child] = false;
	middle.backward(1, &child);

	if (middle.output != 0)
	{
		// the neuron is not resetting the input upon finishing its computation. this could also be caused by the neuron ignoring autocalc and not starting computation upon recieving its last input.
		throw new std::string( "the middle neuron is either not resetting the input or ignoring autocalc"  );
		return true;
	}

	// assuming the neurons computation consists of solely ( output >= 1 ? input = 1 : input = 0 )
	if (middle.input != 1)
	{
		// the output is either incorrect or the neuron is ignoring autocalc and not performing its computation upon recieving its last output.
		throw new std::string( "the middle neuron's output is either incorrect or the middle neuron is ignoring autocalc" );
		return true;
	}

	passon = true;

	middle.output = 0;
	middle.input = 0;
	middle.backward(1, &child);

	if (middle.input != 1)
	{
		// neurons are resetting their input after passing it on to all their children.
		throw new std::string( "neurons are resetting their input after passing it to all their children in reverse mode" );
		return true;
	}

	if (parent.input != 1)
	{
		// this happens if the bias calculations produce anything other than 1 for parent.backward(int).
		throw new std::string( "parent's backward bias calculations are not producing 1 when input 1" );
		return true;
	}

	passon = false;
	autocalc = false;

	neuronBackwardTestStatus = true;
	return false;
}