#include <io.hpp>
#include "parse.hpp"
#include "network.hpp"

bool load(Network &network)
{
  string raw = "";

  raw = io::read("onClose.nnet");

  if (interpretNetwork(raw, network))
    return true;

  return false;
}

bool interpretNetwork(string &raw, Network &network)
{
  if (interpretCluster(raw, network.cluster))
    return true;

  return false;
}

  bool interpretCluster(string raw, Cluster &cluster)
  {
    vector<unsigned int> levelRanges(0);

    while (parse::find(raw, "level " + to_string(cluster.levels.size() + 1) ).position != -1)
    {
      cluster.levels.resize(cluster.levels.size() + 1);
      levelRanges.push_back(parse::find(raw, "level " + to_string(cluster.levels.size() + 1)).position);
    }

    levelRanges.push_back(raw.length());

    for (unsigned int l = 0; l < cluster.levels.size(); l++)
    {
      if (interpretLevel(raw.substr(levelRanges[l], levelRanges[l + 1]), cluster.levels[l]))
        return true;
    }

    return false;
  }

  bool interpretLevel(string raw, Level &level)
  {
    vector<unsigned int> neuronRanges(0);

    while (parse::find(raw, " neuron " + to_string(level.neurons.size() + 1) ).position != -1)
    {
      level.neurons.resize(level.neurons.size() + 1);
      neuronRanges.push_back(parse::find(raw, " neuron " + to_string(level.neurons.size() + 1)).position);
    }

    neuronRanges.push_back(raw.length());

    for (unsigned int n = 0; n < level.neurons.size(); n++)
    {
      if (interpretNeuron(raw.substr(neuronRanges[n], neuronRanges[n + 1]), level.neurons[n]))
        return true;
    }

    return false;
  }

  bool interpretNeuron(string raw, Neuron &neuron)
  {
    vector<unsigned int> outputRanges(0);

    while (parse::find(raw, "  output " + to_string(neuron.outputs.size() + 1) ).position != -1)
    {
      neuron.outputs.resize(neuron.outputs.size() + 1);
      outputRanges.push_back(parse::find(raw, "  output " + to_string(neuron.outputs.size() + 1)).position);
    }

    outputRanges.push_back(raw.length());

    for (unsigned int n = 0; n < neuron.outputs.size(); n++)
    {
      cout << n << endl;
      if (interpretOutput(raw.substr(outputRanges[n], outputRanges[n + 1]), neuron.outputs[n]))
        return true;
    }

    return false;
  }

  bool interpretOutput(string raw, Connection &connection)
  {
    Result weightIterator;

    weightIterator = parse::find(raw, "(~)");

    if (weightIterator.position == -1)
      return true;

    connection.weight = parse::stof(raw.substr(weightIterator.position + 1, weightIterator.length - 2));

    return false;
  }

  bool save(Network &network)
  {
    ofstream file("onClose.nnet");
    
    for (unsigned int l = 0; l < network.cluster.levels.size(); l++)
    {
      file << "level " << l << endl;
      
      for (unsigned int n = 0; n < network.cluster.levels[l].neurons.size(); n++)
      {
        file << " neuron " << n << endl;
        
        for(unsigned int w = 0; w < network.cluster.levels[l].neurons[n].outputs.size(); w++)
        {
          file << "  output " << w << " (" << network.cluster.levels[l].neurons[n].outputs[w].weight << ")" << endl;
        }
      }
      
      if (l + 1 < network.cluster.levels.size())
        file << endl;
    }
    
    file.close();
    return false;
  }

/*#ifdef TESTS

  namespace tests
  {
    bool networkIOTest()
    {
      if (fileExistsTest() || writeTest() || deleteFileTest() || moveFileTest())
      {
        cout << "networkIOTest failed." << endl;
        return true;
      }

      if (fileExists("onClose.nnet"))
        moveFile("onClose.nnet", "old.nnet");
      write("onClose.nnet", testFile);

      if (loadTest() || saveTest())
      {
        cout << "networkIOTest failed." << endl;
        return true;
      }

      deleteFile("onClose.nnet");
      
      cout << "networkIOTest passed." << endl;
      return false;
    }

    bool loadTest()
    {
      if (readTest() || interpretNetworkTest())
      {
        cout << "loadTest failed." << endl;
        return true;
      }

      cout << "loadTest passed." << endl;
      return false;
    }

    bool interpretNetworkTest()
    {
      if (findTest() || interpretClusterTest())
      {
        cout << "interpretNetworkTest failed." << endl;
        return true;
      }

      cout << "interpretNetworkTest passed." << endl;
      return false;
    }

    bool interpretClusterTest()
    {
      if (findTest() || interpretLevelTest())
      {
        cout << "interpretClusterTest failed." << endl;
        return true;
      }

      cout << "interpretClusterTest passed." << endl;
      return false;
    }

    bool interpretLevelTest()
    {
      if (findTest() || interpretNeuronTest())
      {
        cout << "interpretLevelTest failed." << endl;
        return true;
      }

      cout << "interpretLevelTest passed." << endl;
      return false;
    }

    bool interpretNeuronTest()
    {
      if (findTest() || interpretOutputTest())
      {
        cout << "interpretNeuronTest failed." << endl;
        return true;
      }

      Neuron neuron;

      if (interpretNeuron(" neuron 0\n  output 0 (0.1)\n  output 1 (0.8)\n  output 2 (0.4)\n  output 3 (-0.1)\n", neuron))
      {
        cout << "interpretNeuronTest failed." << endl;
        return true;
      }

      if (neuron.outputs.size() != 4)
      {
        cout << "interpretNeuronTest failed." << endl;
        return true;
      }

      if (neuron.outputs[0].weight != 0.1)
      {
        cout << "interpretNeuronTest failed." << endl;
        return true;
      }

      if (neuron.outputs[1].weight != 0.8)
      {
        cout << "interpretNeuronTest failed." << endl;
        return true;
      }

      if (neuron.outputs[2].weight != 0.4)
      {
        cout << "interpretNeuronTest failed." << endl;
        return true;
      }

      if (neuron.outputs[3].weight != -0.1)
      {
        cout << "interpretNeuronTest failed." << endl;
        return true;
      }

      cout << "interpretNeuronTest passed." << endl;
      return false;
    }

    bool interpretOutputTest()
    {
      if (findTest())
      {
        cout << "interpretOutputTest failed." << endl;
        return true;
      }

      Connection connection;

      if (interpretOutput("  output 0 (0.0)", connection))
      {
        cout << "failed to get weight | '  output 0 (0.0)'" << endl;
        cout << "interpretOutputTest failed." << endl;
        return true;
      }

      if (connection.weight != 0.0)
      {
        cout << connection.weight << " != 0.0" << endl;
        cout << "interpretOutputTest failed." << endl;
        return true;
      }

      if (interpretOutput("  output 0 (0.20)", connection))
      {
        cout << "failed to get weight | '  output 0 (0.20)'" << endl;
        cout << "interpretOutputTest failed." << endl;
        return true;
      }

      if (connection.weight - 0.2 != 0.0)
      {
        cout << connection.weight - 0.2 << " != 0.0" << endl;
        cout << "interpretOutputTest failed." << endl;
        return true;
      }

      cout << "interpretOutputTest passed." << endl;
      return false;
    }

    bool saveTest()
    {


      cout << "saveTest passed." << endl;
      return false;
    }
  }

#endif // TESTS*/
#endif // NETWORKIO_SA