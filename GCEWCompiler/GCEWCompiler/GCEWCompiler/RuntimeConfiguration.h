#pragma once
#include "Enums.h"
#include <string>
#include <map>

namespace gcew::commons {


	class RuntimeConfiguration
	{
	private:
		RuntimeConfiguration();
		static RuntimeConfiguration* runtime;
		std::map<std::string, ull> typeWeights;
		std::map<std::string, ull> variable;

		unsigned int treeIndex{ 0 };
		ull variableSize{ 0 };
	public:
		static RuntimeConfiguration& getInstance();
		ull registerVariable(std::string type);
		unsigned int registerTree();
		void unregisterTree(unsigned int);
	};
}

