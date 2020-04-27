#include "External.h"

namespace seac::runtime::external {

	ExternalCallManager* ExternalCallManager::ecm = nullptr;

	ExternalCallManager::ExternalCallManager()
		:config(RuntimeConfiguration::config().get_ec()) {
	}

	ExternalCallManager& seac::runtime::external::ExternalCallManager::manager() {
		if (ecm)
			return *ecm;
		return *(ecm = new ExternalCallManager());
	}

}
