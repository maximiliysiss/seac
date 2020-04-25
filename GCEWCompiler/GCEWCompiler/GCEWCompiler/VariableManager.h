#pragma once
#include <map>
#include <string>
#include <vector>


namespace gcew::commons {

	class VariableManager {
	private:
		static VariableManager* vm;
		VariableManager() = default;
		std::vector<int> levelStart;
		std::map<int, std::map<std::string, int>> contextInfo;
		int currentLevel{ 0 };
		int contextVariableLevel{ 0 };
	public:
		static VariableManager& manager();
		void registerTree();
		void unregisterTree();
		int registerVariable(std::string name);
		void unregisterVariable(std::string name);
		int getVariable(std::string name);
	};


	class FunctionManager {
	private:
		static FunctionManager* fm;
		FunctionManager() = default;
		std::map<std::string, int> contextInfo;
		unsigned int functionId{ 0 };
	public:
		static FunctionManager& manager();
		void registerTree(std::string name);
		int getFunction(std::string name);
	};

}

#define VM gcew::commons::VariableManager::manager()
#define FM gcew::commons::FunctionManager::manager()