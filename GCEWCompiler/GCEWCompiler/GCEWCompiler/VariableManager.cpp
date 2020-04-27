#include "VariableManager.h"

namespace gcew::commons {

	VariableManager& VariableManager::manager() {
		if (vm)
			return *vm;
		return *(vm = new VariableManager());
	}

	void VariableManager::registerTree() {
		currentLevel++;
		levelStart.push_back(contextVariableLevel);
	}

	void VariableManager::unregisterTree() {
		contextInfo[currentLevel].clear();
		currentLevel--;
		contextVariableLevel = levelStart[levelStart.size() - 1];
		levelStart.erase(levelStart.end() - 1);
	}

	int VariableManager::registerVariable(std::string name, ull size) {
		contextVariableLevel++;
		VariableContext vc; vc.id = contextVariableLevel; vc.size = size;
		contextInfo[currentLevel][name] = vc;
		return contextVariableLevel;
	}

	void VariableManager::unregisterVariable(std::string name) {
		contextInfo[currentLevel].erase(name);
	}

	VariableManager::VariableContext VariableManager::getVariable(std::string name) {
		if (contextInfo[currentLevel].find(name) == contextInfo[currentLevel].end()) {
			throw std::exception("not found variable");
		}
		return contextInfo[currentLevel][name];
	}

	VariableManager* VariableManager::vm = nullptr;
	FunctionManager* FunctionManager::fm = nullptr;

	FunctionManager& FunctionManager::manager() {
		if (fm)
			return *fm;
		return *(fm = new FunctionManager());
	}

	void FunctionManager::registerTree(std::string name) {
		if (contextInfo.find(name) != contextInfo.end()) {
			throw std::exception("found copy of function");
		}
		contextInfo[name] = ++functionId;
	}

	int FunctionManager::getFunction(std::string name) {
		if (contextInfo.find(name) == contextInfo.end()) {
			throw std::exception("not found function");
		}
		return contextInfo[name];
	}

}
