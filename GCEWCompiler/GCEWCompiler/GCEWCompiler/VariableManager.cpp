#include "VariableManager.h"
#include "CompileConfiguration.h"
#include "CodeStream.h"
#include "FunctionTree.h"

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

	bool FunctionManager::isGetFunction(std::string name){
		return contextInfo.find(name) != contextInfo.end();
	}

	IncludeManager* IncludeManager::im = nullptr;

	IncludeManager& IncludeManager::manager() {
		if (im)
			return *im;
		return *(im = new IncludeManager());
	}

	void IncludeManager::registerLibs(std::string name) {
		auto splits = splitter(name, '.');
		std::string resultFileName = CompileConfiguration::instance().getLibsPath();
		for (int i = 0; i < splits.size() - 1; i++) {
			resultFileName += '\\' + splits[i];
		}
		resultFileName += '\\' + splits[splits.size() - 1] + ".seac";
		std::ifstream lib(resultFileName);
		if (!lib.is_open())
			throw commons::compiler_exception("lib not found");

		CodeStream codeStream(lib);

		CodeStream::IStreamData* data = nullptr;
		CodeStream::IStreamCodeData* streamCode = nullptr;

		std::vector<std::string> functions;

		do {
			if (data)
				delete data;
			codeStream >> &data;
			streamCode = dynamic_cast<CodeStream::IStreamCodeData*>(data);

			if (streamCode && streamCode->stream_code == 2 && streamCode->code == (ull)JitOperation::libinfo) {
				functions.push_back(((StringStreamData*)streamCode)->operand_first);
			}
		} while (!streamCode || streamCode->code != (ull)JitOperation::libend);

		this->libs[name] = functions;

		lib.close();
	}

	void* IncludeManager::getFunction(std::string name) {

		for (auto& l : libs) {
			std::string res;

			for (auto& p : l.second) {
				if (p.find(name) != std::string::npos) {
					res = p;
					break;
				}
			}

			if (res.length() > 0) {
				std::string funcVirtualCall = "void ";
				auto splt = splitter(res, '_');
				funcVirtualCall += splt[0] + "( ";
				for (int i = 1; i < splt.size(); i++) {
					funcVirtualCall += splt[i] + " a,";
				}
				funcVirtualCall.erase(funcVirtualCall.end() - 1);
				funcVirtualCall += ')';
				return new trees::structural::FunctionTree(0, funcVirtualCall, commons::RegexResult::Function, nullptr);
			}
		}

		return nullptr;
	}

}
