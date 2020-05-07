#pragma once
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include "Instruments.h"
#define ull unsigned long long


namespace gcew::commons {

	class VariableManager {
	public:
		struct VariableContext {
			ull size;
			ull id;
		};
	private:
		static VariableManager* vm;
		VariableManager() = default;
		std::vector<int> levelStart;
		std::map<int, std::map<std::string, VariableContext>> contextInfo;
		int currentLevel{ 0 };
		int contextVariableLevel{ 0 };
	public:
		static VariableManager& manager();
		void registerTree();
		void unregisterTree();
		int registerVariable(std::string name, ull size);
		void unregisterVariable(std::string name);
		VariableContext getVariable(std::string name);
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

	class IncludeManager {
	private:
		std::map<std::string, std::vector<std::string>> libs;
		static IncludeManager* im;
	public:
		static IncludeManager& manager();
		void registerLibs(std::string name);
		bool haveFunction(std::string name);
	};

}

#define VM gcew::commons::VariableManager::manager()
#define FM gcew::commons::FunctionManager::manager()
#define IM gcew::commons::IncludeManager::manager()