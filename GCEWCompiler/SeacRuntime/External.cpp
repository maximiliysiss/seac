#include "External.h"

namespace seac::runtime::external {

	ExternalCallManager* ExternalCallManager::ecm = nullptr;

	ExternalCallManager::ExternalCallManager()
		:config(RuntimeConfiguration::config().get_ec()) {
		caller.push_back(new AdapterCaller());
		for (auto& lib : config.libraries) {
			caller.push_back(new LibraryCaller(lib));
		}
	}

	ExternalCallManager& seac::runtime::external::ExternalCallManager::manager() {
		if (ecm)
			return *ecm;
		return *(ecm = new ExternalCallManager());
	}

	void ExternalCallManager::call(std::string name, std::vector<ArgumentCall> args) {
		auto mainPart = helpers::splitter(name, ':')[1];
		auto resultName = helpers::splitter(mainPart, '(')[0];
		for (auto& call : caller) {
			if (call->find(resultName)) {
				call->call(resultName, args);
				return;
			}
		}

		throw helpers::runtime("not found function");
	}

	void AdapterCaller::call(std::string name, std::vector<ArgumentCall> data) {
		if (name == "printf") {
			uint size = 0;
			for (int i = 1; i < data.size(); i++) {
				size += data[i].size;
			}
			va_list arg = new char[size];
			size = 0;
			for (int i = 1; i < data.size(); i++) {
				memcpy(arg + size, data[i].data, data[i].size);
				size += data[i].size;
			}
			vprintf((const char*)data[0].data, arg);
			delete[] arg;
		} elif(name == "scanf") {
			uint size = 0;
			for (int i = 1; i < data.size(); i++) {
				size += data[i].size;
			}
			va_list arg = new char[size];
			size = 0;
			for (int i = 1; i < data.size(); i++) {
				memcpy(arg + size, data[i].data, data[i].size);
				size += data[i].size;
			}
			vscanf((const char*)data[0].data, arg);
			delete[] arg;
		}
	}

	std::list<std::string> AdapterCaller::operations() {
		return std::list<std::string>{
			"printf", "scanf"
		};
	}

	LibraryCaller::LibraryCaller(std::string name)
		:libName(name) {
		libHandler = LoadLibrary(name.c_str());
	}

	void LibraryCaller::call(std::string name, std::vector<ArgumentCall> data) {
	}

	std::list<std::string> LibraryCaller::operations() {
		return std::list<std::string>();
	}

	bool ICaller::find(std::string name) {
		for (auto& lName : operations()) {
			if (name == lName)
				return true;
		}
		return false;
	}

}
