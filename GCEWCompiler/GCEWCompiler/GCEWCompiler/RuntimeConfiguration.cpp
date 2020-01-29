#include "RuntimeConfiguration.h"

namespace gcew::commons {

	RuntimeConfiguration* RuntimeConfiguration::runtime = nullptr;

	RuntimeConfiguration::RuntimeConfiguration()
	{
		typeWeights = {
			{ "int", 4 },
			{ "float", 4 },
			{ "double", 8 },
			{ "string", 1 },
		};
	}

	RuntimeConfiguration& gcew::commons::RuntimeConfiguration::getInstance()
	{
		if (runtime)
			return *runtime;
		return *(runtime = new RuntimeConfiguration());
	}

	ull RuntimeConfiguration::registerVariable(std::string type)
	{
		return (variableSize += typeWeights[type]);
	}

	unsigned int RuntimeConfiguration::registerTree()
	{
		return treeIndex++;
	}

	void RuntimeConfiguration::unregisterTree(unsigned int index)
	{
		treeIndex = index;
	}


}