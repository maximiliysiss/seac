#include "External.h"

namespace seac::runtime::external {

	ExternalCallManager* ExternalCallManager::ecm = nullptr;

	ExternalCallManager::ExternalCallManager() {
	}

	ExternalCallManager& seac::runtime::external::ExternalCallManager::manager() {
		if (ecm)
			return *ecm;
		return *(ecm = new ExternalCallManager());
	}

	void ExternalCallManager::call(std::string name, void* data ...) {
	}

	void ExternalCallManager::call(std::string name) {
	}

}
